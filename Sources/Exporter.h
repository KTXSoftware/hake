#pragma once

#include "Path.h"
#include "Platform.h"
#include <fstream>

namespace kake {
	class Solution;

	class Exporter {
	public:
		virtual void exportSolution(std::string name, Platform platform, kmd::Path haxeDirectory, kmd::Path from) = 0;
	protected:
		void writeFile(kmd::Path file);
		void closeFile();
		void p();
		void p(std::string line);
		void p(std::string line, int indent);
		
		std::ofstream* out;
	};
}
