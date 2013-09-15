#include "Html5Exporter.h"
#include "Files.h"
#include "ImageTool.h"
#include "SoundTool.h"
#include <sstream>

using namespace hake;
using namespace kake;

Html5Exporter::Html5Exporter(Path directory) : directory(directory) {
	
}

void Html5Exporter::exportSolution(Platform platform, Path haxeDirectory) {
	createDirectory(directory.resolve("build"));
	
	writeFile(directory.resolve(Paths::get("build", "Project.hxproj")));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<project version=\"2\">");
		p("<!-- Output SWF options -->", 1);
		p("<output>", 1);
		p("<movie outputType=\"Application\" />", 2);
		p("<movie input=\"\" />", 2);
		p("<movie path=\"bin\\JSProject.js\" />", 2);
		p("<movie fps=\"0\" />", 2);
		p("<movie width=\"0\" />", 2);
		p("<movie height=\"0\" />", 2);
		p("<movie version=\"1\" />", 2);
		p("<movie minorVersion=\"0\" />", 2);
		p("<movie platform=\"JavaScript\" />", 2);
		p("<movie background=\"#FFFFFF\" />", 2);
		if (Files::isDirectory(haxeDirectory)) p("<movie preferredSDK=\"" + haxeDirectory.toString() + "\" />", 2);
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
		p("<option testMovie=\"OpenDocument\" />", 2);
		p("<option testMovieCommand=\"bin/index.html\" />", 2);
		p("</options>", 1);
		p("<!-- Plugin storage -->", 1);
		p("<storage />", 1);
	p("</project>");
	closeFile();
		
	createDirectory(directory.resolve(Paths::get("build", "bin")));
	writeFile(directory.resolve(Paths::get("build", "bin", "index.html")));
	p("<!DOCTYPE html>");
	p("<html lang=\"en\">");
	p("<head>");
		p("<meta charset=\"utf-8\"/>", 1);
		p("<title>JSProject</title>", 1);
		p("<meta name=\"description\" content=\"\" />", 1);
	p("</head>");
	p("<body>");
		p("<div id=\"haxe:trace\"></div>", 1);
		p("<p align=\"center\">", 1);
			std::stringstream khanvas;
			khanvas << "<canvas id=\"khanvas\" width=\"" << width << "\" height=\"" << height << "\" style=\"outline: none;\"></canvas>";
			p(khanvas.str(), 2);
		p("</p>", 1);
		p("<script type=\"text/vbscript\">", 1);
			p("Function arr(t)", 2);
				p("arr = CStr(t)", 3);
			p("End Function", 2);
			p("Function arrl(t)", 2);
				p("arrl = \"\"", 3);
				p("if LenB(t) mod 2 Then arrl = Chr(AscB(RightB(t,1)))", 3);
			p("End Function", 2);
		p("</script>", 1);
		p("<script src=\"JSProject.js\"></script>", 1);
	p("</body>");
	p("</html>");
	closeFile();
		
	//if (server != null) server.stop();
	//server = new NanoHTTPD(8080, directory.resolve(Paths.get("build", "bin")).toAbsolutePath().toFile());
}

void Html5Exporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	convertSound(directory.resolve(from.toString() + ".wav"), directory.resolve(Paths::get("build", "bin")).resolve(to.toString() + ".ogg"), oggEncoder);
	convertSound(directory.resolve(from.toString() + ".wav"), directory.resolve(Paths::get("build", "bin")).resolve(to.toString() + ".mp4"), aacEncoder);
}

void Html5Exporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	convertSound(directory.resolve(from.toString() + ".wav"), directory.resolve(Paths::get("build", "bin")).resolve(to.toString() + ".ogg"), oggEncoder);
	convertSound(directory.resolve(from.toString() + ".wav"), directory.resolve(Paths::get("build", "bin")).resolve(to.toString() + ".mp4"), aacEncoder);
}

void Html5Exporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) {
	exportImage(directory.resolve(from), directory.resolve(Paths::get("build", "bin")).resolve(to), asset);
}

void Html5Exporter::copyBlob(kake::Platform platform, kake::Path from, kake::Path to) {
	copyFile(directory.resolve(from), directory.resolve(Paths::get("build", "bin")).resolve(to));
}