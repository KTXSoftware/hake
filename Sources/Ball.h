#pragma once

#include "ByteStream.h"
#include "Image.h"

namespace kake {
	enum Color {
		white, black, transparent
	};
	
	class Ball {
	public:
		static Ball* the();
		Image* scale(int width, int height);
		Image* scale(int width, int height, Color color, Path directory);
		void exportTo(Path file, int width, int height, Color color, Path directory);
		void writeIcoHeader(ByteStream& stream);
		void writeIconDirEntry(ByteStream& stream, int width, int height, int offset);
		void writeBMPHeader(ByteStream& stream, int width, int height);
		void writeBMP(ByteStream& stream, Image* image);
		int getBMPSize(int width, int height);
		void exportToWindowsIcon(Path filename, Path directory);
		void exportToMacIcon(Path filename, Path directory);
	private:
		Ball();
		Image* ball;
	};
}
