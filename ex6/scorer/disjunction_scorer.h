#ifndef SCORER_DISJUNCTION_SCORER_H_
#define SCORER_DISJUNCTION_SCORER_H_

#include <vector>

#include "scorer/scorer.h"

namespace search {

// DisjunctionScorer iterates and scores documents that hit any one among
// sub-queries.
class DisjunctionScorer : public Scorer {
 public:
  // Constructor.
  //
  // - scorers are sub-queries' scorers. There should be at least 2 scorers.
  //   Should keep alive in this class.
  DisjunctionScorer(const std::vector<Scorer*>& scorers);
  DisjunctionScorer(std::vector<Scorer*>&& scorers);

  // Deletes all sub-scorers.
  ~DisjunctionScorer();

  int Next() override;
  float score() override;

 private:
  // Initializes DisjunctionScorer.
  void Init();

 private:
  std::vector<Scorer*> scorers_;  // ELEMENTS OWNED
};

}  // namespace search

#endif  // SCORER_DISJUNCTION_SCORER_H_
