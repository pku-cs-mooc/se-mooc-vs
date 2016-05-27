#ifndef ANALYSIS_TEXT_TOKEN_STREAM_H_
#define ANALYSIS_TEXT_TOKEN_STREAM_H_

#include <istream>

#include "analysis/token.h"
#include "analysis/token_stream.h"

namespace search {

class TextTokenStream : public TokenStream {
 public:
  // Constructor.
  //
  // - in should keep alive in this class.
  TextTokenStream(std::istream* in);

  bool HasNext() const override;

  Token Next() override;

 private:
  // TODO: Add members you need.
};

}  // namespace search

#endif  // ANALYSIS_TEXT_TOKEN_STREAM_H_
