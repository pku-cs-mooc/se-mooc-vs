#ifndef QUERY_TERM_QUERY_H_
#define QUERY_TERM_QUERY_H_

#include <string>
#include <utility>

#include "index/inverted_index_searcher.h"
#include "index/storage_reader.h"
#include "query/query.h"
#include "scorer/scorer.h"

namespace search {

// Queries a term.
class TermQuery : public Query {
 public:
  TermQuery(const std::string& term) : term_(term) {}
  TermQuery(std::string&& term) : term_(std::move(term)) {}

  Scorer* NewScorer(InvertedIndexSearcher* searcher,
                    StorageReader* storage_reader) const override {
    return searcher->NewTermScorer(term_, storage_reader);
  }

  std::string DebugString() const override { return term_; }

 private:
  std::string term_;  // The term to be queried.
};

}  // namespace search

#endif  // QUERY_TERM_QUERY_H_
