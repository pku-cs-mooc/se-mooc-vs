#ifndef ANALYSIS_TOKEN_STREAM_H_
#define ANALYSIS_TOKEN_STREAM_H_

#include <string>

#include "analysis/token.h"

namespace search {

class TokenStream {
 public:
  virtual ~TokenStream() = default;

  // Judges whether it has next token.
  virtual bool HasNext() const = 0;

  // Gets the next token. Should make sure HasNext before calling.
  //
  // Supposed that we have tokens "<a> <b>", this function returns <b> on its
  // second call.
  virtual Token Next() = 0;

 protected:
  // Normalizes str.
  virtual void Normalize(std::string* str) const;
};

}  // namespace search

#endif  // ANALYSIS_TOKEN_STREAM_H_
