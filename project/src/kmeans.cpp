#include "kmeans.hpp"
#include <iostream>

namespace ipb {

// compute euclidean distance for a matrix
float compute_euc_dist(cv::Mat_<float> mat) {
  float dist = 0;
  for (int i = 0; i < mat.rows; i++) {
    for (int j = 0; j < mat.cols; j++) {
      dist += pow(mat.at<float>(i, j), 2);
    }
  }
  return dist;
}

// compute the center (mean) of all cluster
cv::Mat compute_clusters_mean(std::vector<std::vector<cv::Mat>> vec) {
  // std::cout << vec.size() << "X" << vec.begin()->size()
  //           << ",type:" << vec.begin()->begin()->type() << std::endl;
  cv::Mat mean_mat = cv::Mat::zeros(vec.size(), vec.begin()->begin()->cols,
                                    vec.begin()->begin()->type());

  for (int r = 0; r < int(vec.size()); r++) {
    auto vec_row = vec[r];
    cv::Mat mean_mat_row = cv::Mat::zeros(1, vec.begin()->begin()->cols,
                                          vec.begin()->begin()->type());
    mean_mat_row =
        std::accumulate(vec_row.begin(), vec_row.end(), mean_mat_row);
    // mean_mat.row(r) = mean_mat_row.clone() / vec_row.size();
    cv::Mat m = mean_mat_row.clone() / vec_row.size();
    m.copyTo(mean_mat.row(r));
  }

  return mean_mat;
}

/**
 * @brief
 * 1. Given cluster centroids i initialized in some way,
 * 2. For iteration t=1..T:
 * 1. Compute the distance from each point x to each cluster centroid ,
 * 2. Assign each point to the centroid it is closest to,
 * 3. Recompute each centroid as the mean of all points assigned to it,
 *
 * @param descriptors The input SIFT descriptors to cluster.
 * @param k The size of the dictionary, ie, number of visual words.
 * @param max_iterations Maximum number of iterations before convergence.
 * @return cv::Mat One unique Matrix representing all the $k$-means(stacked).
 */

// This implementation is not passing the gtest. The main reason is the
// initialization is not working well. 
cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {

  int desc_vec_size = descriptors.begin()->cols;
  int desc_num = descriptors.size();
  cv::Mat kmeans_centers = cv::Mat::zeros(k, desc_vec_size, CV_32F);

  //   Initialize k means with random values
  // float rand_max = 1;
  // std::random_device rd;
  // std::uniform_real_distribution<float> dist(-rand_max, rand_max);
  // for (int i = 0; i < kmeans_centers.rows; i++) {
  //   for (int j = 0; j < kmeans_centers.cols; j++) {
  //     kmeans_centers.at<float>(i, j) = dist(rd);
  //   }
  // }
  auto desc_copy = descriptors;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(desc_copy.begin(), desc_copy.end(),
               std::default_random_engine(seed));
  for (int i = 0; i < kmeans_centers.rows; i++) {
    // kmeans_centers.row(i) = desc_copy[i].clone();
    desc_copy[i].copyTo(kmeans_centers.row(i));
    // std::cout << desc_copy[i] << std::endl << std::endl;
    // std::cout << kmeans_centers.row(i) << std::endl << std::endl;
  }
  // std::cout << kmeans_centers << std::endl << std::endl;

  std::vector<std::vector<cv::Mat>> clusters;
  std::vector<float> euc_dist;
  clusters.resize(k);
  euc_dist.resize(k);
  // -- > For a given number of iterations :
  for (int iter = 0; iter < max_iter; iter++) {
    std::cout << "kmeans iter: " << iter << std::endl;
    // //       -- > Iterate through items :
    // for (const auto &desc : descriptors) {
      
    //   //       -- > Find the mean closest to the item by calculating the
    //   //       euclidean distance of the item with each of the means
    //   for (int n = 0; n < k; n++) {
    //     euc_dist[n] = compute_euc_dist(desc - kmeans_centers.row(n));
    //   }
    //   auto min_elem_ptr = std::min_element(euc_dist.begin(), euc_dist.end());
    //   auto min_clus_idx = std::distance(euc_dist.begin(), min_elem_ptr);

    //   //       -- > Assign item to mean
    //   clusters[min_clus_idx].emplace_back(desc);
    // }

    // find the descriptors to clusters correspondance
    cv::Mat descriptors_mat = cv::Mat::zeros(desc_num, desc_vec_size, CV_32F);
    for (int r=0; r<desc_num; ++r) {
      descriptors[r].copyTo(descriptors_mat.row(r));
    }
    cv::Ptr<cv::DescriptorMatcher> flann_matcher =
        cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
    std::vector<std::vector<cv::DMatch>> knn_matches;
    flann_matcher->knnMatch(descriptors_mat, kmeans_centers, knn_matches, 2);
    for (size_t i = 0; i < knn_matches.size(); i++) {
      clusters[knn_matches[i][0].trainIdx].emplace_back(
          descriptors_mat.row(knn_matches[i][0].queryIdx));
    }

    //       -- > Update mean by shifting it to the average of the items in
    //       that cluster
    for (int r = 0; r < int(clusters.size()); r++) {
      if (clusters[r].empty()) {
        clusters[r].emplace_back(kmeans_centers.row(r));
      }
    }
    kmeans_centers = compute_clusters_mean(clusters);
    clusters.clear();
    clusters.resize(k);
  }

  return kmeans_centers;
}

// cv::Mat kMeans(const std::vector<cv::Mat> &descriptors, int k, int max_iter) {
//   int desc_vec_size = descriptors.begin()->size().area();
//   cv::Mat kmeans_centers = cv::Mat::zeros(k, desc_vec_size, CV_32F);
//   cv::Mat desc_mat = cv::Mat::zeros(descriptors.size(), desc_vec_size, CV_32F);
//   cv::Mat empty_labels;

//   for (int i = 0; i < int(descriptors.size()); i++) {
//     descriptors[i].copyTo(desc_mat.row(i));
//   }

//   kmeans(desc_mat, k, empty_labels,
//          cv::TermCriteria(cv::TermCriteria::COUNT, max_iter, 1.0), 1,
//          cv::KMEANS_RANDOM_CENTERS, kmeans_centers); 

//   return kmeans_centers;
// }

}