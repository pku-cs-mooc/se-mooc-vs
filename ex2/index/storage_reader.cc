#include "index/storage_reader.h"

#include <string>

#include "util/io.h"
#include "util/logging.h"

namespace search {

	StorageReader::StorageReader(util::IO* io) {
		// TODO: Implement this function.
		this->io = io;
		this->indexReader = io->NewStorageIndexIn();
		this->storageReader = io->NewStorageIn();
	}

	StorageReader::~StorageReader() {
		// TODO: Implement this function.
		Close();
	}

	void StorageReader::Close() {
		// TODO: Implement this function.
		if (indexReader) {
			io->CloseStorageIndexIn(indexReader);
			indexReader = nullptr;
		}
		if (storageReader) {
			io->CloseStorageIn(storageReader);
			storageReader = nullptr;
		}
	}

	std::string StorageReader::Stored(int doc) {
		CHECK(0 <= doc && doc < num_docs()) << "doc " << doc << " is out of range.";
		// TODO: Implement this function.
		int startIndex = getIndex(doc);
		int endIndex = getIndex(doc + 1);
		storageReader->seekg(startIndex, storageReader->beg);
		char* buffer = new char[endIndex - startIndex + 1];
		storageReader->read(buffer, endIndex - startIndex);
		buffer[endIndex - startIndex] = '\0';
		std::string result(buffer);
		delete[] buffer;
		return result;
	}

	int StorageReader::getIndex(int doc) {
		int index = 0;
		if (doc == num_docs()) {
			std::streampos initialPosition = storageReader->tellg();
			storageReader->seekg(0, storageReader->end);
			index = storageReader->tellg();
			storageReader->seekg(initialPosition, storageReader->beg);
		} else {
			std::streampos initialPosition = indexReader->tellg();
			indexReader->seekg(sizeof(int) * doc, indexReader->beg);
			char bytes[sizeof(int)];
			indexReader->read(bytes, sizeof(int));
			index = 0;
			for (int i = sizeof(int) - 1; i >= 0; i--) {
				index <<= 8;
				index |= bytes[i];
			}
			indexReader->seekg(initialPosition, indexReader->beg);
		}
		return index;
	}

}  // namespace search
