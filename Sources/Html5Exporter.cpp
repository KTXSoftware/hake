#include "Html5Exporter.h"
#include "Converter.h"
#include "FileReader.h"
#include "Files.h"
#include "Haxe.h"
#include "ImageTool.h"
#include "Options.h"
#include "StringHelper.h"
#include <sstream>

using namespace hake;
using namespace kake;

namespace {
	std::string readFile(std::string filename) {
		kmd::FileReader reader(filename.c_str());
		return std::string((char*)reader.readAll(), reader.size());
	}
}

Html5Exporter::Html5Exporter(Path directory) : directory(directory) {
	
}

std::string Html5Exporter::sysdir() {
	return "html5";
}

void Html5Exporter::exportSolution(std::string name, Platform platform, Path haxeDirectory, Path from) {
	createDirectory(directory.resolve(sysdir()));

	writeFile(directory.resolve("project-" + sysdir() + ".hxproj"));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<project version=\"2\">");
	p("<!-- Output SWF options -->", 1);
	p("<output>", 1);
	p("<movie outputType=\"Application\" />", 2);
	p("<movie input=\"\" />", 2);
	p("<movie path=\"html5\\kha.js\" />", 2);
	p("<movie fps=\"0\" />", 2);
	p("<movie width=\"0\" />", 2);
	p("<movie height=\"0\" />", 2);
	p("<movie version=\"1\" />", 2);
	p("<movie minorVersion=\"0\" />", 2);
	p("<movie platform=\"JavaScript\" />", 2);
	p("<movie background=\"#FFFFFF\" />", 2);
	if (Files::isDirectory(haxeDirectory)) p("<movie preferredSDK=\"../" + haxeDirectory.toString() + "\" />", 2);
	p("</output>", 1);
	p("<!-- Other classes to be compiled into your SWF -->", 1);
	p("<classpaths>", 1);
	p("<class path=\"..\\Sources\" />", 2);
	p("<class path=\"..\\Kha\\Sources\" />", 2);
	p("<class path=\"..\\Kha\\Backends\\HTML5\" />", 2);
	p("</classpaths>", 1);
	p("<!-- Build options -->", 1);
	p("<build>", 1);
	p("<option directives=\"\" />", 2);
	p("<option flashStrict=\"False\" />", 2);
	p("<option mainClass=\"Main\" />", 2);
	p("<option enabledebug=\"False\" />", 2);
	p("<option additional=\"\" />", 2);
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
	p("<option testMovie=\"Webserver\" />", 2);
	p("<option testMovieCommand=\"html5/index.html\" />", 2);
	p("</options>", 1);
	p("<!-- Plugin storage -->", 1);
	p("<storage />", 1);
	p("</project>");
	closeFile();

	Path index = directory.resolve(Paths::get(sysdir(), "index.html"));
	if (!Files::exists(index)) {

		std::string protoindex = readFile(Paths::executableDir().resolve(Paths::get("Data", "html5", "index.html")).toString());
		writeFile(index);
		protoindex = replace(protoindex, "{Name}", name);
		std::stringstream w;
		w << width;
		protoindex = replace(protoindex, "{Width}", w.str());
		std::stringstream h;
		h << height;
		protoindex = replace(protoindex, "{Height}", h.str());
		out->write(protoindex.c_str(), protoindex.size());
		closeFile();
	}

	writeFile(directory.resolve("project-" + sysdir() + ".hxml"));
	p("-cp " + from.resolve(Paths::get("../", "Sources")).toString());
	p("-cp " + from.resolve(Paths::get("../", "Kha", "Sources")).toString());
	p("-cp " + from.resolve(Paths::get("../", "Kha", "Backends", "HTML5")).toString());
	p("-js " + Paths::get(sysdir(), "kha.js").toString());
	p("-main Main");
	closeFile();

	if (Options::compilation()) {
		std::vector<std::string> options;
		options.push_back("project-" + sysdir() + ".hxml");
		executeHaxe(haxeDirectory, options);
	}
}

void Html5Exporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	Files::createDirectories(directory.resolve(sysdir()).resolve(to.toString()).parent());
	convert(from, directory.resolve(sysdir()).resolve(to.toString() + ".ogg"), oggEncoder);
	convert(from, directory.resolve(sysdir()).resolve(to.toString() + ".mp4"), aacEncoder);
}

void Html5Exporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	Files::createDirectories(directory.resolve(sysdir()).resolve(to.toString()).parent());
	convert(from, directory.resolve(sysdir()).resolve(to.toString() + ".ogg"), oggEncoder);
	convert(from, directory.resolve(sysdir()).resolve(to.toString() + ".mp4"), aacEncoder);
}

void Html5Exporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) {
	exportImage(from, directory.resolve(sysdir()).resolve(to), asset);
}

void Html5Exporter::copyBlob(kake::Platform platform, kake::Path from, kake::Path to) {
	copyFile(from, directory.resolve(sysdir()).resolve(to));
}

void Html5Exporter::copyVideo(kake::Platform platform, kake::Path from, kake::Path to, std::string h264Encoder, std::string webmEncoder, std::string wmvEncoder) {
	Files::createDirectories(directory.resolve(sysdir()).resolve(to.toString()).parent());
	convert(from, directory.resolve(sysdir()).resolve(to.toString() + ".mp4"), h264Encoder);
	convert(from, directory.resolve(sysdir()).resolve(to.toString() + ".webm"), webmEncoder);
}
