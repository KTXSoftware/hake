#include "SoundTool.h"
#include "Execute.h"
#include "String.h"

using namespace hake;
using namespace kake;

void hake::convertSound(Path inFilename, Path outFilename, std::string encoder) {
	executeSync(replace(replace(encoder, "{in}", inFilename.toString()), "{out}", outFilename.toString()));
}
