#include "image_browser.hpp"
#include "html_writer.hpp"
#include <string>

namespace image_browser {

void AddFullRow(const ImageRow &row, bool first_row) {
  html_writer::OpenRow();

  bool is_first_img = first_row;
  for (const auto &sc_img : row) {
    const auto [img_path, img_sc] = sc_img;

    html_writer::AddImage(img_path, img_sc, is_first_img);
    if (is_first_img){ is_first_img = false;}
  }

  html_writer::CloseRow();
}

void CreateImageBrowser(const std::string &title, const std::string &stylesheet,
                        const std::vector<ImageRow> &rows) {
  html_writer::OpenDocument();
  html_writer::AddTitle(title);
  html_writer::AddCSSStyle(stylesheet);
  html_writer::OpenBody();

  bool is_first_row = true;
  for (const auto &img_raw : rows) {
    AddFullRow(img_raw, is_first_row);
    if (is_first_row) { is_first_row = false; }
  }

  html_writer::CloseBody();
  html_writer::CloseDocument();
}
}