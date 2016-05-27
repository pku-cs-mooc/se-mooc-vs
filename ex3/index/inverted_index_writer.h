#ifndef INDEX_INVERTED_INDEX_WRITER_H_
#define INDEX_INVERTED_INDEX_WRITER_H_

#include <string>
// TODO: Add headers you need.

#include "analysis/analyzer.h"
#include "index/document.h"
#include "util/io.h"
// TODO: Add headers you need.

namespace search {

class InvertedIndexWriter {
 public:
  // InvertedIndexWriter will take the ownship of all ostreams and inv_index.
  //
  // - analyzer is tokenizer generator.
  // - io manages ostreams.
  // - id specifies which inverted index will this class write.
  //
  // analyzer and io should keep alive in this class.
  InvertedIndexWriter(const Analyzer& analyzer, util::IO* io, int id) {
    // TODO: Implement constructor.
  }

  // Firstly, writes inverted index to ostreams.
  // Secondly, closes and deletes all ostreams and inv_index.
  ~InvertedIndexWriter();

  // Adds document's text into inverted index and writes document's stored data
  // into storage index.
  //
  // This function can only be called once for each doc, and the doc_id should
  // be bigger than the previous added document.
  //
  // If doc doesn't contain text, it crashes.
  void AddDocument(Document* doc);

  // Writes inverted index and closes term_out_ and posting_out_.
  //
  // After called, any document can not be added successfully.
  void WriteAndClose();

  int num_terms() const {
    // TODO: Implement this function.
    return 0;
  }

  std::string DebugString() const;

 private:
  // TODO: Add members you need.
};

}  // namespace search

#endif  // INDEX_INVERTED_INDEX_WRITER_H_
