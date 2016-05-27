#ifndef INDEX_STORAGE_WRITER_H_
#define INDEX_STORAGE_WRITER_H_

#include <ostream>
#include <string>

#include "util/io.h"

namespace search {

// StorageWriter writes and indexes storage data.
class StorageWriter {
 public:
  // Constructor.
  //
  // - io manages ostreams, and should keep alive in this class.
  StorageWriter(util::IO* io)
      : io_(io),
        storage_index_out_(io->NewStorageIndexOut()),
        storage_out_(io->NewStorageOut()) {}

  // Closes and deletes ostreams.
  ~StorageWriter();

  // Closes ostreams.
  //
  // This function can be both called and never called, as the destructor will
  // call it. Should not add any document, after this function is called.
  void Close();

  // Adds stored data into the storage ostreams.
  void AddStorage(const std::string& stored);

 private:
  util::IO* const io_;

  // storage_index_out_ indexes storage data offset in storage_out_.
  std::ostream* const storage_index_out_;  // OWNED
  // storage_out_ stores document data.
  std::ostream* const storage_out_;  // OWNED
};

}  // namespace search

#endif  // INDEX_STORAGE_WRITER_H_
