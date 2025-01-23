#ifndef BOVW_HPP_
#define BOVW_HPP_

#include "BowDictionary.hpp"
#include "histogram.hpp"
#include "serialize.hpp"
#include <filesystem>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <string>
#include <vector>
#include "image_browser.hpp"

namespace ipb {

class BoVW {
public:
  BoVW();
  bool set_train_folder(std::string bin_path, std::string img_path);
  bool set_kmeans_max_iter(int max_iter);
  bool set_kmeans_dic_size(int dic_size);
  bool set_css_file_path(std::string path);
  bool set_html_file_path(std::string path);
  bool set_bow_dic_path(std::string path);
  bool set_query_bin_path(std::string path);

  bool build_descriptors();
  bool build_dictionary();
  bool save_dictionary();
  bool load_dictionary();
  bool compute_histogram();
  bool select_query_image();
  bool apply_tf_idf_to_histogram();
  bool get_10_similar_images();
  bool save_results_to_html();

private:
  std::string train_bin_folder_ = "";
  std::string train_img_folder_ = "";
  std::string css_file_path_ = "";
  std::string html_file_path_ = "test.html";
  std::string bow_dic_path_ = "../dic.bin";
  std::vector<std::string> train_bin_paths_;

  std::vector<cv::Mat> descriptors_;
  std::vector<cv::Mat> descriptors_single_row_;
  int kmeans_max_iter_ = 10;
  int kmeans_dic_size_ = 1000;

  BowDictionary &bow_dic_ = BowDictionary::GetInstance();
  std::string query_bin_path_ = "";
  std::string query_img_path_ = "";

  std::vector<Histogram> hists_;
  std::vector<std::string> similar_images_;
  std::vector<float> similar_images_cossim_;

  std::vector<std::vector<float>> tf_idf_hist_;
};

}

#endif