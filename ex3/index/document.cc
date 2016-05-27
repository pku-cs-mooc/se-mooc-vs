#include "index/document.h"

#include <fstream>
#include <sstream>
#include <string>

#include "analysis/analyzer.h"
#include "analysis/token_stream.h"
#include "util/logging.h"

namespace search {

Document::~Document() {
  if (std::ifstream* fin = dynamic_cast<std::ifstream*>(text_in_)) {
    fin->close();
  }
  if (text_in_) delete text_in_;
}

void Document::set_text(const std::string& text) {
  check_set_text();
  text_in_ = new std::istringstream(text);
}

void Document::set_text(std::istream* text) {
  check_set_text();
  text_in_ = text;
}

void Document::set_doc_id(int doc_id) {
  CHECK(doc_id_ < 0) << "doc_id has been set before.";
  doc_id_ = doc_id;
}

void Document::check_set_text() const {
  CHECK(text_in_ == nullptr) << "set_text can only be called once.";
}

TokenStream* Document::NewTokenStream(const Analyzer& analyzer) {
  return analyzer.NewTextTokenStream(text_in_);
}

}  // namespace search
