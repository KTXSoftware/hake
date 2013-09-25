#include "Execute.h"
#include "FileReader.h"
#include "Files.h"
#include "Haxe.h"
#include "Options.h"
#include "Path.h"
#include "Platform.h"
#include "Random.h"
#include "String.h"
#include "DalvikExporter.h"
#include "FlashExporter.h"
#include "Html5Exporter.h"
#include "JavaExporter.h"
#include "KoreExporter.h"
#include "PlayStationMobileExporter.h"
#include "WpfExporter.h"
#include "XnaExporter.h"
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
}

	void compileShader(std::string kfx, std::string type, Path from, Path to, Path temp) {
		if (kfx.size() > 0) {
			executeSync(kfx + " " + type + " " + from.toString() + " " + to.toString() + " " + temp.toString());
		}
	}

namespace {
	void addShader(Json::Data& project, std::string name, std::string extension) {
		std::map<std::string, Json::Value*> values;
		values["file"] = new Json::String(name + extension);
		values["name"] = new Json::String(name);
		Json::Object* s = new Json::Object(values);
		if (!project.has("shaders")) {
			std::vector<Json::Value*> novalues;
			project.add("shaders", new Json::Array(novalues));
		}
		project["shaders"].add(s);
	}

	void addShaders(Platform platform, Json::Data& project, Path directory, Path shaderPath, std::string kfx) {
		if (!Files::isDirectory(shaderPath)) return;
		Files::createDirectories(directory.resolve(Paths::get("build", "bin")));
		Files::createDirectories(directory.resolve(Paths::get("build", "temp")));
		auto shaders = Files::newDirectoryStream(shaderPath);
		for (Path shader : shaders) {
			std::string name = shader.getFileName();
			if (!endsWith(name, ".glsl")) continue;
			name = name.substr(0, lastIndexOf(name, '.'));
			switch (platform) {
			case Flash: {
				if (Files::exists(shaderPath.resolve(name + ".agal"))) Files::copy(shaderPath.resolve(name + ".agal"), directory.resolve(Paths::get("build", "bin", name + ".agal")), true);
				else compileShader(kfx, "agal", shader, directory.resolve(Paths::get("build", "bin", name + ".agal")), directory.resolve(Paths::get("build", "temp")));
				addShader(project, name, ".agal");
				break;
			}
			case HTML5:
			case Android:
			case iOS: {
				compileShader(kfx, "essl", shader, directory.resolve(Paths::get("build", "bin", name + ".essl")), directory.resolve(Paths::get("build", "temp")));
				addShader(project, name, ".essl");
				break;
			}
			case Windows: {
				if (Options::getGraphicsApi() == OpenGL || Options::getGraphicsApi() == OpenGL2) {
					compileShader(kfx, "glsl", shader, directory.resolve(Paths::get("build", "bin", name + ".glsl")), directory.resolve(Paths::get("build", "temp")));
					addShader(project, name, ".glsl");
				}
				else if (Options::getGraphicsApi() == Direct3D11) {
					compileShader(kfx, "d3d11", shader, directory.resolve(Paths::get("build", "bin", name + ".d3d11")), directory.resolve(Paths::get("build", "temp")));
					addShader(project, name, ".d3d11");
				}
				else {
					compileShader(kfx, "d3d9", shader, directory.resolve(Paths::get("build", "bin", name + ".d3d9")), directory.resolve(Paths::get("build", "temp")));
					addShader(project, name, ".d3d9");
				}
				break;
			}
			case Xbox360:
			case PlayStation3: {
				compileShader(kfx, "d3d9", shader, directory.resolve(Paths::get("build", "bin", name + ".d3d9")), directory.resolve(Paths::get("build", "temp")));
				addShader(project, name, ".d3d9");
				break;
			}
			case OSX:
			case Linux: {
				compileShader(kfx, "glsl", shader, directory.resolve(Paths::get("build", "bin", name + ".glsl")), directory.resolve(Paths::get("build", "temp")));
				addShader(project, name, ".glsl");
				break;
			}
			default:
				break;
			}
		}
	}

	std::string exportKhaProject(Path directory, Platform platform, Path haxeDirectory, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder, std::string kfx) {
		std::cout << "Generating Kha project." << std::endl;
		KhaExporter* exporter = nullptr;
		bool kore = false;
		switch (platform) {
		case Flash:
			exporter = new FlashExporter(directory);
			break;
		case HTML5:
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
		case PlayStationMobile:
			exporter = new PlayStationMobileExporter(directory);
			break;
		case Dalvik:
			exporter = new DalvikExporter(directory);
			break;
		default:
			kore = true;
			exporter = new KoreExporter(directory);
			break;
		}
		
		if (Files::exists(directory.resolve("project.kha"))) {
			Kore::FileReader reader(directory.resolve("project.kha").toString().c_str());
			char* content = (char*)reader.readAll();
			char* text = new char[reader.size() + 1];
			for (int i = 0; i < reader.size(); ++i) text[i] = content[i];
			text[reader.size()] = 0;
			Json::Data project(text);

			exporter->setWidthAndHeight(project["game"]["width"].number(), project["game"]["height"].number());

			for (int i = 0; i < project["assets"].size(); ++i) {
				Json::Value& asset = project["assets"][i];
				if      (asset["type"].string() == "image") exporter->copyImage(platform, Paths::get("Assets", "Graphics", asset["file"].string()), Paths::get(asset["file"].string()), asset);
				else if (asset["type"].string() == "music") exporter->copyMusic(platform, Paths::get("Assets", "Sound", asset["file"].string()), Paths::get(asset["file"].string()), oggEncoder, aacEncoder, mp3Encoder);
				else if (asset["type"].string() == "sound") exporter->copySound(platform, Paths::get("Assets", "Sound", asset["file"].string()), Paths::get(asset["file"].string()), oggEncoder, aacEncoder, mp3Encoder);
				else if (asset["type"].string() == "blob")  exporter->copyBlob(platform, Paths::get("Assets", asset["file"].string()), Paths::get(asset["file"].string()));
			}
			
			//if (Tools.isWindows()) {
				addShaders(platform, project, directory, directory.resolve(Paths::get("Sources", "Shaders")), kfx);
				addShaders(platform, project, directory, directory.resolve(Paths::get("Kha", "Sources", "Shaders")), kfx);
			//}
			
			Path temp = directory.resolve(Paths::get("build", "temp"));
			if (!Files::exists(temp)) Files::createDirectories(temp);
			project.save(directory.resolve(Paths::get("build", "temp", "project.kha")));
			exporter->copyBlob(platform, Paths::get("build", "temp", "project.kha"), Paths::get("project.kha"));
		}
		exporter->exportSolution(platform, haxeDirectory);
		
		std::string name = directory.toAbsolutePath().getFileName();
		
		if (kore && Files::exists(directory.resolve("Kore"))) {
			executeHaxe(haxeDirectory, directory, "Kore", "cpp", " -D no-compilation");
			
			{
				std::ofstream out(directory.resolve("kake.lua").toString().c_str());
				out << "solution = Solution.new(\"" << name << "\")\n";
				out << "project = Project.new(\"" << name << "\")\n";
				std::vector<std::string> files;
				files.push_back("Kha/Backends/kxcpp/src/**.h");
				files.push_back("Kha/Backends/kxcpp/src/**.cpp");
				files.push_back("Kha/Backends/kxcpp/include/**.h");
				//"Kha/Backends/kxcpp/runtime/libs/nekoapi/**.cpp"
				files.push_back("Kha/Backends/kxcpp/runtime/libs/regexp/**.cpp");
				files.push_back("Kha/Backends/kxcpp/runtime/libs/std/**.cpp");
				//"Kha/Backends/kxcpp/runtime/libs/zlib/**.cpp"
				files.push_back("Kha/Backends/kxcpp/runtime/thirdparty/pcre-7.8/**.h");
				files.push_back("Kha/Backends/kxcpp/runtime/thirdparty/pcre-7.8/**.cpp");
				//"Kha/Backends/kxcpp/runtime/thirdparty/pcre-7.8/**.cc"
				files.push_back("Kha/Backends/Kore/*.cpp");
				files.push_back("Kha/Backends/Kore/*.h");
				files.push_back("build/Sources/**.h");
				files.push_back("build/Sources/**.cpp");
				out << "project:addFiles(\n";
				out << "\"" + files[0] + "\"";
				for (unsigned i = 1; i < files.size(); ++i) {
					out << ", \"" + files[i] + "\"";
				}
				out << ")\n";
				out << "project:addExcludes(\"Kha/Backends/kxcpp/runtime/thirdparty/pcre-7.8/dftables.cpp\", "
					<< "\"Kha/Backends/kxcpp/runtime/thirdparty/pcre-7.8/pcredemo.cpp\", "
					<< "\"Kha/Backends/kxcpp/runtime/thirdparty/pcre-7.8/pcregrep.cpp\", "
					<< "\"Kha/Backends/kxcpp/runtime/thirdparty/pcre-7.8/pcretest.cpp\", "
					<< "\"Kha/Backends/kxcpp/src/ExampleMain.cpp\", "
					<< "\"Kha/Backends/kxcpp/src/hx/Scriptable.cpp\", "
					<< "\"**/src/__main__.cpp\", "
					<< "\"Kha/Backends/kxcpp/src/hx/NekoAPI.cpp\")\n";
				out << "project:addIncludeDirs(\"Kha/Backends/kxcpp/include\", \"build/Sources/include\", "
					<< "\"Kha/Backends/kxcpp/runtime/thirdparty/pcre-7.8\", \"Kha/Backends/kxcpp/runtime/libs/nekoapi\");\n";
				out << "project:setDebugDir(\"build/bin\")\n";
				if (platform == Windows) out << "project:addDefine(\"HX_WINDOWS\")\n";
				if (platform == WindowsRT) out << "project:addDefine(\"HX_WINRT\")\n";
				if (platform == OSX) out << "project:addDefine(\"HXCPP_M64\")\n";
				if (platform == iOS) out << "project:addDefine(\"IPHONE\")\n";
				out << "project:addDefine(\"STATIC_LINK\")\n";
				out << "project:addDefine(\"PCRE_STATIC\")\n";
				out << "project:addDefine(\"HXCPP_SET_PROP\")\n";
				out << "project:addDefine(\"HXCPP_VISIT_ALLOCS\")\n";
				out << "project:addDefine(\"KORE\")\n";
				out << "project:addDefine(\"ROTATE90\")\n";
				if (platform == Windows) out << "project:addLib(\"ws2_32\")\n";
				out << "project:addSubProject(Solution.createProject(\"Kore\"))\n";
				out << "solution:addProject(project)\n";
			}

			//exportKoreProject(directory);
#ifdef SYS_WINDOWS
			Path kake = directory.resolve(Paths::get("Kore", "Tools", "kake", "kake.exe"));
#elif defined SYS_OSX
			Path kake = directory.resolve(Paths::get("Kore", "Tools", "kake", "kake-osx"));
#elif defined SYS_LINUX
			Path kake = directory.resolve(Paths::get("Kore", "Tools", "kake", "kake-linux"));
#endif
			std::string platformString = "unknown";
			switch (platform) {
			case Windows:
				platformString = "windows";
				break;
			case Linux:
				platformString = "linux";
				break;
			case Xbox360:
				platformString = "xbox360";
				break;
			case PlayStation3:
				platformString = "ps3";
				break;
			case Android:
				platformString = "android";
				break;
			case WindowsRT:
				platformString = "windowsrt";
				break;
			case OSX:
				platformString = "osx";
				break;
			case iOS:
				platformString = "ios";
				break;
			case HTML5:
				platformString = "html5";
				break;
			case Flash:
				platformString = "flash";
				break;
			case WPF:
				platformString = "wpf";
				break;
			case XNA:
				platformString = "xna";
				break;
			case Java:
				platformString = "java";
				break;
			case PlayStationMobile:
				platformString = "psm";
				break;
			case Dalvik:
				platformString = "dalvik";
				break;
			}

			std::string gfx = "unknown";
			switch (Options::getGraphicsApi()) {
			case OpenGL:
				gfx = "opengl";
				break;
			case OpenGL2:
				gfx = "opengl2";
				break;
			case Direct3D9:
				gfx = "direct3d9";
				break;
			case Direct3D11:
				gfx = "direct3d11";
				break;
			}

			std::string vs = "unknown";
			switch (Options::getVisualStudioVersion()) {
			case VS2010:
				vs = "vs2010";
				break;
			case VS2012:
				vs = "vs2012";
				break;
			}

			std::string exe;
			exe = kake.toString()
				+ " " + platformString;
				//+ " pch=" + Options::getPrecompiledHeaders()
			if (Options::getIntermediateDrive() != "") exe += " intermediate=" + Options::getIntermediateDrive();
			exe += " gfx=" + gfx + " vs=" + vs;
			if (directory.toString() != ".") exe += " " + directory.toString();
		
			executeSync(exe);
		}
		
		std::cout << "Done." << std::endl;
		return name;
	}

	bool isKhaProject(Path directory) {
		return Files::exists(directory.resolve("Kha"));
	}

	std::string exportProject(Path directory, Platform platform, Path haxeDirectory, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder, std::string kfx) {
		if (isKhaProject(directory)) {
			return exportKhaProject(directory, platform, haxeDirectory, oggEncoder, aacEncoder, mp3Encoder, kfx);
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
#elif defined SYS_LINUX
	Platform platform = Platform::Linux;
#elif defined SYS_OSX
	Platform platform = Platform::OSX;
#endif

	Path haxeDirectory;
	std::string oggEncoder;
	std::string aacEncoder;
	std::string mp3Encoder;
	std::string kfx;

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
		else if (arg == "flash") platform = Flash;
		else if (arg == "wpf") platform = WPF;
		else if (arg == "xna") platform = XNA;
		else if (arg == "java") platform = Java;
		else if (arg == "psm") platform = PlayStationMobile;
		else if (arg == "dalvik") platform = Dalvik;

		else if (arg == "pch") Options::setPrecompiledHeaders(true);
		else if (startsWith(arg, "intermediate=")) Options::setIntermediateDrive(arg.substr(13));
		else if (startsWith(arg, "gfx=")) Options::setGraphicsApi(arg.substr(4));
		else if (startsWith(arg, "vs=")) Options::setVisualStudioVersion(arg.substr(3));
		else if (startsWith(arg, "haxe=")) haxeDirectory = Paths::get(arg.substr(5));
		else if (startsWith(arg, "ogg=")) oggEncoder = arg.substr(4);
		else if (startsWith(arg, "aac=")) aacEncoder = arg.substr(4);
		else if (startsWith(arg, "mp3=")) mp3Encoder = arg.substr(4);
		else if (startsWith(arg, "kfx=")) kfx = arg.substr(4);

		else path = arg;
	}
	exportProject(Paths::get(path), platform, haxeDirectory, oggEncoder, aacEncoder, mp3Encoder, kfx);
}
