#ifndef INDEX_INVERTED_INDEX_WRITER_H_
#define INDEX_INVERTED_INDEX_WRITER_H_

#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "analysis/analyzer.h"
#include "index/document.h"
#include "index/posting.h"
#include "util/io.h"

namespace search {

class InvertedIndexWriter {
 private:
  using InvertedIndex = std::unordered_map<std::string, std::vector<Posting>>;

 public:
  // InvertedIndexWriter will take the ownship of all ostreams and inv_index.
  //
  // - analyzer is tokenizer generator.
  // - io manages ostreams.
  // - id specifies which inverted index will this class write.
  //
  // analyzer and io should keep alive in this class.
  InvertedIndexWriter(const Analyzer& analyzer, util::IO* io, int id)
      : analyzer_(analyzer),
        io_(io),
        term_out_(io->NewTermOut(id)),
        posting_out_(io->NewPostingOut(id)) {}

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

  int num_terms() const { return inv_index_->size(); }

  std::string DebugString() const;

 private:
  static bool LessInvertedIndexIterator(InvertedIndex::const_iterator it1,
                                        InvertedIndex::const_iterator it2);

 private:
  const Analyzer& analyzer_;
  util::IO* const io_;
  bool has_written_ = false;  // Whether the inverted index has been written.

  // term_out_ ouputs the term table.
  std::ostream* const term_out_;  // OWNED
  // posting_out_ outputs posting lists.
  std::ostream* const posting_out_;  // OWNED

  InvertedIndex* const inv_index_ = new InvertedIndex;  // OWNED
};

}  // namespace search

#endif  // INDEX_INVERTED_INDEX_WRITER_H_
