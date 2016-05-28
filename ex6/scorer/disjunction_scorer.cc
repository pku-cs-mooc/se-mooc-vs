#include "scorer/disjunction_scorer.h"

#include <utility>
#include <vector>
// TODO: Add headers you need.

#include "scorer/scorer.h"
#include "util/logging.h"

namespace search {

DisjunctionScorer::DisjunctionScorer(const std::vector<Scorer*>& scorers)
    : scorers_(scorers) {
  Init();
}

DisjunctionScorer::DisjunctionScorer(std::vector<Scorer*>&& scorers)
    : scorers_(std::move(scorers)) {
  Init();
}

void DisjunctionScorer::Init() {
  CHECK(scorers_.size() > 1)
      << "There should be at least 2 scorers in a disjunction scorer.";
  // TODO: Implement this function.
}

DisjunctionScorer::~DisjunctionScorer() {
  // TODO: Implement destructor.
}

int DisjunctionScorer::Next() {
  // TODO: Implement this function.
  doc_ = kDocExhausted;
  return kDocExhausted;
}

float DisjunctionScorer::score() {
  // TODO: Implement this function.
  return 0;
}

}  // namespace search
