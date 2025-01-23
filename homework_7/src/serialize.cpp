#include "serialize.hpp"
#include <cstdlib>
#include <fstream>
#include <ios>

namespace ipb::serialization {

/**
 * @brief Writes the input cv::Mat(Image, SIFT, etc) to a binary file
 *
 * @param m        The input cv::Mat you want to serialize.
 * @param filename The filename of the file where the cv::Mat will be written.
 */
void Serialize(const cv::Mat &m, const std::string &filename) {
  int mtype = m.type();
  int row_num = m.rows;
  int col_num = m.cols;

  std::ofstream output_file(filename,
                            std::ios_base::out | std::ios_base::binary);

  output_file.write(reinterpret_cast<char *>(&mtype), sizeof(mtype));
  output_file.write(reinterpret_cast<char *>(&row_num), sizeof(row_num));
  output_file.write(reinterpret_cast<char *>(&col_num), sizeof(col_num));

  // char m_begin_el = m.at<char>(0);
  // output_file.write(reinterpret_cast<char *>(&m_begin_el),
  //                   row_num * col_num * CV_ELEM_SIZE(mtype));
  output_file.write(reinterpret_cast<char *>(m.data),
                    row_num * col_num * CV_ELEM_SIZE(mtype));
  return;
};

/**
 * @brief Reads a binary file representing a cv::Mat type and outputs the
 * contetnt of this file into a new cv::Mat
 *
 * @param filename The binary file you want to read
 * @return cv::Mat The cv::Mat created from the binary file
 */
cv::Mat Deserialize(const std::string &filename) {
  std::ifstream input_file(filename, std::ios_base::in | std::ios_base::binary);

  int mtype, row_num, col_num;
  input_file.read(reinterpret_cast<char *>(&mtype), sizeof(mtype));
  input_file.read(reinterpret_cast<char *>(&row_num), sizeof(row_num));
  input_file.read(reinterpret_cast<char *>(&col_num), sizeof(col_num));

  cv::Mat m(row_num, col_num, mtype);
  input_file.read(reinterpret_cast<char *>(m.data),
                  row_num * col_num * CV_ELEM_SIZE(mtype));

  return m;
};

} // namespace ipb::serialization