#ifndef UTIL_MEM_IO_H_
#define UTIL_MEM_IO_H_

#include <sstream>
#include <string>

#include "util/io.h"
#include "util/logging.h"

namespace search {
namespace util {

// IO for memory.
class MemIO : public IO {
 public:
  MemIO() = default;
  MemIO(int term_size) : IO(term_size) {}

  // Term.
  std::istream* NewTermIn(int id) const override {
    return HasIdForIn(id) ? new std::istringstream(term_) : nullptr;
  }

  void CloseTermIn(std::istream* in) const override {}

  std::ostream* NewTermOut(int id) const override {
    CheckIdForOut(id);
    return new std::ostringstream();
  }

  void CloseTermOut(std::ostream* out) override {
    if (std::ostringstream* sout = dynamic_cast<std::ostringstream*>(out)) {
      term_ = sout->str();
    }
  }

  // Posting.
  std::istream* NewPostingIn(int id) const override {
    return HasIdForIn(id) ? new std::istringstream(posting_) : nullptr;
  }

  void ClosePostingIn(std::istream* in) const override {}

  std::ostream* NewPostingOut(int id) const override {
    CheckIdForOut(id);
    return new std::ostringstream();
  }

  void ClosePostingOut(std::ostream* out) override {
    if (std::ostringstream* sout = dynamic_cast<std::ostringstream*>(out)) {
      posting_ = sout->str();
    }
  }

  // Storage Index.
  std::istream* NewStorageIndexIn() const override {
    return new std::istringstream(storage_index_);
  }

  void CloseStorageIndexIn(std::istream* in) const override {}

  std::ostream* NewStorageIndexOut() const override {
    return new std::ostringstream();
  }

  void CloseStorageIndexOut(std::ostream* out) override {
    if (std::ostringstream* sout = dynamic_cast<std::ostringstream*>(out)) {
      storage_index_ = sout->str();
    }
  }

  // Storage.
  std::istream* NewStorageIn() const override {
    return new std::istringstream(storage_);
  }

  void CloseStorageIn(std::istream* in) const override {}

  std::ostream* NewStorageOut() const override {
    return new std::ostringstream();
  }

  void CloseStorageOut(std::ostream* out) override {
    if (std::ostringstream* sout = dynamic_cast<std::ostringstream*>(out)) {
      storage_ = sout->str();
    }
  }

  bool HasIdForIn(int id) const override { return id == 0; }

  // Data.
  const std::string& term() const { return term_; }
  const std::string& posting() const { return posting_; }
  const std::string& storage_index() const { return storage_index_; }
  const std::string& storage() const { return storage_; }

 private:
  void CheckIdForOut(int id) const {
    CHECK(id == 0) << "Unimplement for id != 0.";
  }

 private:
  std::string term_;
  std::string posting_;
  std::string storage_index_;
  std::string storage_;
};

}  // namespace util
}  // namespace search

#endif  // UTIL_IO_H_
