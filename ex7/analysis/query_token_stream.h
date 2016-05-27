#ifndef ANALYSIS_QUERY_TOKEN_STREAM_H_
#define ANALYSIS_QUERY_TOKEN_STREAM_H_

#include <istream>

#include "analysis/token.h"
#include "analysis/token_stream.h"

namespace search {

class QueryTokenStream : public TokenStream {
 public:
  // Constructor.
  //
  // - in should keep alive in this class.
  QueryTokenStream(std::istream* in);

  bool HasNext() const override;

  Token Next() override;

 private:
  // TODO: Add members you need.
};

}  // namespace search

#endif  // ANALYSIS_QUERY_TOKEN_STREAM_H_
