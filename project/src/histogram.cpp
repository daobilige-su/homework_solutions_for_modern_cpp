#include "histogram.hpp"
#include <numeric>
#include <opencv2/core/cvstd_wrapper.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/features2d.hpp>
#include <string>

namespace ipb {

// compute euclidean distance for a matrix
// float compute_euc_dist(cv::Mat_<float> mat) {
//   float dist = 0;
//   for (int i = 0; i < mat.rows; i++) {
//     for (int j = 0; j < mat.cols; j++) {
//       dist += pow(mat.at<float>(i, j), 2);
//     }
//   }
//   return dist;
// }

Histogram::Histogram() { data_.clear(); }
Histogram::Histogram(const std::vector<int> &data) { data_ = data; }
Histogram::Histogram(const cv::Mat &descriptors,
                     const BowDictionary &dictionary) {
  cv::Mat voc = dictionary.vocabulary();

  data_.clear();
  if (descriptors.empty()) {
    return;
  }
  data_.resize(voc.rows);

  // for (int i = 0; i < descriptors.rows; i++) {
  //   cv::Mat desc = descriptors.row(i);

  //   float min_dist = -1;
  //   int min_dist_idx = -1;
  //   for (int j = 0; j < voc.rows; j++) {
  //     cv::Mat voc_row = voc.row(j);
  //     float dist = compute_euc_dist(desc - voc_row);

  //     if (min_dist < 0) {
  //       min_dist = dist;
  //       min_dist_idx = 0;
  //     } else {
  //       if (min_dist>dist) {
  //         min_dist = dist;
  //         min_dist_idx = j;
  //       }
  //     }
  //   }
  //   data_.at(min_dist_idx) += 1;
  // }

  // Ptr<DescriptorMatcher> matcher =
  //     DescriptorMatcher::create(DescriptorMatcher::FLANNBASED);
  // std::vector<std::vector<DMatch>> knn_matches;
  // matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);

  cv::Ptr<cv::DescriptorMatcher> flann_matcher =
      cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
  std::vector<std::vector<cv::DMatch>> knn_matches;
  flann_matcher->knnMatch(descriptors, voc, knn_matches, 2);

  for (size_t i = 0; i < knn_matches.size(); i++) {
    data_.at(knn_matches[i][0].trainIdx) += 1;
  }
}

int &Histogram::operator[](std::size_t idx) { return data_[idx]; }

const int &Histogram::operator[](std::size_t idx) const { return data_[idx]; }

bool Histogram::WriteToCSV(std::string filename) {
  std::ofstream output_file(filename, std::ios_base::out);

  for (const auto &val : data_) {
    output_file<< val << ",";
  }
  output_file<<std::endl;

  return true;
}

Histogram Histogram::ReadFromCSV(std::string filaname) {
  std::vector<int> data;
  std::string line, word;

  std::ifstream in_file(filaname, std::ios_base::in);
  getline(in_file, line);

  std::stringstream s(line);
  while (getline(s, word, ',')) {
    data.push_back(std::stoi(word));
  }

  return Histogram(data);
}

std::vector<int> Histogram::data() const { return data_; }

int Histogram::size() const { return data_.size(); }

bool Histogram::empty() const { return data_.empty(); }

std::vector<int>::iterator Histogram::begin() { return data_.begin(); }
// std::vector<int>::const_iterator iter = data_.begin();
// return iter;
std::vector<int>::const_iterator Histogram::begin() const {
  return data_.begin();
}
std::vector<int>::const_iterator Histogram::cbegin() const {
  return data_.cbegin();
}
std::vector<int>::iterator Histogram::end() { return data_.end(); }
std::vector<int>::const_iterator Histogram::end() const { return data_.end(); }
std::vector<int>::const_iterator Histogram::cend() const {
  return data_.cend();
}

std::ostream &operator<<(std::ostream &os, const Histogram &histogram) {
  auto data = histogram.data();
  for (auto iter = data.begin(); iter !=data.end(); ++iter) {
    os << *iter;
    if (iter != data.end()) {
      os << ", ";
    }
  }
  return os;
}

} // namespace ipb