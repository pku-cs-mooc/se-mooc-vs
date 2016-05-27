#ifndef SCORER_REQ_EXCL_SCORER_H_
#define SCORER_REQ_EXCL_SCORER_H_

#include "scorer/scorer.h"

namespace search {

// ReqExclScorer iterates and scores documents that hit the required query,
// while not hit the excluded query.
class ReqExclScorer : public Scorer {
 public:
  // Constructor.
  //
  // - required iterates documents that should appear.
  // - required iterates documents that must not appear.
  //
  // required and excluded should keep alive in this class.
  ReqExclScorer(Scorer* required, Scorer* excluded);

  // Deletes all sub-scorers.
  ~ReqExclScorer();

  int Next() override;
  float score() override;

 private:
  Scorer* required_;  // OWNED
  Scorer* excluded_;  // OWNED
};

}  // namespace search

#endif  // SCORER_REQ_EXCL_SCORER_H_
