#ifndef INDEX_INVERTED_INDEX_SEARCHER_H_
#define INDEX_INVERTED_INDEX_SEARCHER_H_

#include <istream>
#include <string>
#include <tuple>

#include "index/storage_reader.h"
#include "scorer/term_scorer.h"
#include "util/io.h"

namespace search {

class InvertedIndexSearcher {
 private:
  // posting_begin, df
  using TermEntry = std::tuple<int, int>;

 public:
  // Constructor.
  //
  // - io manages istreams, and should keep alive in this class.
  // - id specifies which inverted index should be read and used in this class.
  InvertedIndexSearcher(util::IO* io, int id);

  // Closes all istreams and deletes them.
  ~InvertedIndexSearcher();

  // Closes all istreams.
  //
  // This function can be both called and never called, as the destructor will
  // call it. Should not do further operations, after this function is called.
  void Close();

  // Finds a term's id.
  //
  // If the term is not indexed, returns -1.
  int FindTerm(const std::string& term);

  // Gets the term whose id is 'id'.
  //
  // If the term id is out of range, it crashes.
  std::string GetTerm(int id);

  // Creates a scorer who iterates term's hit documents.
  //
  // - term is what we want to search.
  // - storage_reader provides interface to access data that help scoring.
  //
  // The caller will take the ownship of the returnned scorer.
  TermScorer* NewTermScorer(const std::string& term,
                            StorageReader* storage_reader);

  // Number of terms in this inverted index.
  int num_terms() const { return num_terms_; }

  std::string DebugString();

 private:
  // Gets the inverted index entry of term.
  //
  // - id is the term id.
  TermEntry GetTermEntry(int id);

  // Creates a scorer who iterates term's hit documents.
  //
  // - id is the term's id.
  // - storage_reader provides interface to access data that help scoring.
  //
  // The caller will take the ownership of the returned scorer.
  TermScorer* NewTermScorer(int id, StorageReader* storage_reader);

 private:
  util::IO* const io_;

  int num_terms_;  // ASSIGNED ONCE

  // term_in_ reads the term table.
  std::istream* const term_in_;  // OWNED
  // posting_in_ reads posting lists.
  std::istream* const posting_in_;  // OWNED
};

}  // namespace search

#endif  // INDEX_INVERTED_INDEX_SEARCHER_H_
