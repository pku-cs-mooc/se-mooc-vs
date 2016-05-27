#ifndef QUERY_QUERY_PARSER_H_
#define QUERY_QUERY_PARSER_H_

#include <string>

#include "analysis/analyzer.h"
#include "query/query.h"
#include "query/query_manager.h"

namespace search {

// QueryParser parses string into structured query tree.
class QueryParser {
 public:
  QueryParser(const Analyzer& analyzer, QueryManager* query_manager)
      : analyzer_(analyzer), query_manager_(query_manager) {}

  // Creates a query by parsing str.
  //
  // It crashes, when it fails to parse.
  //
  // The query_manager will take the ownership of the returned query.
  Query* NewQuery(const std::string& str);

 private:
  const Analyzer& analyzer_;
  QueryManager* const query_manager_;
};

}  // namespace search

#endif  // QUERY_QUERY_PARSER_H_
