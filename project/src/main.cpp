#include "main.hpp"

int main() {
  // params
  std::string train_feature_bin_folder = "../../images-freiburg-x10/bin";
  std::string train_img_folder = "../../images-freiburg-x10/data1";
  std::string css_file = "../rsc/style.css";
  std::string output_html_file = "test.html";
  std::string query_bin_path =
      "../../images-freiburg-x10/bin/imageCompressedCam0_0001580.bin";
  std::string bow_dic_path = "../dic.bin";
  bool use_saved_vocabulary = true;
  bool select_random_query = false;

  ipb::BoVW bovw_obj;
  bovw_obj.set_train_folder(train_feature_bin_folder, train_img_folder);
  bovw_obj.set_css_file_path(css_file);
  bovw_obj.set_html_file_path(output_html_file);
  bovw_obj.set_kmeans_dic_size(1000);
  bovw_obj.set_kmeans_max_iter(10);
  bovw_obj.set_bow_dic_path(bow_dic_path);
  if (!select_random_query) {
    bovw_obj.set_query_bin_path(query_bin_path);
  }

  bovw_obj.build_descriptors();
  if (use_saved_vocabulary) {
    bovw_obj.load_dictionary();
  } else {
    bovw_obj.build_dictionary();
    bovw_obj.save_dictionary();
  }
  bovw_obj.compute_histogram();
  bovw_obj.select_query_image();
  bovw_obj.apply_tf_idf_to_histogram();
  bovw_obj.get_10_similar_images();
  bovw_obj.save_results_to_html();
}