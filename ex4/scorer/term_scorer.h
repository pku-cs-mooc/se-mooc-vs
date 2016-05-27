#ifndef SCORER_TERM_SCORER_H_
#define SCORER_TERM_SCORER_H_

#include <istream>

#include "index/storage_reader.h"
#include "scorer/scorer.h"

namespace search {

// TermScorer iterates and scores documents that hit the term.
class TermScorer : public Scorer {
 public:
  // Constructor.
  //
  // - df is the term's document frequency.
  // - in is an stream contains this term's posting list.
  // - begin is the beginning offset of the posting list in 'in'.
  // - storage_reader provides interface to access some storage data that help
  //   scoring. If it is null, every score will be set as 0.
  //
  // in and storage_reader should keep alive in this class.
  TermScorer(int df, std::istream* in, int begin,
             StorageReader* storage_reader);

  int Next() override;
  float score() override;

  int df() const {
    // TODO: Implement this function.
    return 0;
  }
  int tf();

 private:
  // TODO: Add members you need.
};

}  // namespace search

#endif  // SCORER_TERM_SCORER_H_
