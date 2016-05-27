#ifndef SCORER_CONJUNCTION_SCORER_H_
#define SCORER_CONJUNCTION_SCORER_H_

#include <vector>

#include "scorer/scorer.h"

namespace search {

// ConjunctionScorer iterates and scores documents that hit all sub-queries.
class ConjunctionScorer : public Scorer {
 public:
  // Constructor.
  //
  // - scorers are sub-queries' scorers. There should be at least 2 scorers.
  //   Should keep alive in this class.
  ConjunctionScorer(const std::vector<Scorer*>& scorers);
  ConjunctionScorer(std::vector<Scorer*>&& scorers);

  // Deletes all sub-scorers.
  ~ConjunctionScorer();

  int Next() override;
  float score() override;

 private:
  // Initializes ConjunctionScorer.
  void Init();

 private:
  std::vector<Scorer*> scorers_;  // ELEMENTS OWNED
};

}  // namespace search

#endif  // SCORER_CONJUNCTION_SCORER_H_
