#include "KoreExporter.h"
#include "Files.h"
#include "ImageTool.h"
#include "SoundTool.h"

using namespace hake;
using namespace kake;

KoreExporter::KoreExporter(Platform platform, Path directory) : directory(directory), platform(platform) {
	
}

std::string KoreExporter::sysdir() {
	switch (platform) {
	case Windows:
		return "windows";
	case WindowsRT:
		return "winrt";
	case PlayStation3:
		return "ps3";
	case iOS:
		return "ios";
	case OSX:
		return "osx";
	case Android:
		return "android";
	case Xbox360:
		return "xbox360";
	case Linux:
		return "linux";
	default:
		return "kore";
	}
}
	
void KoreExporter::exportSolution(Platform platform, Path haxeDirectory, Path from) {
	writeFile(directory.resolve("project-" + sysdir() + ".hxproj"));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<project version=\"2\">");
		p("<!-- Output SWF options -->", 1);
		p("<output>", 1);
		p("<movie outputType=\"Application\" />", 2);
		p("<movie input=\"\" />", 2);
		p("<movie path=\"" + sysdir() + "-build\\Sources\" />", 2);
		p("<movie fps=\"0\" />", 2);
		p("<movie width=\"0\" />", 2);
		p("<movie height=\"0\" />", 2);
		p("<movie version=\"1\" />", 2);
		p("<movie minorVersion=\"0\" />", 2);
		p("<movie platform=\"C++\" />", 2);
		p("<movie background=\"#FFFFFF\" />", 2);
		if (Files::isDirectory(haxeDirectory)) p("<movie preferredSDK=\"../" + haxeDirectory.toString() + "\" />", 2);
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
	
void KoreExporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	if (platform == Android)  convertSound(from, directory.resolve(Paths::get(sysdir(), "assets")).resolve(to.toString() + ".ogg"), oggEncoder);
	else convertSound(from, directory.resolve(sysdir()).resolve(to.toString() + ".ogg"), oggEncoder);
}

void KoreExporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	if (platform == Android) copyFile(from, directory.resolve(Paths::get(sysdir(), "assets")).resolve(to.toString() + ".wav"));
	else copyFile(from, directory.resolve(sysdir()).resolve(to.toString() + ".wav"));
}

void KoreExporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) {
	if (platform == Android) exportImage(from, directory.resolve(Paths::get(sysdir(), "assets")).resolve(to), asset);
	else exportImage(from, directory.resolve(sysdir()).resolve(to), asset);
}

void KoreExporter::copyBlob(Platform platform, Path from, Path to) {
	if (platform == Android) copyFile(from, directory.resolve(Paths::get(sysdir(), "assets")).resolve(to));
	else copyFile(from, directory.resolve(sysdir()).resolve(to));
}
