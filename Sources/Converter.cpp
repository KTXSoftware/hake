#include "Converter.h"
#include "Execute.h"
#include "StringHelper.h"

using namespace hake;
using namespace kake;

void hake::convert(Path inFilename, Path outFilename, std::string encoder) {
	if (encoder == "") return;
	//std::string cmd = replace(replace(encoder, "{in}", "\"" + inFilename.toString()) + "\"", "{out}", "\"" + outFilename.toString() + "\"");
	auto parts = split(encoder, ' ');
	std::vector<std::string> options;
	for (unsigned i = 1; i < parts.size(); ++i) {
		if (parts[i] == "{in}") options.push_back(inFilename.toString());
		else if (parts[i] == "{out}") options.push_back(outFilename.toString());
		else options.push_back(parts[i]);
	}
	executeSync(parts[0], options);
}
