#include "Haxe.h"
#include "Execute.h"

using namespace kake;

void hake::executeHaxe(Path haxeDirectory, std::vector<std::string> options) {
#ifdef SYS_WINDOWS
	Path exe = haxeDirectory.resolve("haxe.exe").toAbsolutePath();
#elif defined SYS_OSX
	Path exe = haxeDirectory.resolve("haxe-osx").toAbsolutePath();
#elif defined SYS_LINUX
	Path exe = haxeDirectory.resolve("haxe-linux").toAbsolutePath();
#endif
	executeSync(exe.toString(), options, std::string("HAXE_STD_PATH=../") + haxeDirectory.resolve("std").toString(), "build");
}
