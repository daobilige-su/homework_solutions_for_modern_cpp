#include "html_writer.hpp"
#include <ios>
#include <iostream>
#include <iomanip>
#include <string>
#include <filesystem>

namespace html_writer {

void OpenDocument() {
  std::cout << "<!DOCTYPE html>" << std::endl;
  std::cout << "<html>" << std::endl;
}

void CloseDocument() { std::cout << "</html>" << std::endl; };

void AddCSSStyle(const std::string &stylesheet) {
  std::cout << "<head>" << std::endl;
  std::cout << "<link rel = \"stylesheet\" type = \"text/css\" href = \""
            << stylesheet << "\" />" << std::endl;
  std::cout << "</head> " << std::endl;
}

void AddTitle(const std::string &title) {
  std::cout << "<title>" << title << "</title>" << std::endl;
}

void OpenBody() { std::cout << "<body>" << std::endl; }

void CloseBody() { std::cout << "</body>" << std::endl; }

void OpenRow() { std::cout << "<div class=\"row\">" << std::endl; }

void CloseRow() { std::cout << "</div>" << std::endl; }

void AddImage(const std::string &img_path, float score, bool highlight) {
  auto filename = std::filesystem::path(img_path).filename().string();
  auto file_ext = std::filesystem::path(img_path).extension().string();

  if (file_ext != ".png" && file_ext != ".jpg") {
    std::cerr << "Error: Unkown image file extension, only supports png and "
                 "jpg files."
              << std::endl;
  }
  if (highlight) {
    std::cout << "<div class=\"column\" style=\"border: 5px solid green;\">"
              << std::endl;
  }
  else {
    std::cout << "<div class=\"column\">" << std::endl;
  }
  std::cout << "<h2> " << filename << " </h2> " << std::endl;
  std::cout << "<img src=\"" << img_path << "\" />" << std::endl;
  std::cout << std::setprecision(2) << std::fixed << "<p>score = " << score
            << "</p>" << std::endl;
  std::cout << "</div>" << std::endl;
}
} // namespace html_writer