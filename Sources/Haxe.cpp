#include "Haxe.h"
#include "Execute.h"

using namespace kake;

void hake::executeHaxe(Path haxeDirectory, Path from, Path to, std::string backendDir, std::string language, std::vector<std::string> options) {
#ifdef SYS_WINDOWS
	Path exe = haxeDirectory.resolve("haxe.exe");
#elif defined SYS_OSX
	Path exe = haxeDirectory.resolve("haxe-osx");
#elif defined SYS_LINUX
	Path exe = haxeDirectory.resolve("haxe-linux");
#endif
	std::vector<std::string> args;
	args.push_back("-cp");
	args.push_back(from.resolve("Sources").toString());
	args.push_back("-cp");
	args.push_back(from.resolve(Paths::get("Kha", "Sources")).toString());
	args.push_back("-cp");
	args.push_back(from.resolve(Paths::get("Kha", "Backends", backendDir)).toString());
	args.push_back(std::string("-") + language);
	args.push_back(to.toString());
	args.push_back("-main");
	args.push_back("Main");
	for (unsigned i = 0; i < options.size(); ++i) args.push_back(options[i]);
	executeSync(exe.toString(), args, std::string("HAXE_STD_PATH=") + haxeDirectory.resolve("std").toString());
}
