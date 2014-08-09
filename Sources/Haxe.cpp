#include "Haxe.h"
#include "Execute.h"

void hake::executeHaxe(kmd::Path haxeDirectory, std::vector<std::string> options) {
#ifdef SYS_WINDOWS
	kmd::Path exe = haxeDirectory.resolve("haxe.exe").toAbsolutePath();
#elif defined SYS_OSX
	kmd::Path exe = haxeDirectory.resolve("haxe-osx").toAbsolutePath();
#elif defined SYS_LINUX
	kmd::Path exe = haxeDirectory.resolve("haxe-linux").toAbsolutePath();
#endif
	executeSync(exe.toString(), options, std::string("HAXE_STD_PATH=../") + haxeDirectory.resolve("std").toString(), "build");
}
