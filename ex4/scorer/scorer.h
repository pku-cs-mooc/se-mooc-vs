#ifndef SCORER_SCORER_H_
#define SCORER_SCORER_H_

#include <climits>

// A scorer is an iterator which iterates hit documents. It also scores the
// document when iterating.
class Scorer {
 public:
  // When all documents are iterated, it comes to a state of Document
  // Exhausted.
  static const int kDocExhausted = INT_MAX;

  virtual ~Scorer() = default;

  // Iterates to the next document.
  //
  // Returns the next doc_id. Should set the current score as unassigned at the
  // beginning of this function.
  //
  // Undefined, when doc() already returned kDocExhausted.
  virtual int Next() = 0;

  // Document id.
  //
  // When scorer is initialized, its corresponding document id is -1. When all
  // hit document are iterated, it returns kDocExhausted.
  int doc() const { return doc_; }

  // Score of the current document.
  //
  // Currently, we use tf-idf as our scoring function.
  //
  // Undefined, when doc() points at -1 or has already returned kDocExhausted.
  virtual float score() = 0;

  // Cost of this scorer.
  //
  // It's an estimated value which indicates how much it would cost to run this
  // iterator.
  //
  // For TermScorer, its cost is its document frequency.
  float cost() const { return cost_; }

  // Advances doc_ to the document whose id is greater than or equal to doc.
  //
  // Undefined, when doc_ is not less than doc, either when doc_ =
  // kDocExhausted.
  int Advance(int doc) {
    score_ = -1;  // Sets score_ as unassigned.
    do
      Next();
    while (doc_ < doc);
    return doc_;
  }

 protected:
  int doc_ = -1;  // Current iterating doc id.
  float score_;   // Score of current iterating doc.
  float cost_;
};

#endif  // SCORER_SCORER_H_
