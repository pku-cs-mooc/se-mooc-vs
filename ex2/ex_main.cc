#include <string>
#include <vector>

#include "index/storage_reader.h"
#include "index/storage_writer.h"
#include "util/logging.h"
#include "util/mem_io.h"

int main(int argc, char** argv) {
  std::vector<std::string> data = {"1 2 3 4", "2 3 ", "3,4"};

  search::util::MemIO mem_io;
  search::StorageWriter writer(&mem_io);
  for (const std::string& item : data) {
    writer.AddStorage(item);
  }
  writer.Close();

  search::StorageReader reader(&mem_io);
  for (int i = 0; i < reader.num_docs(); ++i) {
    LOG(INFO) << "data[" << i << "]: " << reader.Stored(i);
  }
  return 0;
}
