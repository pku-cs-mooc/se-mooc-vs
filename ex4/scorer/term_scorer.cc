#include "scorer/term_scorer.h"

#include <istream>

#include "index/storage_reader.h"

namespace search {

TermScorer::TermScorer(int df, std::istream* in, int begin,
                       StorageReader* storage_reader) {
  if (in == nullptr || storage_reader == nullptr) {
    // Mark this scorer as exhausted
    doc_ = kDocExhausted;
  } else {
    // TODO: Implement constructor.
  }
}

int TermScorer::Next() {
  // TODO: Implement this function.
  doc_ = kDocExhausted;
  return kDocExhausted;
}

int TermScorer::tf() {
  // Implement this function.
  return 0;
}

float TermScorer::score() {
  // TODO: Implement this function.
  return 0;
}

}  // namespace search
