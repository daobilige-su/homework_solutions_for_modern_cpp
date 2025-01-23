#include "BowDictionary.hpp"

namespace ipb {

BowDictionary &BowDictionary::GetInstance() {
  static BowDictionary instance;
  return instance;
}

// Getters methods
// int BowDictionary::max_iterations() const { return max_iter_; }

int BowDictionary::size() const { return dic_.rows; } // number of centroids

// std::vector<cv::Mat> BowDictionary::descriptors() const { return desc_; }

cv::Mat BowDictionary::vocabulary() const { return dic_; }

// int BowDictionary::total_features() const {
//   return desc_.size();
// } // number of input features

bool BowDictionary::set_vocabulary(const cv::Mat& dic) {
  dic_ = dic;
  return true;
  }

bool BowDictionary::empty() const {
  // return (dic_size_ == 0);
  return (dic_.rows == 0);
  }


// Setters methods
// bool BowDictionary::set_max_iterations(const int max_iter){
//   max_iter_ = max_iter;
//   compute_bow_dict();
//   return true;
// }

// bool BowDictionary::set_size(const int dic_size) {
//   dic_size_ = dic_size;
//   compute_bow_dict();
//   return true;
// }

// bool BowDictionary::set_descriptors(const std::vector<cv::Mat> &desc) {
//   desc_ = desc;
//   compute_bow_dict();
//   return true;
// }

bool BowDictionary::build(const int max_iter, const int dic_size,
                               const std::vector<cv::Mat> &desc) {
  // max_iter_ = max_iter;
  // dic_size_ = dic_size;
  // desc_ = desc;
  compute_bow_dict(desc, dic_size, max_iter);
  return true;
}

bool BowDictionary::compute_bow_dict(std::vector<cv::Mat> desc, int dic_size,
                                     int max_iter) {
  dic_ = kMeans(desc, dic_size, max_iter);
  return true;
}

} // namespace ipb