#include "bovw.hpp"
#include "histogram.hpp"
#include "image_browser.hpp"
#include "serialize.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <math.h>
#include <numeric>
#include <opencv2/core/mat.hpp>
#include <string>
#include <vector>


namespace ipb {

float compute_cos_dist(std::vector<float> can_hist,
                       std::vector<float> query_tf_idf_hist) {
  if (can_hist.size() != query_tf_idf_hist.size()) {
    std::cout << "Error in function compute_cos_dist(), vector size don't match"
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  int S = can_hist.size();
  float dist = 0, x_norm = 0, y_norm = 0;
  for (int s = 0; s < S; ++s) {
    dist += can_hist[s] * query_tf_idf_hist[s];
    x_norm += can_hist[s] * can_hist[s];
    y_norm += query_tf_idf_hist[s] * query_tf_idf_hist[s];
  }
  x_norm = sqrt(x_norm);
  y_norm = sqrt(y_norm);

  float cos_dist = 1 - (dist / (x_norm * y_norm));
  return cos_dist;
}

BoVW::BoVW() {
  train_bin_folder_ = "";
  train_img_folder_ = "";
  train_bin_paths_.clear();
  descriptors_.clear();
  descriptors_single_row_.clear();
  bow_dic_.set_vocabulary(cv::Mat());
  query_bin_path_ = "";
  query_img_path_ = "";
  hists_.clear();
  similar_images_.clear();
  similar_images_cossim_.clear();
  tf_idf_hist_.clear();
}

bool BoVW::set_train_folder(std::string bin_path, std::string img_path) {

  BoVW(); // reset
  std::cout<< "Intialized BoVW params." << std::endl;

  std::filesystem::path bin_folder(bin_path);
  if (std::filesystem::exists(bin_folder)) {
    train_bin_folder_ = bin_path;
    std::cout << "train_bin_folder_: [" << bin_path << "]" << std::endl;

    std::set<std::string> file_path_sorted; // sort by name
    for (const auto &entry : std::filesystem::directory_iterator(bin_folder)) {
      file_path_sorted.insert(entry.path().filename().string());
    }

    for (const auto &file_path : file_path_sorted) {
      if (std::filesystem::path(file_path).extension().string() == ".bin") {
        train_bin_paths_.emplace_back(train_bin_folder_ + "/" + file_path);
        // std::cout << train_bin_paths_.back() << std::endl;
      }
    }
  } else {
    std::cout << "Error: Bin folder [" << bin_path << "] does not exist."
              << std::endl;
    return false;
  }

  std::filesystem::path img_folder(img_path);
  if (std::filesystem::exists(img_folder)) {
    train_img_folder_ = img_path;
    std::cout << "train_img_folder_: [" << img_path << "]" << std::endl;
  } else {
    std::cout << "Error: Image folder [" << img_path << "] does not exist."
              << std::endl;
    return false;
  }

  return true;
}

bool BoVW::set_kmeans_max_iter(int max_iter) {
  kmeans_max_iter_ = max_iter;
  return true;
}

bool BoVW::set_kmeans_dic_size(int dic_size) {
  kmeans_dic_size_ = dic_size;
  return true;
}

bool BoVW::set_css_file_path(std::string path) {
  css_file_path_ = path;
  return true;
}

bool BoVW::set_html_file_path(std::string path) {
  html_file_path_ = path;
  return true;
}

bool BoVW::set_bow_dic_path(std::string path) {
  bow_dic_path_ = path;
  return true;
}

bool BoVW::set_query_bin_path(std::string path) {
  query_bin_path_ = path;
  return true;
}

bool BoVW::build_descriptors() {
  std::cout << "Start extracting descriptors ..." << std::endl;
  for (const auto &file_path : train_bin_paths_) {
    cv::Mat desc = serialization::Deserialize(file_path);
    descriptors_.emplace_back(desc);
    for (int n = 0; n < desc.rows; ++n) {
      descriptors_single_row_.emplace_back(desc.row(n));
    }
  }
  std::cout << "Finished." << std::endl;

  return true;
}

bool BoVW::build_dictionary() {
  std::cout << "Start building dictionary ..." << std::endl;
  std::cout << "Kmeans Max Iter: " << kmeans_max_iter_ << std::endl;
  std::cout << "Kmeans Dic Size: " << kmeans_dic_size_ << std::endl;
  std::cout << "descriptors_ size (Image numbers): " << descriptors_.size()
            << std::endl;
  std::cout << "descriptors_single_row_ size (descriptor vector numbers): "
            << descriptors_single_row_.size() << std::endl;
  bow_dic_.build(kmeans_max_iter_, kmeans_dic_size_, descriptors_single_row_);
  std::cout << "Finished." << std::endl;
  return true;
}

bool BoVW::save_dictionary() {
  ipb::serialization::Serialize(bow_dic_.vocabulary(), bow_dic_path_);
  std::cout << "Saved BoVW dictionary to [" << bow_dic_path_ << "]" << std::endl;
  return true;
}

bool BoVW::load_dictionary() {
  cv::Mat dic = ipb::serialization::Deserialize(bow_dic_path_);
  bow_dic_.set_vocabulary(dic);
  std::cout << "Loaded BoVW dictionary from [" << bow_dic_path_ << "]" << std::endl;
  return true;
}

bool BoVW::compute_histogram() {
  std::cout << "Start computing histogram ..." << std::endl;
  for (const auto &desc : descriptors_) {
    hists_.emplace_back(Histogram(desc, bow_dic_));
  }
  std::cout << "Finished." << std::endl;
  return true;
}

bool BoVW::select_query_image() {
  if (query_bin_path_.empty()) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, train_bin_paths_.size() - 1);
    int img_idx = dist(rd);
    query_bin_path_ = train_bin_paths_[img_idx];
  }
  std::cout << "Query Bin: " << query_bin_path_ << std::endl;

  query_img_path_ = train_img_folder_ + "/" +
                    std::filesystem::path(query_bin_path_).stem().c_str() +
                    ".png";
  std::cout << "Query Image: " << query_img_path_ << std::endl;

  cv::Mat query_desc = serialization::Deserialize(query_bin_path_);
  Histogram query_hist = Histogram(query_desc, bow_dic_);
  hists_.emplace_back(query_hist);

  return true;
}

bool BoVW::apply_tf_idf_to_histogram() {
  std::cout << "Start applying TF-IDF ..." << std::endl;

  float N = float(hists_.size());
  float S = float(hists_.begin()->size()); // dictionary size

  std::vector<float> tmp (S, 0);
  std::vector<std::vector<float>> nid(N, tmp);
  std::vector<float> ni(S, 0);
  std::vector<float> nd(N, 0);

  std::vector<std::vector<float>> tid(N, tmp);

  std::vector<int> his;
  for (int n = 0; n < N; ++n) {
    his = hists_[n].data();
    nd[n] = std::accumulate(his.begin(), his.end(), 0);

    for (int s = 0; s < S; ++s) {
      nid[n][s] = his[s];
      if (his[s] > 0) {
        ni[s] += 1;
      }
    }
  }

  for (int n = 0; n < N; ++n) {
    for (int s = 0; s < S; ++s) {
      tid[n][s] = (nid[n][s] / nd[n]) * std::log(N / ni[s]);
    }
  }

  tf_idf_hist_ = tid;
  std::cout << "Finished." << std::endl;
  return true;
}

bool BoVW::get_10_similar_images() {
  std::cout << "Finding the 10 most similar images ..." << std::endl;

  std::vector<float> query_tf_idf_hist = tf_idf_hist_.back();
  tf_idf_hist_.pop_back(); // remove the query image
  
  std::vector<float> cos_dist_vec;
  for (const auto& can_hist : tf_idf_hist_) {
    // compute cosine dist
    float cos_dist = compute_cos_dist(can_hist, query_tf_idf_hist);
    cos_dist_vec.emplace_back(cos_dist);
  }

  // sort and get the smallest 10.
  std::vector<std::pair<float, int>> cos_dist_vec_with_idx;
  for (int n = 0; n < int(cos_dist_vec.size()); ++n) {
    // filling the original array
    cos_dist_vec_with_idx.emplace_back(
        std::make_pair(cos_dist_vec[n], n)); // k = value, i = original index
  }
  sort(cos_dist_vec_with_idx.begin(), cos_dist_vec_with_idx.end());

  for (int n = 0; n < 10; ++n) {
    similar_images_.emplace_back(
        train_bin_paths_[cos_dist_vec_with_idx[n].second]);
    similar_images_cossim_.emplace_back(cos_dist_vec_with_idx[n].first);
  }

  std::cout << "Finished." << std::endl;
  return true;
}

bool BoVW::save_results_to_html() {
  std::cout << "Writing results to [" << html_file_path_ << "] ..."
            << std::endl;
  std::cout
      << "First row are query image, the next 4 rows are 10 similar images."
      << std::endl;
  

  std::vector<image_browser::ImageRow> img_rows;
  int img_num = 0;
  image_browser::ImageRow img_row;
  image_browser::ScoredImage sc_img;

  sc_img = std::make_tuple(query_img_path_, 0);
  img_row[0] = sc_img;
  img_row[1] = sc_img;
  img_row[2] = sc_img;
  img_rows.emplace_back(img_row);

  for (int n=0; n<10; n++) {
    // std::cout << entry.c_str() << std::endl;
    std::filesystem::path bin_file(similar_images_[n]);

    std::string img_path = train_img_folder_ + "/" + bin_file.stem().c_str() + ".png";
    float img_sc = similar_images_cossim_[n];

    sc_img = std::make_tuple(img_path, img_sc);
    img_row[img_num] = sc_img;

    img_num = img_num + 1;
    if (img_num == 3) {
      img_rows.emplace_back(img_row);
      img_num = 0;
    }

    if (n == 9) {
      img_row[0] = sc_img;
      img_row[1] = sc_img;
      img_row[2] = sc_img;
      img_rows.emplace_back(img_row);
      img_num = 0;
    }
  }

  image_browser::ImageBrowser ib(html_file_path_);
  ib.CreateImageBrowser("Image Browser: 10 similar images", css_file_path_,
                        img_rows);

  std::cout << "Finished." << std::endl;
  return true;
}


}