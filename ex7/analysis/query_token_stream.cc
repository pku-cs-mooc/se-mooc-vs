#include "analysis/query_token_stream.h"

#include <istream>
// TODO: Add headers you need.

#include "analysis/token.h"

namespace search {
namespace {

bool IsOperator(char c) {
  return c == '(' || c == ')' || c == '&' || c == '|' || c == '-';
}

}  // namespace

QueryTokenStream::QueryTokenStream(std::istream* in) {
  // TODO: Implement constructor.
}

bool QueryTokenStream::HasNext() const {
  // TODO: Implement this function.
  return false;
}

Token QueryTokenStream::Next() {
  // TODO: Implement this function.
  return Token("", 0, 0);
}

}  // namespace search
