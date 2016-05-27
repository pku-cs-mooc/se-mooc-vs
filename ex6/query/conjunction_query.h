#ifndef QUERY_CONJUNCTION_QUERY_H_
#define QUERY_CONJUNCTION_QUERY_H_

#include <string>
#include <utility>
#include <vector>

#include "index/inverted_index_searcher.h"
#include "index/storage_reader.h"
#include "query/query.h"
#include "scorer/conjunction_scorer.h"
#include "scorer/scorer.h"

namespace search {

// Queries sub-queries' conjunction.
class ConjunctionQuery : public Query {
 public:
  // Constructor.
  //
  // queries should keep alive in this class.
  ConjunctionQuery(const std::vector<const Query*>& queries)
      : queries_(queries) {}

  ConjunctionQuery(std::vector<const Query*>&& queries)
      : queries_(std::move(queries)) {}

  void AddQuery(const Query* query) { queries_.push_back(query); }

  Scorer* NewScorer(InvertedIndexSearcher* searcher,
                    StorageReader* storage_reader) const override {
    std::vector<Scorer*> scorers;
    for (const Query* query : queries_) {
      scorers.push_back(query->NewScorer(searcher, storage_reader));
    }
    return new ConjunctionScorer(std::move(scorers));
  }

  std::string DebugString() const override {
    std::string ans = "(";
    for (const Query* query : queries_) {
      ans += query->DebugString() + " & ";
    }
    if (ans.back() == ' ') ans.resize(ans.size() - 3);
    ans += ")";
    return ans;
  }

 private:
  std::vector<const Query*> queries_;
};

}  // namespace search

#endif  // QUERY_CONJUNCTION_QUERY_H_
