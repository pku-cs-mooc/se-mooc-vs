#ifndef ANALYSIS_ANALYZER_H_
#define ANALYSIS_ANALYZER_H_

#include <istream>

#include "analysis/token_stream.h"

namespace search {

class Analyzer {
 public:
  virtual ~Analyzer() = default;

  // Creates a TextTokenStream on an istream.
  //
  // The caller will take the ownership of the returned TextTokenStream.
  virtual TokenStream* NewTextTokenStream(std::istream* in) const;

  // Creates a QueryTokenStream on an istream.
  //
  // The caller will take the ownership of the returned QueryTokenStream.
  virtual TokenStream* NewQueryTokenStream(std::istream* in) const;
};

}  // namespace search

#endif  // ANALYSIS_ANALYZER_H_
