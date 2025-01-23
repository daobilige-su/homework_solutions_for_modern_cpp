#include "convert_dataset.hpp"


namespace ipb::serialization::sifts {
/**
 * @brief This helper function reads all the png files from a given path,
 * compute the SIFT descriptors for each of them, and saves the results to a
 * binary file. You can see this function as a "dataset" converter, it basically
 * converts a set of png image files to a SIFT representation of the image and
 * save the descriptors to the filesystem. You MUST write the descriptors use
 * the same filename of each image, but instead of using a '.png' extension you
 * must use a '.bin' extension
 *
 * It MUST store the binary files on the same parent directory where the images
 * are located but inside a `bin/` subfolder. Basically, after calling this
 * function with "data/freiburg/images/" as input path the results should be
 * stored in "data/freiburg/bin/""
 *
 * @param img_path The path where the png image files are located.
 */
void ConvertDataset(const std::filesystem::path &img_path) {
  std::filesystem::path img_path_clean = img_path;
  if (img_path.filename().string().empty()) {
    img_path_clean = img_path.parent_path();
  }

  const std::filesystem::path bin_path =
      std::filesystem::path(img_path_clean.parent_path().string() + "/bin");
  if (!std::filesystem::exists(bin_path)) {
    std::filesystem::create_directory(bin_path);
  }

  for (const auto& kImgDirIter : std::filesystem::directory_iterator(img_path_clean)) {
    if (kImgDirIter.path().extension().string() != ".png") {
      continue;
    }

    const cv::Mat kImg =
        cv::imread(kImgDirIter.path().string(), cv::IMREAD_GRAYSCALE);
    

    auto sift_detector = cv::xfeatures2d::SiftFeatureDetector::create();
    std::vector<cv::KeyPoint> keypts;
    sift_detector->detect(kImg, keypts);

    cv::Mat sift_descriptors;
    auto sift_desc_extr = cv::xfeatures2d::SiftDescriptorExtractor::create();
    sift_desc_extr->compute(kImg, keypts, sift_descriptors);

    std::filesystem::path output_bin_file = std::filesystem::path(
        bin_path.string() + "/" + kImgDirIter.path().stem().string() + ".bin");
    ipb::serialization::Serialize(sift_descriptors, output_bin_file.string());
  }
}

/**
 * @brief This helper function will allow you to read from a binary-like dataset
 * of SIFT descriptors and load the data into a container. This utility might be
 * used after creating this so called 'binary dataset' that basically holds all
 * the feature descriptors from a given dataset of images.
 *
 * @param bin_path Where the '.bin' files are located
 * @return std::vector<cv::Mat> Containing all the SIFT features from the input
 * binary dataset.
 */
std::vector<cv::Mat> LoadDataset(const std::filesystem::path &bin_path) {
  std::vector<cv::Mat> sift_desc_vec;

  for (const auto &kBinDirIter : std::filesystem::directory_iterator(bin_path)) {
    if (kBinDirIter.path().extension().string() != ".bin") {
      continue;
    }

    cv::Mat sift_desc =
        ipb::serialization::Deserialize(kBinDirIter.path().string());

    for (int n = 0; n < sift_desc.rows; n++) {
      sift_desc_vec.emplace_back(sift_desc.row(n));
    }
  }

  return sift_desc_vec;
}

} // namespace ipb::serialization::sifts