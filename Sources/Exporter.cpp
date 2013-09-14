#include "Exporter.h"

using namespace kake;

void Exporter::writeFile(Path file) {
	out = new std::ofstream(file.toString().c_str());
}
	
void Exporter::closeFile() {
	delete out;
}

void Exporter::p() {
	p("");
}
	
void Exporter::p(std::string line) {
	p(line, 0);	
}

void Exporter::p(std::string line, int indent) {
	std::string tabs = "";
	for (int i = 0; i < indent; ++i) tabs += "\t";
	*out << tabs << line << "\n";
}
