#ifndef INDEX_INVERTED_INDEX_SEARCHER_H_
#define INDEX_INVERTED_INDEX_SEARCHER_H_

#include <string>
// TODO: Add headers you need.

#include "index/storage_reader.h"
#include "scorer/term_scorer.h"
#include "util/io.h"

namespace search {

class InvertedIndexSearcher {
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
  int num_terms() const {
    // TODO: Implement this function.
    return 0;
  }

  std::string DebugString();

 private:
  // TODO: Add members you need.
};

}  // namespace search

#endif  // INDEX_INVERTED_INDEX_SEARCHER_H_
