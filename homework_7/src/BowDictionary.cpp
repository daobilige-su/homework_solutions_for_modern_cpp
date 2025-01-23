#include "BowDictionary.hpp"

namespace ipb {

BowDictionary &BowDictionary::GetInstance() {
  static BowDictionary instance;
  return instance;
}

// Getters methods
int BowDictionary::max_iterations() const { return max_iter_; }

int BowDictionary::size() const { return dic_size_; } // number of centroids

std::vector<cv::Mat> BowDictionary::descriptors() const { return desc_; }

cv::Mat BowDictionary::vocabulary() const { return dic_; }

int BowDictionary::total_features() const {
  return desc_.size();
} // number of input features

bool BowDictionary::empty() const { return (dic_size_ == 0); }


// Setters methods
bool BowDictionary::set_max_iterations(const int max_iter){
  max_iter_ = max_iter;
  compute_bow_dict();
  return true;
}

bool BowDictionary::set_size(const int dic_size) {
  dic_size_ = dic_size;
  compute_bow_dict();
  return true;
}

bool BowDictionary::set_descriptors(const std::vector<cv::Mat> &desc) {
  desc_ = desc;
  compute_bow_dict();
  return true;
}

bool BowDictionary::set_params(const int max_iter, const int dic_size,
                               const std::vector<cv::Mat> &desc) {
  max_iter_ = max_iter;
  dic_size_ = dic_size;
  desc_ = desc;
  compute_bow_dict();
  return true;
}

bool BowDictionary::compute_bow_dict() {
  dic_ = kMeans(desc_, dic_size_, max_iter_);
  return true;
}

} // namespace ipb