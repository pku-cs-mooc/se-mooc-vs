#ifndef INDEX_INDEX_SEARCHER_H_
#define INDEX_INDEX_SEARCHER_H_

#include <climits>
#include <string>
#include <vector>

#include "index/inverted_index_searcher.h"
#include "index/score_doc.h"
#include "index/storage_reader.h"
#include "query/query.h"
#include "util/io.h"

namespace search {

// IndexSearcher coordinates to search from several inverted indices and storage
// index.
class IndexSearcher {
 private:
  // storage_begin
  using StorageEntry = int;

 public:
  // Constructor.
  //
  // - io manages istreams in sub-searchers and readers, and should keep alive
  //   in this class.
  IndexSearcher(util::IO* io);

  // Closes and deletes all inverted index searchers and storage reader.
  ~IndexSearcher();

  // Closes all inverted index searchers and storage reader.
  //
  // This function can be both called and never called, as the destructor will
  // call it. Should not do further operations, after this function is called.
  void Close();

  // Searches the query to get all hit scored documents which are sorted in
  // score decreasing order.
  std::vector<ScoreDoc> Search(const Query& query) {
    return Search(query, INT_MAX);
  }

  // Searches the query to get top-n hit scored documents which are sorted in
  // score decreasing order.
  std::vector<ScoreDoc> Search(const Query& query, int n);

  // Gets the stored data the document whose id is 'doc'.
  std::string Stored(int doc) { return storage_reader_->Stored(doc); }

 private:
  // Elements in inv_index_searcher_vec_ in it reads pieces of posting data.
  std::vector<InvertedIndexSearcher*>
      inv_index_searcher_vec_;  // ELEMENTS OWNED

  // storage_reader_ reads storage data.
  StorageReader* const storage_reader_;  // OWNED
};

}  // namespace search

#endif  // INDEX_INDEX_SEARCHER_H_
