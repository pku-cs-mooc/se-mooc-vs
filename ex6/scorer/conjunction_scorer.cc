#include "scorer/conjunction_scorer.h"

#include <utility>
#include <vector>
// TODO: Add headers you need.

#include "scorer/scorer.h"
#include "util/logging.h"
// TODO: Add headers you need.

namespace search {

ConjunctionScorer::ConjunctionScorer(const std::vector<Scorer*>& scorers)
    : scorers_(scorers) {
  Init();
}

ConjunctionScorer::ConjunctionScorer(std::vector<Scorer*>&& scorers)
    : scorers_(std::move(scorers)) {
  Init();
}

void ConjunctionScorer::Init() {
  CHECK(scorers_.size() > 1)
      << "There should be at least 2 scorers in a conjunction scorer.";
  // TODO: Implement this function.
}

ConjunctionScorer::~ConjunctionScorer() {
  // TODO: Implement destructor.
}

int ConjunctionScorer::Next() {
  // TODO: Implement this function.
  doc_ = kDocExhausted;
  return kDocExhausted;
}

float ConjunctionScorer::score() {
  // TODO: Implement this function.
  return 0;
}

}  // namespace search
