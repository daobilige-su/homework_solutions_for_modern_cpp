#include "html_writer.hpp"
#include <ios>
#include <iostream>
#include <iomanip>
#include <string>
#include <filesystem>

namespace html_writer {
HtmlWriter::HtmlWriter() {}

HtmlWriter::HtmlWriter(const std::string &output_file) {
  output_file_path_ = output_file;
  ofs_ = std::ofstream(output_file_path_, std::ios_base::out);
}

void HtmlWriter::OpenDocument() {
  ofs_ << "<!DOCTYPE html>" << std::endl;
  ofs_ << "<html>" << std::endl;
}

void HtmlWriter::CloseDocument() { ofs_ << "</html>" << std::endl; };

void HtmlWriter::AddCSSStyle(const std::string &stylesheet) {
  ofs_ << "<head>" << std::endl;
  ofs_ << "<link rel = \"stylesheet\" type = \"text/css\" href = \""
       << stylesheet << "\" />" << std::endl;
  ofs_ << "</head> " << std::endl;
}

void HtmlWriter::AddTitle(const std::string &title) {
  ofs_ << "<title>" << title << "</title>" << std::endl;
}

void HtmlWriter::OpenBody() { ofs_ << "<body>" << std::endl; }

void HtmlWriter::CloseBody() { ofs_ << "</body>" << std::endl; }

void HtmlWriter::OpenRow() { ofs_ << "<div class=\"row\">" << std::endl; }

void HtmlWriter::CloseRow() { ofs_ << "</div>" << std::endl; }

void HtmlWriter::AddImage(const std::string &img_path, float score,
                          bool highlight) {
  auto filename = std::filesystem::path(img_path).filename().string();
  auto file_ext = std::filesystem::path(img_path).extension().string();

  if (file_ext != ".png" && file_ext != ".jpg") {
    std::cerr << "Error: Unkown image file extension, only supports png and "
                 "jpg files."
              << std::endl;
  }
  if (highlight) {
    ofs_ << "<div class=\"column\" style=\"border: 5px solid green;\">"
         << std::endl;
  }
  else {
    ofs_ << "<div class=\"column\">" << std::endl;
  }
  ofs_ << "<h2> " << filename << " </h2> " << std::endl;
  ofs_ << "<img src=\"" << img_path << "\" />" << std::endl;
  ofs_ << std::setprecision(2) << std::fixed << "<p>score = " << score << "</p>"
       << std::endl;
  ofs_ << "</div>" << std::endl;
}
} // namespace html_writer