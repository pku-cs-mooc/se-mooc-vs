#ifndef QUERY_QUERY_MANAGER_H_
#define QUERY_QUERY_MANAGER_H_

#include <string>
#include <vector>

#include "query/query.h"

namespace search {

// QueryManager manages queries' construction and destruction.
//
// By applying this class, the caller does not need to care about the memory
// for queries.
//
// The caller does not take the ownership of any created query by this class.
//
// This class is not thread-safe, as the function push_back of vector is not
// thread-safe.
class QueryManager {
 public:
  ~QueryManager();

  Query* NewTermQuery(const std::string& term);
  Query* NewTermQuery(std::string&& term);

  Query* NewConjunctionQuery(const std::vector<const Query*>& queries);
  Query* NewConjunctionQuery(std::vector<const Query*>&& queries);

  Query* NewDisjunctionQuery(const std::vector<const Query*>& queries);

  Query* NewReqExclQuery(const Query* required, const Query* excluded);

 private:
  std::vector<const Query*> queries_;  // ELEMENTS OWNED
};

}  // search

#endif  // QUERY_QUERY_MANAGER_H_
