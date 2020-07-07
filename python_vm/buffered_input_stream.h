#pragma once
#ifndef BUFFERED_INPUT_STREAM_H_
#define BUFFERED_INPUT_STREAM_H_

#include <cstdio>

#define BUFFER_LEN 256

class BufferedInputStream {
private:
	FILE* fp;
	char szBuffer[BUFFER_LEN];
	unsigned short index;
public:
	BufferedInputStream(const char* filename) {
		fopen_s(&fp, filename, "rb");
		fread(szBuffer, BUFFER_LEN * sizeof(char), 1, fp);
		index = 0;
	}

	~BufferedInputStream() {
		close();
	}

	char read() {
		if (index < BUFFER_LEN) {
			return szBuffer[index++];
		}
		else {
			index = 0;
			fread(szBuffer, BUFFER_LEN * sizeof(char), 1, fp);
			return szBuffer[index++];
		}
	}

	// read one integer with 32bits
	int read_int() {
		int b1 = read() & 0xff;
		int b2 = read() & 0xff;
		int b3 = read() & 0xff;
		int b4 = read() & 0xff;
		return b4 << 24 | b3 << 16 | b2 << 8 | b1;
	}

	void unread() {
		index--;
	}

	void close() {
		if (fp != NULL) {
			fclose(fp);
			fp = NULL;
		}
	}
};

#endif  // BUFFERED_INPUT_STREAM_H_
