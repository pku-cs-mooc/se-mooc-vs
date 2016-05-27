#include "index/storage_reader.h"

#include <string>

#include "util/io.h"
#include "util/logging.h"

namespace search {

	StorageReader::StorageReader(util::IO* io) {
		// TODO: Implement this function.
	}

	StorageReader::~StorageReader() {
		// TODO: Implement this function.
	}

	void StorageReader::Close() {
		// TODO: Implement this function.
	}

	std::string StorageReader::Stored(int doc) {
		CHECK(0 <= doc && doc < num_docs()) << "doc " << doc << " is out of range.";
		// TODO: Implement this function.
		return "";
	}

}  // namespace search
