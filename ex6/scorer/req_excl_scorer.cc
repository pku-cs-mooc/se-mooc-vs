#include "scorer/req_excl_scorer.h"

#include "scorer/scorer.h"

namespace search {

ReqExclScorer::ReqExclScorer(Scorer* required, Scorer* excluded) {
  // TODO: Implement constructor.
}

ReqExclScorer::~ReqExclScorer() {
  // TODO: Implement destructor.
}

int ReqExclScorer::Next() {
  // TODO: Implement this function.
  doc_ = kDocExhausted;
  return kDocExhausted;
}

float ReqExclScorer::score() {
  // TODO: Implement this function.
  return 0;
}

}  // namespace search
