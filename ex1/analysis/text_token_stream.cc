#include "analysis/text_token_stream.h"

#include <istream>
// TODO: Add headers you need.

#include "analysis/token.h"

namespace search {

TextTokenStream::TextTokenStream(std::istream* in) {
  // TODO: Implement constructor.
}

bool TextTokenStream::HasNext() const {
  // TODO: Implement this function.
  return false;
}

Token TextTokenStream::Next() {
  // TODO: Implement this function.
  std::string term;
  Normalize(&term);
  return Token(term, 0, 0);
}

}  // namespace search
