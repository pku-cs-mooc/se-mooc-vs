#ifndef UTIL_IO_H_
#define UTIL_IO_H_

#include <iostream>

namespace search {
namespace util {

// IO manages the creation and close of all iostreams.
//
// The caller will take the ownership of all created iostreams by this class.
class IO {
 public:
  IO() : IO(kDefaultTermSize) {}
  IO(int term_size) : kTermSize(term_size) {}
  virtual ~IO() = default;

  virtual std::istream* NewTermIn(int id) const = 0;
  virtual void CloseTermIn(std::istream* in) const = 0;
  virtual std::ostream* NewTermOut(int id) const = 0;
  virtual void CloseTermOut(std::ostream* out) = 0;

  virtual std::istream* NewPostingIn(int id) const = 0;
  virtual void ClosePostingIn(std::istream* in) const = 0;
  virtual std::ostream* NewPostingOut(int id) const = 0;
  virtual void ClosePostingOut(std::ostream* out) = 0;

  virtual std::istream* NewStorageIndexIn() const = 0;
  virtual void CloseStorageIndexIn(std::istream* in) const = 0;
  virtual std::ostream* NewStorageIndexOut() const = 0;
  virtual void CloseStorageIndexOut(std::ostream* out) = 0;

  virtual std::istream* NewStorageIn() const = 0;
  virtual void CloseStorageIn(std::istream* in) const = 0;
  virtual std::ostream* NewStorageOut() const = 0;
  virtual void CloseStorageOut(std::ostream* out) = 0;

  virtual bool HasIdForIn(int id) const = 0;

  // As we store fixed padding terms in the term table, we need to know the
  // term's storage size.
  static const int kDefaultTermSize = 100;
  const int kTermSize;
};

}  // namespace util
}  // namespace search

#endif  // UTIL_IO_H_
