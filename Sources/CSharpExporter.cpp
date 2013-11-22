#include "CSharpExporter.h"
#include "Files.h"
#include "Haxe.h"
#include "ImageTool.h"
#include "String.h"

using namespace hake;
using namespace kake;

CSharpExporter::CSharpExporter(Path directory) : directory(directory) {
	
}
	
void CSharpExporter::includeFiles(Path dir, Path baseDir) {
	if (dir.path.size() == 0 || !Files::exists(dir)) return;
	auto files = Files::newDirectoryStream(dir);
	for (Path file : files) {
		if (Files::isDirectory(file)) includeFiles(file, baseDir);
		else if (endsWith(file.getFileName(), ".cs")) {
			p(std::string("<Compile Include=\"") + replace(baseDir.relativize(file).toString(), '/', '\\') + "\" />", 2);
		}
	}
}

void CSharpExporter::exportSolution(kake::Platform platform, kake::Path haxeDirectory, kake::Path from) {
	createDirectory(directory.resolve(sysdir()));
	createDirectory(directory.resolve(sysdir() + "-build"));

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
		p("<movie platform=\"C#\" />", 2);
		p("<movie background=\"#FFFFFF\" />", 2);
		if (Files::isDirectory(haxeDirectory)) p("<movie preferredSDK=\"../" + haxeDirectory.toString() + "\" />", 2);
		p("</output>", 1);
		p("<!-- Other classes to be compiled into your SWF -->", 1);
		p("<classpaths>", 1);
		p("<class path=\"..\\Sources\" />", 2);
		p("<class path=\"..\\Kha\\Sources\" />", 2);
		p("<class path=\"..\\Kha\\Backends\\" + backendDir() + "\" />", 2);
		p("</classpaths>", 1);
		p("<!-- Build options -->", 1);
		p("<build>", 1);
		p("<option directives=\"\" />", 2);
		p("<option flashStrict=\"False\" />", 2);
		p("<option mainClass=\"Main\" />", 2);
		p("<option enabledebug=\"False\" />", 2);
		p("<option additional=\"-D no-root&#xA;-D no-compilation\" />", 2);
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
	
	writeFile(directory.resolve("project-" + sysdir() + ".hxml"));
	p("-cp " + from.resolve("Sources").toString());
	p("-cp " + from.resolve(Paths::get("Kha", "Sources")).toString());
	p("-cp " + from.resolve(Paths::get("Kha", "Backends", backendDir())).toString());
	p("-cs " + directory.resolve(Paths::get(sysdir() + "-build", "Sources")).toString());
	p("-main Main");
	p("-D no-root");
	p("-D no-compilation");
	closeFile();

	std::vector<std::string> options;
	options.push_back(directory.resolve("project-" + sysdir() + ".hxml").toString());
	executeHaxe(haxeDirectory, options);
	
	UUID projectUuid = UUID::randomUUID();
	exportSLN(projectUuid);
	exportCsProj(projectUuid);
	exportResources();
}

void CSharpExporter::exportSLN(UUID projectUuid) {
	writeFile(directory.resolve(Paths::get(sysdir() + "-build", "Project.sln")));
	UUID solutionUuid = UUID::randomUUID();
		
	p("Microsoft Visual Studio Solution File, Format Version 11.00");
	p("# Visual Studio 2010");
	p("Project(\"{" + toUpperCase(solutionUuid.toString()) + "}\") = \"HaxeProject\", \"Project.csproj\", \"{" + toUpperCase(projectUuid.toString()) + "}\"");
	p("EndProject");
	p("Global");
		p("GlobalSection(SolutionConfigurationPlatforms) = preSolution", 1);
			p("Debug|x86 = Debug|x86", 2);
			p("Release|x86 = Release|x86", 2);
		p("EndGlobalSection", 1);
		p("GlobalSection(ProjectConfigurationPlatforms) = postSolution", 1);
			p("{" + toUpperCase(projectUuid.toString()) + "}.Debug|x86.ActiveCfg = Debug|x86", 2);
			p("{" + toUpperCase(projectUuid.toString()) + "}.Debug|x86.Build.0 = Debug|x86", 2);
			p("{" + toUpperCase(projectUuid.toString()) + "}.Release|x86.ActiveCfg = Release|x86", 2);
			p("{" + toUpperCase(projectUuid.toString()) + "}.Release|x86.Build.0 = Release|x86", 2);
		p("EndGlobalSection", 1);
		p("GlobalSection(SolutionProperties) = preSolution", 1);
			p("HideSolutionNode = FALSE", 2);
		p("EndGlobalSection", 1);
	p("EndGlobal");
	closeFile();
}

void CSharpExporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	
}

void CSharpExporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	
}

void CSharpExporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) {
	exportImage(from, directory.resolve(sysdir()).resolve(to), asset);
}
	
void CSharpExporter::copyBlob(Platform platform, Path from, Path to) {
	copyFile(from, directory.resolve(sysdir()).resolve(to));
}
