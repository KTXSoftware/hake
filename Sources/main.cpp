#include "FileReader.h"
#include "Files.h"
#include "Options.h"
#include "Path.h"
#include "Platform.h"
#include "Random.h"
#include "String.h"
#include "FlashExporter.h"
#include "KoreExporter.h"
#include "Json.h"
#include <iostream>
#include <vector>

#ifdef SYS_OSX
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <errno.h>
#endif

#ifdef SYS_WINDOWS
#include <Windows.h>
#endif

using namespace hake;
using namespace kake;

Path koreDir;

namespace {
	std::string fromPlatform(Platform platform) {
		switch (platform) {
		case Windows:
			return "Windows";
		case WindowsRT:
			return "WindowsRT";
		case PlayStation3:
			return "PlayStation 3";
		case iOS:
			return "iOS";
		case OSX:
			return "OS X";
		case Android:
			return "Android";
		case Xbox360:
			return "Xbox 360";
		case Linux:
			return "Linux";
		case HTML5:
			return "HTML5";
		default:
			return "unknown";
		}
	}

	std::string shaderLang(Platform platform) {
		switch (platform) {
			case Windows:
				switch (Options::getGraphicsApi()) {
					case kake::OpenGL:
					case kake::OpenGL2:
						return "glsl";
					case kake::Direct3D9:
						return "d3d9";
					case kake::Direct3D11:
						return "d3d11";
					default:
						return "d3d9";
				}
			case WindowsRT:
				return "d3d11";
			case PlayStation3:
				return "d3d9";
			case iOS:
				return "essl";
			case OSX:
				return "glsl";
			case Android:
				return "essl";
			case Xbox360:
				return "d3d9";
			case Linux:
				return "glsl";
			case HTML5:
				return "essl";
			default:
				return "unknown";
		}
	}

	void executeSync(const char* command) {
#ifdef SYS_WINDOWS
		STARTUPINFOA startupInfo;
		PROCESS_INFORMATION processInfo;
		memset(&startupInfo, 0, sizeof(startupInfo));
		memset(&processInfo, 0, sizeof(processInfo));
		startupInfo.cb = sizeof(startupInfo);
		CreateProcessA(nullptr, (char*)command, nullptr, nullptr, FALSE, CREATE_DEFAULT_ERROR_MODE, nullptr, nullptr, &startupInfo, &processInfo);
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
#else
		system(command);
#endif
	}
}
	void compileShader(std::string type, std::string from, std::string to, std::string temp) {
#ifdef SYS_WINDOWS
		if (koreDir.toString().size() > 0) {
			Path path = koreDir.resolve(Paths::get("Tools", "kfx", "kfx.exe"));
			std::string exe = path.toString() + " " + type + " " + from + " " + to + " " + temp;
			executeSync(exe.c_str());
		}
#endif
#ifdef SYS_OSX
		if (koreDir.toString().size() > 0) {
			Path path = koreDir.resolve(Paths::get("Tools", "kfx", "kfx-osx"));
			std::string exe = path.toString() + " " + type + " " + from + " " + to + " " + temp;
			system(exe.c_str());
		}
#endif
#ifdef SYS_LINUX
		if (koreDir.toString().size() > 0) {
			Path path = koreDir.resolve(Paths::get("Tools", "kfx", "kfx-linux"));
			std::string exe = path.toString() + " " + type + " " + from + " " + to + " " + temp;
			system(exe.c_str());
		}
#endif
	}

namespace {
	void addShaders(Json::Data& project, Path directory, Path shaderPath) {
		if (!Files::isDirectory(shaderPath)) return;
		Files::createDirectories(directory.resolve(Paths::get("build", "bin")));
		//for (Path shader : Files::newDirectoryStream(shaderPath)) {
		//	std::string name = shader.getFileName().toString();
		//	if (!endsWith(name, ".glsl")) continue;
		//	name = name.substring(0, name.lastIndexOf('.'));
		//	switch (Options.Platform) {
		//	case Flash: {
		//		compileShader("agal", shader, directory.resolve(Paths::get("build", "bin", name + ".agal")), directory.resolve(Paths::get("build", "temp")));
		//		Shader s = new Shader();
		//		Json::Object s;
		//		s.add("file",  name + ".agal");
		//		s.add("name", name);
		//		project.shaders.add(s);
		//		break;
		//	}
		//	case HTML5:
		//	case Android:
		//	case iOS: {
		//		compileShader("essl", shader, directory.resolve(Paths::get("build", "bin", name + ".essl")), directory.resolve(Paths::get("build", "temp")));
		//		Shader s = new Shader();
		//		s.file = name + ".essl";
		//		s.name = name;
		//		project.shaders.add(s);
		//		break;
		//	}
		//	case Windows: {
		//		if (Configuration.getWindowsGraphicsBackend() == WindowsGraphicsBackend.OpenGL || Configuration.getWindowsGraphicsBackend() == WindowsGraphicsBackend.OpenGL2) {
		//			compileShader("glsl", shader, directory.resolve(Paths::get("build", "bin", name + ".glsl")), directory.resolve(Paths::get("build", "temp")));
		//			Shader s = new Shader();
		//			s.file = name + ".glsl";
		//			s.name = name;
		//			project.shaders.add(s);
		//		}
		//		else if (Configuration.getWindowsGraphicsBackend() == WindowsGraphicsBackend.Direct3D11) {
		//			compileShader("d3d11", shader, directory.resolve(Paths::get("build", "bin", name + ".d3d11")), directory.resolve(Paths::get("build", "temp")));
		//			Shader s = new Shader();
		//			s.file = name + ".d3d11";
		//			s.name = name;
		//			project.shaders.add(s);
		//		}
		//		else {
		//			compileShader("d3d9", shader, directory.resolve(Paths::get("build", "bin", name + ".d3d9")), directory.resolve(Paths::get("build", "temp")));
		//			Shader s = new Shader();
		//			s.file = name + ".d3d9";
		//			s.name = name;
		//			project.shaders.add(s);
		//		}
		//		break;
		//	}
		//	case Xbox360:
		//	case PlayStation3: {
		//		compileShader("d3d9", shader, directory.resolve(Paths::get("build", "bin", name + ".d3d9")), directory.resolve(Paths::get("build", "temp")));
		//		Shader s = new Shader();
		//		s.file = name + ".d3d9";
		//		s.name = name;
		//		project.shaders.add(s);
		//		break;
		//	}
		//	case MacOSX:
		//	case Linux: {
		//		compileShader("glsl", shader, directory.resolve(Paths::get("build", "bin", name + ".glsl")), directory.resolve(Paths::get("build", "temp")));
		//		Shader s = new Shader();
		//		s.file = name + ".glsl";
		//		s.name = name;
		//		project.shaders.add(s);
		//		break;
		//	}
		//	default:
		//		break;
		//	}
		//}
	}

	std::string exportKhaProject(Path directory, Platform platform) {
		std::cout << "Generating Kha solution." << std::endl;
		KhaExporter* exporter = nullptr;
		switch (platform) {
		case Flash:
			exporter = new FlashExporter(directory);
			break;
		/*case HTML5:
			exporter = new Html5Exporter(directory);
			break;
		case WPF:
			exporter = new WpfExporter(directory);
			break;
		case XNA:
			exporter = new XnaExporter(directory);
			break;
		case Java:
			exporter = new JavaExporter(directory);
			break;
		case Pss:
			exporter = new PssExporter(directory);
			break;
		case Dalvik:
			exporter = new com.ktxsoftware.kake.kha.AndroidExporter(directory);
			break;*/
		default:
			exporter = new KoreExporter(directory);
			break;
		}
		
		if (Files::exists(directory.resolve("project.kha"))) {
			Kore::FileReader reader(directory.resolve("project.kha").toString().c_str());
			Json::Data project((char*)reader.readAll());

			exporter->setWidthAndHeight(project["game"]["width"].number(), project["game"]["height"].number());

			for (int i = 0; i < project["assets"].size(); ++i) {
				auto asset = project["assets"][i];
				if      (asset["type"].string() == "image") exporter->copyImage(Paths::get("Assets", "Graphics", asset["file"].string()), Paths::get(asset["file"].string()), asset);
				else if (asset["type"].string() == "music") exporter->copyMusic(Paths::get("Assets", "Sound", asset["file"].string()), Paths::get(asset["file"].string()));
				else if (asset["type"].string() == "sound") exporter->copySound(Paths::get("Assets", "Sound", asset["file"].string()), Paths::get(asset["file"].string()));
				else if (asset["type"].string() == "blob")  exporter->copyBlob(Paths::get("Assets", asset["file"].string()), Paths::get(asset["file"].string()));
			}
			
			//if (Tools.isWindows()) {
				addShaders(project, directory, directory.resolve(Paths::get("Sources", "Shaders")));
				addShaders(project, directory, directory.resolve(Paths::get("Kha", "Sources", "Shaders")));
			//}
			
			Path temp = directory.resolve(Paths::get("build", "temp"));
			if (!Files::exists(temp)) Files::createDirectories(temp);
		//	saveJson(project, directory.resolve(Paths::get("build", "temp", "project.kha")));
			exporter->copyBlob(Paths::get("build", "temp", "project.kha"), Paths::get("project.kha"));
		}
		exporter->exportSolution(directory, platform);
		
		std::string name = directory.getFileName();
		
		//if (Tools.isKtPlatform(Options.Platform) && Files.exists(directory.resolve("Kore"))) {
		//	Haxe.execute(directory, "Kore", "cpp", " -D no-compilation");
		//	
		//	FileWriter outFile = new FileWriter(directory.resolve("kake.lua").toFile());
		//	PrintWriter out = new PrintWriter(outFile);
		//	out.println("solution = Solution.new(\"" + name + "\")");
		//	out.println("project = Project.new(\"" + name + "\")");
		//	String[] files = {
		//			"Kha/Backends/hxcpp/src/**.h",
		//			"Kha/Backends/hxcpp/src/**.cpp",
		//			"Kha/Backends/hxcpp/include/**.h",
		//			//"Kha/Backends/hxcpp/runtime/libs/nekoapi/**.cpp",
		//			"Kha/Backends/hxcpp/runtime/libs/regexp/**.cpp",
		//			"Kha/Backends/hxcpp/runtime/libs/std/**.cpp",
		//			//"Kha/Backends/hxcpp/runtime/libs/zlib/**.cpp",
		//			"Kha/Backends/hxcpp/runtime/thirdparty/pcre-7.8/**.h",
		//			"Kha/Backends/hxcpp/runtime/thirdparty/pcre-7.8/**.cpp",
		//			//"Kha/Backends/hxcpp/runtime/thirdparty/pcre-7.8/**.cc",
		//			"Kha/Backends/Kore/*.cpp",
		//			"Kha/Backends/Kore/*.h",
		//			"build/Sources/**.h",
		//			"build/Sources/**.cpp"
		//	};
		//	out.print("project:addFiles(");
		//	out.print("\"" + files[0] + "\"");
		//	for (int i = 1; i < 5; ++i) {
		//		out.print(", \"" + files[i] + "\"");
		//	}
		//	out.print(")\n");
		//	out.print("project:addFiles(");
		//	out.print("\"" + files[5] + "\"");
		//	for (int i = 6; i < files.length; ++i) {
		//		out.print(", \"" + files[i] + "\"");
		//	}
		//	out.print(")\n");
		//	out.println("project:addExcludes(\"Kha/Backends/hxcpp/runtime/thirdparty/pcre-7.8/dftables.cpp\", "
		//			+ "\"Kha/Backends/hxcpp/runtime/thirdparty/pcre-7.8/pcredemo.cpp\", "
		//			+ "\"Kha/Backends/hxcpp/runtime/thirdparty/pcre-7.8/pcregrep.cpp\", "
		//			+ "\"Kha/Backends/hxcpp/runtime/thirdparty/pcre-7.8/pcretest.cpp\", "
		//			+ "\"Kha/Backends/hxcpp/src/ExampleMain.cpp\", "
		//			+ "\"Kha/Backends/hxcpp/src/hx/Scriptable.cpp\", "
		//			+ "\"**/src/__main__.cpp\", "
		//			+ "\"Kha/Backends/hxcpp/src/hx/NekoAPI.cpp\")"
		//			);
		//	out.println("project:addIncludeDirs(\"Kha/Backends/hxcpp/include\", \"build/Sources/include\", "
		//			+"\"Kha/Backends/hxcpp/runtime/thirdparty/pcre-7.8\", \"Kha/Backends/hxcpp/runtime/libs/nekoapi\");");
		//	out.println("project:setDebugDir(\"build/bin\")");
		//	if (Options.Platform == Platform.Windows) out.println("project:addDefine(\"HX_WINDOWS\")");
		//	if (Options.Platform == Platform.Windows8) out.println("project:addDefine(\"HX_WINRT\")");
		//	if (Options.Platform == Platform.MacOSX) out.println("project:addDefine(\"HXCPP_M64\")");
		//	if (Options.Platform == Platform.iOS) out.println("project:addDefine(\"IPHONE\")");
		//	out.println("project:addDefine(\"STATIC_LINK\")");
		//	out.println("project:addDefine(\"PCRE_STATIC\")");
		//	out.println("project:addDefine(\"HXCPP_SET_PROP\")");
		//	out.println("project:addDefine(\"HXCPP_VISIT_ALLOCS\")");
		//	out.println("project:addDefine(\"KORE\")");
		//	out.println("project:addDefine(\"ROTATE90\")");
		//	out.println("project:addDefine(\"KORE_DEBUGDIR=\\\"bin\\\"\")");
		//	if (Options.Platform == Platform.Windows) out.println("project:addLib(\"ws2_32\")");
		//	out.println("project:addSubProject(Solution.createProject(\"Kore\"))");
		//	out.println("solution:addProject(project)");
		//	out.close();
		//	outFile.close();
		//	
		//	exportKoreProject(directory);
		//}
		
		std::cout << "Done." << std::endl;
		return name;
	}

	bool isKhaProject(Path directory) {
		return Files::exists(directory.resolve("Kha"));
	}

	std::string exportProject(Path directory, Platform platform) {
		if (isKhaProject(directory)) {
			return exportKhaProject(directory, platform);
		}
		else {
			std::cerr << "Kha directory not found." << std::endl;
			return "";
		}
	}
}

int main(int argc, char** argv) {
	Random::init(rand());
	std::string path = ".";
	#ifdef SYS_WINDOWS
	Platform platform = Platform::Windows;
	#endif
	#ifdef SYS_LINUX
	Platform platform = Platform::Linux;
	#endif
	#ifdef SYS_OSX
	Platform platform = Platform::OSX;
	#endif
	for (int i = 1; i < argc; ++i) {
		std::string arg(argv[i]);
		if (arg == "windows") platform = Windows;
		else if (arg == "linux") platform = Linux;
		else if (arg == "xbox360") platform = Xbox360;
		else if (arg == "ps3") platform = PlayStation3;
		else if (arg == "android") platform = Android;
		else if (arg == "windowsrt") platform = WindowsRT;
		else if (arg == "osx") platform = OSX;
		else if (arg == "ios") platform = iOS;
		else if (arg == "html5") platform = HTML5;

		else if (arg == "pch") Options::setPrecompiledHeaders(true);
		else if (startsWith(arg, "intermediate=")) Options::setIntermediateDrive(arg.substr(13));
		else if (startsWith(arg, "gfx=")) Options::setGraphicsApi(arg.substr(4));
		else if (startsWith(arg, "vs=")) Options::setVisualStudioVersion(arg.substr(3));

		else path = arg;
	}
	exportProject(Paths::get(path), platform);
}
