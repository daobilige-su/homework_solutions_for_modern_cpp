#ifndef BOWDICTIONARY_HPP_
#define BOWDICTIONARY_HPP_

#include <opencv2/core/mat.hpp>
#include <vector>
#include "kmeans.hpp"

namespace ipb {
class BowDictionary {
public:
  BowDictionary(const BowDictionary &) = delete;
  void operator=(const BowDictionary &) = delete;
  static BowDictionary& GetInstance();
  // Getters methods
  int max_iterations() const;
  int size() const; // number of centroids / codewords
  std::vector<cv::Mat> descriptors() const;
  cv::Mat vocabulary() const;
  int total_features() const; // number of input features
  bool empty() const;

  // Setters methods
  bool set_max_iterations(const int max_iter);
  bool set_size(const int dic_size);
  bool set_descriptors(const std::vector<cv::Mat> &desc);

  bool set_params(const int max_iter, const int dic_size,
                  const std::vector<cv::Mat> &desc);

private:
  BowDictionary() = default;
  ~BowDictionary() = default;
  bool compute_bow_dict();

  int max_iter_ = 0;
  int dic_size_ = 0;
  std::vector<cv::Mat> desc_;
  cv::Mat dic_;
};
}

#endif