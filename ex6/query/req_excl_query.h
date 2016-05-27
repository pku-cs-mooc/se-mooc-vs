#ifndef QUERY_REQ_EXCL_QUERY_H_
#define QUERY_REQ_EXCL_QUERY_H_

#include <string>
#include <vector>

#include "index/inverted_index_searcher.h"
#include "index/storage_reader.h"
#include "query/query.h"
#include "scorer/req_excl_scorer.h"
#include "scorer/scorer.h"

namespace search {

// Queries documents that hit the required query while not hit the excluded
// query.
class ReqExclQuery : public Query {
 public:
  // Constructor.
  //
  // requried and excluded should keep alive in this class.
  ReqExclQuery(const Query* required, const Query* excluded)
      : required_(required), excluded_(excluded) {}

  Scorer* NewScorer(InvertedIndexSearcher* searcher,
                    StorageReader* storage_reader) const override {
    return new ReqExclScorer(required_->NewScorer(searcher, storage_reader),
                             excluded_->NewScorer(searcher, storage_reader));
  }

  std::string DebugString() const override {
    return "(" + required_->DebugString() + " - " + excluded_->DebugString() +
           ")";
  }

 private:
  const Query* required_;
  const Query* excluded_;
};

}  // namespace search

#endif  // QUERY_REQ_EXCL_QUERY_H_
