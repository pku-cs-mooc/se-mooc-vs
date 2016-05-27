#include "index/inverted_index_writer.h"

#include <string>
// TODO: Add headers you need.

#include "index/document.h"
#include "util/logging.h"
// TODO: Add headers you need.

namespace search {

InvertedIndexWriter::~InvertedIndexWriter() {
  // TODO: Implement destructor.
}

void InvertedIndexWriter::AddDocument(Document* doc) {
  CHECK(doc->text()) << "Document is in lack of text.";

  // TODO: Implement this function.
}

void InvertedIndexWriter::WriteAndClose() {
  // TODO: Writes inverted index to term_out_ and posting_out_.
}

std::string InvertedIndexWriter::DebugString() const {
  // TODO: Implement this function.
  return "";
}

}  // namespace search
