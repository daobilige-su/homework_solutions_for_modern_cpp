#include "image_browser.hpp"

namespace image_browser {

ImageBrowser::ImageBrowser(const std::string& output_file) {
  output_file_path_ = output_file;
  html_writer_ = html_writer::HtmlWriter(output_file_path_);
}

void ImageBrowser::AddFullRow(const ImageRow &row, bool first_row) {
  html_writer_.OpenRow();

  bool is_first_img = first_row;
  for (const auto &sc_img : row) {
    const auto [img_path, img_sc] = sc_img;
    if (img_path.empty()) {
      continue;
    }

    html_writer_.AddImage(img_path, img_sc, is_first_img);
    if (is_first_img){ is_first_img = false;}
  }

  html_writer_.CloseRow();
}

void ImageBrowser::CreateImageBrowser(const std::string &title,
                                    const std::string &stylesheet,
                                    const std::vector<ImageRow> &rows) {
  html_writer_.OpenDocument();
  html_writer_.AddTitle(title);
  html_writer_.AddCSSStyle(stylesheet);
  html_writer_.OpenBody();

  bool is_first_row = true;
  for (const auto &img_raw : rows) {
    AddFullRow(img_raw, is_first_row);
    if (is_first_row) { is_first_row = false; }
  }

  html_writer_.CloseBody();
  html_writer_.CloseDocument();
}
}