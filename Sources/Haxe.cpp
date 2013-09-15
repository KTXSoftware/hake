#include "Haxe.h"
#include "Execute.h"

using namespace kake;

void hake::executeHaxe(Path haxeDirectory, Path directory, std::string backendDir, std::string language, std::string options) {
#ifdef SYS_WINDOWS
	Path exe = haxeDirectory.resolve("haxe.exe");
#elif defined SYS_OSX
	Path exe = haxeDirectory.resolve("haxe-osx");
#elif defined SYS_LINUX
	Path exe = haxeDirectory.resolve("haxe-linux");
#endif
	executeSync(exe.toString() + " -cp " + directory.resolve("Sources").toString() + " -cp " + directory.resolve(Paths::get("Kha", "Sources")).toString() + " -cp " + directory.resolve(Paths::get("Kha", "Backends", backendDir)).toString() + " -" + language + " " + directory.resolve(Paths::get("build", "Sources")).toString() + " -main Main" + options);		
}
