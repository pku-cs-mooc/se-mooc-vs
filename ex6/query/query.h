#ifndef QUERY_QUERY_H_
#define QUERY_QUERY_H_

#include <string>

#include "index/inverted_index_searcher.h"
#include "index/storage_reader.h"
#include "scorer/scorer.h"

namespace search {

// Query defines user's intention on search.
class Query {
 public:
  virtual ~Query() = default;

  // Creates a scorer to based on the searcher and storage reader.
  //
  // The caller will take the ownship of the returned scorer.
  virtual Scorer* NewScorer(InvertedIndexSearcher* searcher,
                            StorageReader* storage_reader) const = 0;

  virtual std::string DebugString() const = 0;
};

}  // namespace search

#endif  // QUERY_QUERY_H_
