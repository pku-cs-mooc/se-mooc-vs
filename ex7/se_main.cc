#include "analysis/analyzer.h"
#include "query/query.h"
#include "query/query_manager.h"
#include "query/query_parser.h"
#include "util/logging.h"

int main(int argc, char** argv) {
  search::Analyzer analyzer;
  search::QueryManager query_manager;
  search::QueryParser parser(analyzer, &query_manager);
  search::Query* query = parser.NewQuery("(a|b  -(c&d))  ");
  if (query) {
    LOG(INFO) << query->DebugString();
  }
  return 0;
}
