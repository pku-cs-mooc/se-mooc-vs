#ifndef INDEX_STORAGE_READER_H_
#define INDEX_STORAGE_READER_H_

#include <istream>
#include <string>

#include "util/io.h"

namespace search {

// StorageReader reads storage data.
class StorageReader {
 private:
  // storage_begin
  using StorageEntry = int;

 public:
  // Constructor.
  //
  // - io manages istreams, and should keep alive in this class.
  StorageReader(util::IO* io);

  // Closes and deletes istreams.
  virtual ~StorageReader();

  // Closes istreams.
  //
  // This function can be both called and never called, as the destructor will
  // call it. Should not do further operations, after this function is called.
  void Close();

  // Gets the stored data the document whose id is 'doc'.
  //
  // If doc is out of range, it crashes.
  std::string Stored(int doc);

  // Number of documents.
  virtual int num_docs() const { return num_docs_; }

 private:
  util::IO* const io_;

  int num_docs_;  // ASSIGNED ONCE

  // storage_index_in_ reades storage data's offset in storage_out_.
  std::istream* const storage_index_in_;  // OWNED
  // storage_in_ reads storage data.
  std::istream* const storage_in_;  // OWNED
};

}  // namespace search

#endif  // INDEX_STORAGE_READER_H_
