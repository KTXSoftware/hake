#include "JavaExporter.h"
#include "Files.h"
#include "Haxe.h"
#include "ImageTool.h"

using namespace hake;
using namespace kake;

JavaExporter::JavaExporter(Path directory) : directory(directory) {
	
}

void JavaExporter::exportSolution(kake::Platform platform, kake::Path haxeDirectory) {
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
		p("<movie platform=\"Java\" />", 2);
		p("<movie background=\"#FFFFFF\" />", 2);
		if (Files::isDirectory(haxeDirectory)) p("<movie preferredSDK=\"" + haxeDirectory.toString() + "\" />", 2);
		p("</output>", 1);
		p("<!-- Other classes to be compiled into your SWF -->", 1);
		p("<classpaths>", 1);
		p("<class path=\"..\\Sources\" />", 2);
		p("<class path=\"..\\Kha\\Sources\" />", 2);
		p("<class path=\"..\\Kha\\Backends\\" + backend() + "\" />", 2);
		p("</classpaths>", 1);
		p("<!-- Build options -->", 1);
		p("<build>", 1);
		p("<option directives=\"\" />", 2);
		p("<option flashStrict=\"False\" />", 2);
		p("<option mainClass=\"Main\" />", 2);
		p("<option enabledebug=\"False\" />", 2);
		p("<option additional=\"-D no-compilation&#xA;-java-lib " + haxeDirectory.resolve(Paths::get("hxjava", "hxjava-std.jar")).toString() + "\" />", 2);
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
		p("<option testMovieCommand=\"\" />", 2);
		p("</options>", 1);
		p("<!-- Plugin storage -->", 1);
		p("<storage />", 1);
	p("</project>");
	closeFile();
		
	Path p = directory.resolve("build").relativize(haxeDirectory.resolve(Paths::get("hxjava", "hxjava-std.jar")));
	executeHaxe(haxeDirectory, directory, backend(), "java", " -D no-compilation -java-lib " + p.toString());
		
	exportEclipseProject();
}

std::string JavaExporter::backend() {
	return "Java";
}

void JavaExporter::exportEclipseProject() {
	writeFile(directory.resolve(Paths::get("build", ".classpath")));
	p("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	p("<classpath>");
	p("\t<classpathentry kind=\"src\" path=\"Sources/src\"/>");
	p("\t<classpathentry kind=\"con\" path=\"org.eclipse.jdt.launching.JRE_CONTAINER\"/>");
	p("\t<classpathentry kind=\"output\" path=\"bin\"/>");
	p("</classpath>");
	closeFile();
		
	writeFile(directory.resolve(Paths::get("build", ".project")));
	p("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	p("<projectDescription>");
	p("\t<name>" + getCurrentDirectoryName(directory) + "</name>");
	p("\t<comment></comment>");
	p("\t<projects>");
	p("\t</projects>");
	p("\t<buildSpec>");
	p("\t\t<buildCommand>");
	p("\t\t\t<name>org.eclipse.jdt.core.javabuilder</name>");
	p("\t\t\t<arguments>");
	p("\t\t\t</arguments>");
	p("\t\t</buildCommand>");
	p("\t</buildSpec>");
	p("\t<natures>");
	p("\t\t<nature>org.eclipse.jdt.core.javanature</nature>");
	p("\t</natures>");
	p("</projectDescription>");
	closeFile();
}

void JavaExporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	copyFile(directory.resolve(from.toString() + ".wav"), directory.resolve("build").resolve(to.toString() + ".wav"));
}

void JavaExporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	copyFile(directory.resolve(from.toString() + ".wav"), directory.resolve("build").resolve(to.toString() + ".wav"));
}

void JavaExporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) {
	exportImage(directory.resolve(from), directory.resolve("build").resolve(to), asset);
}

void JavaExporter::copyBlob(Platform platform, Path from, Path to) {
	copyFile(directory.resolve(from), directory.resolve("build").resolve(to));
}
