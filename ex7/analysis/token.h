#ifndef ANALYSIS_TOKEN_H_
#define ANALYSIS_TOKEN_H_

#include <string>
#include <utility>

namespace search {

class Token {
 public:
  Token() : Token("", 0, 0) {}
  Token(const std::string& term, int begin, int end)
      : term_(term), begin_(begin), end_(end) {}
  Token(std::string&& term, int begin, int end)
      : term_(std::move(term)), begin_(begin), end_(end) {}

  const std::string& term() const { return term_; }
  int begin() const { return begin_; }
  int end() const { return end_; }

  bool operator==(const Token& token) const {
    return term_ == token.term_ && begin_ == token.begin_ && end_ == token.end_;
  }

  bool operator!=(const Token& token) const { return !(*this == token); }

  std::string DebugString() const {
    return "<" + term_ + ":" + std::to_string(begin_) + "," +
           std::to_string(end_) + ">";
  }

 private:
  std::string term_;  // The normalized form.
  int begin_;         // Begin offset.
  int end_;           // End offset.
};

}  // namespace search

#endif  // ANALYSIS_TOKEN_H_
