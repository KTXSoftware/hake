#include "KoreExporter.h"
#include "Files.h"

using namespace hake;
using namespace kake;

KoreExporter::KoreExporter(Path directory) : directory(directory) {
	
}
	
void KoreExporter::exportSolution(Path directory, Platform platform) {
	createDirectory(directory.resolve("build"));
		
	writeFile(directory.resolve(Paths::get("build", "Project.hxproj")));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<project version=\"2\">");
		p("<!-- Output SWF options -->", 1);
		p("<output>", 1);
		p("<movie outputType=\"Application\" />", 2);
		p("<movie input=\"\" />", 2);
		p("<movie path=\"Sources\" />", 2);
		p("<movie fps=\"0\" />", 2);
		p("<movie width=\"0\" />", 2);
		p("<movie height=\"0\" />", 2);
		p("<movie version=\"1\" />", 2);
		p("<movie minorVersion=\"0\" />", 2);
		p("<movie platform=\"C++\" />", 2);
		p("<movie background=\"#FFFFFF\" />", 2);
	//	if (Files::isDirectory(Configuration.getProjectsDirectory().resolve(Paths::get("Externals", "haxe")))) p("<movie preferredSDK=\"" + Configuration.getProjectsDirectory().resolve(Paths::get("Externals", "haxe")).toString() + "\" />", 2);
		p("</output>", 1);
		p("<!-- Other classes to be compiled into your SWF -->", 1);
		p("<classpaths>", 1);
		p("<class path=\"..\\Sources\" />", 2);
		p("<class path=\"..\\Kha\\Sources\" />", 2);
		p("<class path=\"..\\Kha\\Backends\\Kore\" />", 2);
		p("</classpaths>", 1);
		p("<!-- Build options -->", 1);
		p("<build>", 1);
		p("<option directives=\"\" />", 2);
		p("<option flashStrict=\"False\" />", 2);
		p("<option mainClass=\"Main\" />", 2);
		p("<option enabledebug=\"False\" />", 2);
		p("<option additional=\"-D no-compilation\" />", 2);
		p("</build>", 1);
		p("<!-- haxelib libraries -->", 1);
		p("<haxelib>", 1);
		p("<!-- example: <library name=\"...\" /> -->", 2);
		p("</haxelib>", 1);
		p("<!-- Class files to compile (other referenced classes will automatically be included) -->", 1);
		p("<compileTargets>", 1);
		p("<compile path=\"..\\Sources\\Main.hx\" />", 2);
		p("</compileTargets>", 1);
		p("<!-- Paths to exclude from the Project Explorer tree -->", 1);
		p("<hiddenPaths>", 1);
		p("<!-- example: <hidden path=\"...\" /> -->", 2);
		p("</hiddenPaths>", 1);
		p("<!-- Executed before build -->", 1);
		p("<preBuildCommand />", 1);
		p("<!-- Executed after build -->", 1);
		p("<postBuildCommand alwaysRun=\"False\" />", 1);
		p("<!-- Other project options -->", 1);
		p("<options>", 1);
		p("<option showHiddenPaths=\"False\" />", 2);
		p("<option testMovie=\"Custom\" />", 2);
		p("<option testMovieCommand=\"run.bat\" />", 2);
		p("</options>", 1);
		p("<!-- Plugin storage -->", 1);
		p("<storage />", 1);
	p("</project>");
	closeFile();
}
	
void KoreExporter::copyMusic(Path from, Path to) {
	//if (Options.Platform == Platform.Android) SoundTool.convertToOgg(directory, directory.resolve(from + ".wav"), directory.resolve(Paths::get("build", "assets")).resolve(to + ".ogg"));
	//else SoundTool.convertToOgg(directory, directory.resolve(from + ".wav"), directory.resolve(Paths::get("build", "bin")).resolve(to + ".ogg"));
}

void KoreExporter::copySound(Path from, Path to) {
	//if (Options.Platform == Platform.Android) copyFile(directory.resolve(from + ".wav"), directory.resolve(Paths::get("build", "assets")).resolve(to + ".wav"));
	//else copyFile(directory.resolve(from + ".wav"), directory.resolve(Paths::get("build", "bin")).resolve(to + ".wav"));
}

void KoreExporter::copyImage(Path from, Path to, const Json::Value& asset) {
	//if (Options.Platform == Platform.Android) ImageTool.export(directory.resolve(from), directory.resolve(Paths::get("build", "assets")).resolve(to), asset);
	//else ImageTool.export(directory.resolve(from), directory.resolve(Paths.get("build", "bin")).resolve(to), asset);
}

void KoreExporter::copyBlob(Path from, Path to) {
	//if (Options.Platform == Platform.Android) copyFile(directory.resolve(from), directory.resolve(Paths::get("build", "assets")).resolve(to));
	//else copyFile(directory.resolve(from), directory.resolve(Paths::get("build", "bin")).resolve(to));
}
