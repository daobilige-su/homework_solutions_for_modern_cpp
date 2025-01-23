#include "homework_3.h"
#include <filesystem>
#include <string>
#include <iostream>
#include <set>
#include <tuple>

int main() {

  std::string web_browser_folder = "web_app/";
  std::string img_folder = "data/";
  std::string title = "Image Browser";
  std::string css_style_file = "style.css";

  std::set<std::string> img_path_sorted;
  for (const auto &entry : std::filesystem::directory_iterator(web_browser_folder + img_folder)){
    img_path_sorted.insert(entry.path().filename().string());
    // std::cout << entry.path() << std::endl;
  }

  std::vector<image_browser::ImageRow> img_rows;
  int img_num = 0;
  image_browser::ImageRow img_row;

  for (const auto &filename : img_path_sorted) {
    // std::cout << entry.c_str() << std::endl;
    std::string img_path = img_folder + filename;
    float img_sc = 0.9;

    image_browser::ScoredImage sc_img = std::make_tuple(img_path, img_sc);
    img_row[img_num] = sc_img;

    img_num = img_num+1;
    if (img_num == 3) {
      img_rows.emplace_back(img_row);
      img_num = 0;
    }
  }

  image_browser::CreateImageBrowser(title, css_style_file, img_rows);
}

