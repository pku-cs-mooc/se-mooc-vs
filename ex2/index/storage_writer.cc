#include "index/storage_writer.h"

#include <string>

namespace search {

	StorageWriter::~StorageWriter() {
		// TODO: Implement destructor.
		Close();
	}

	void StorageWriter::Close() {
		// TODO: Implement this function.
		if (storageWriter) {
			io->CloseStorageOut(storageWriter);
			storageWriter = nullptr;
		}
		if (indexWriter) {
			io->CloseStorageIndexOut(indexWriter);
			indexWriter = nullptr;
		}
	}

	void StorageWriter::AddStorage(const std::string& stored) {
		// TODO: Implement this function.
		char bytes[sizeof(int)];
		for (int i = 0; i < sizeof(int); i++) {
			bytes[i] = (index >> (8 * i)) & 0xff;
		}
		indexWriter->write(bytes, sizeof(int));
		int strLength = stored.length();
		index += strLength;
		storageWriter->write(stored.c_str(), strLength);
	}

}  // namespace search
