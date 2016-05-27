#include "index/inverted_index_searcher.h"

#include <string>

#include "index/storage_reader.h"
#include "scorer/term_scorer.h"
#include "util/logging.h"
// TODO: Add headers you need.

namespace search {

InvertedIndexSearcher::InvertedIndexSearcher(util::IO* io, int id) {
  // TODO: Implement constructor.
}

InvertedIndexSearcher::~InvertedIndexSearcher() {
  // TODO: Implement destructor.
}

void InvertedIndexSearcher::Close() {
  // TODO: Implement this function.
}

int InvertedIndexSearcher::FindTerm(const std::string& term) {
  // TODO: Implement this function.
  return 0;
}

std::string InvertedIndexSearcher::GetTerm(int id) {
  CHECK(0 <= id && id < num_terms()) << "term_id " << id << " is out of range.";

  // TODO: Implement this function.
  return "";
}

TermScorer* InvertedIndexSearcher::NewTermScorer(
    const std::string& term, StorageReader* storage_reader) {
  // TODO: Implement this function.
  return new TermScorer(0, nullptr, 0, nullptr);
}

std::string InvertedIndexSearcher::DebugString() {
  // TODO: Implement this function.
  return "";
}

}  // namespace search
