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

  int df() const { return df_; }
  int tf();

 private:
  // in:begin specifies the beginning of the posting list.
  std::istream* const in_;
  int begin_;

  int df_;  // Document frequency.
  int tf_;  // Term frequency.

  // Provides interface to access data that help scoring.
  StorageReader* const storage_reader_ = nullptr;

  // Current posting list offset, which specifies the beginning offset of the
  // next posting in 'in'.
  //
  // Needs to reset 'in' to this offset, as 'in' is shared by many classes.
  int offset_;

  int count_ = 0;  // Number of documents already iterated.
};

}  // namespace search

#endif  // SCORER_TERM_SCORER_H_
