#include "SoundTool.h"
#include "Execute.h"
#include "String.h"

using namespace hake;
using namespace kake;

void hake::convertSound(Path inFilename, Path outFilename, std::string encoder) {
	if (encoder == "") return;
	std::string cmd = replace(replace(encoder, "{in}", inFilename.toString()), "{out}", outFilename.toString());
	auto parts = split(cmd, ' ');
	std::vector<std::string> options;
	for (unsigned i = 1; i < parts.size(); ++i) options.push_back(parts[i]);
	executeSync(parts[0], options);
}
