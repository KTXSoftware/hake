#include "PlayStationMobileExporter.h"
#include "ImageTool.h"
#include "String.h"

using namespace hake;
using namespace kake;

PlayStationMobileExporter::PlayStationMobileExporter(Path directory) : CSharpExporter(directory) {

}

std::string PlayStationMobileExporter::backendDir() {
	return "Pss";
}

void PlayStationMobileExporter::exportSLN(UUID projectUuid) {
	writeFile(directory.resolve(Paths::get("build", "Project.sln")));
	UUID solutionUuid = UUID::randomUUID();
		
	p("Microsoft Visual Studio Solution File, Format Version 11.00");
	p("# Visual Studio 2010");
	p("Project(\"{" + toUpperCase(solutionUuid.toString()) + "}\") = \"HaxeProject\", \"Project.csproj\", \"{" + toUpperCase(projectUuid.toString()) + "}\"");
	p("EndProject");
	p("Global");
		p("GlobalSection(SolutionConfigurationPlatforms) = preSolution", 1);
			p("Debug|Any CPU = Debug|Any CPU", 2);
			p("Release|Any CPU = Release|Any CPU", 2);
		p("EndGlobalSection", 1);
		p("GlobalSection(ProjectConfigurationPlatforms) = postSolution", 1);
			p("{" + toUpperCase(projectUuid.toString()) + "}.Debug|Any CPU.ActiveCfg = Debug|Any CPU", 2);
			p("{" + toUpperCase(projectUuid.toString()) + "}.Debug|Any CPU.Build.0 = Debug|Any CPU", 2);
			p("{" + toUpperCase(projectUuid.toString()) + "}.Release|Any CPU.ActiveCfg = Release|Any CPU", 2);
			p("{" + toUpperCase(projectUuid.toString()) + "}.Release|Any CPU.Build.0 = Release|Any CPU", 2);
		p("EndGlobalSection", 1);
		p("GlobalSection(MonoDevelopProperties) = preSolution", 1);
			p("StartupItem = Project.csproj", 2);
		p("EndGlobalSection", 1);
	p("EndGlobal");
	closeFile();
}

void PlayStationMobileExporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
		
}

void PlayStationMobileExporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
		
}

void PlayStationMobileExporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) {
	exportImage(directory.resolve(from), directory.resolve(Paths::get("build", "bin")).resolve(to), asset);
	files.push_back(Paths::get(asset["file"].string()));
}

void PlayStationMobileExporter::copyBlob(Platform platform, Path from, Path to) {
	copyFile(directory.resolve(from), directory.resolve(Paths::get("build", "bin")).resolve(to));
	files.push_back(to);
}

void PlayStationMobileExporter::exportResources() {
	std::ofstream simple_fcg(directory.resolve(Paths::get("build", "shaders", "Simple.fcg")).toString());
	simple_fcg
		<< "void main(float4 out Color : COLOR, uniform float4 MaterialColor) {\n"
		<< "\tColor = MaterialColor;\n"
		<< "}\n";

	std::ofstream simple_vcg(directory.resolve(Paths::get("build", "shaders", "Simple.vcg")).toString());
	simple_vcg
		<< "void main(float4 in a_Position : POSITION, float4 out v_Position : POSITION, uniform float4x4 WorldViewProj) {\n"
		<< "\tv_Position = mul(a_Position, WorldViewProj);\n"
		<< "}\n";

	std::ofstream texture_fcg(directory.resolve(Paths::get("build", "shaders", "Texture.fcg")).toString());
	texture_fcg
		<< "void main(float2 in  v_TexCoord : TEXCOORD0, float4 out Color : COLOR, uniform sampler2D Texture0 : TEXUNIT0) {\n"
		<< "\tColor = tex2D(Texture0, v_TexCoord);\n"
		<< "}\n";

	std::ofstream texture_vcg(directory.resolve(Paths::get("build", "shaders", "Texture.vcg")).toString());
	texture_vcg
		<< "void main(float4 in a_Position : POSITION, float2 in a_TexCoord : TEXCOORD0, float4 out v_Position : POSITION, float2 out v_TexCoord : TEXCOORD0, uniform float4x4 WorldViewProj) {\n"
		<< "\tv_Position = mul(a_Position, WorldViewProj);\n"
		<< "\tv_TexCoord  = a_TexCoord;\n"
		<< "}\n";
}

void PlayStationMobileExporter::exportCsProj(UUID projectUuid) {
	writeFile(directory.resolve(Paths::get("build", "Project.csproj")));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<Project DefaultTargets=\"Build\" ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">");
		p("<PropertyGroup>", 1);
			p("<Configuration Condition=\" '$(Configuration)' == '' \">Debug</Configuration>", 2);
			p("<Platform Condition=\" '$(Platform)' == '' \">AnyCPU</Platform>", 2);
			p("<ProductVersion>10.0.0</ProductVersion>", 2);
			p("<SchemaVersion>2.0</SchemaVersion>", 2);
			p("<ProjectGuid>{" + toUpperCase(projectUuid.toString()) + "}</ProjectGuid>", 2);
			p("<ProjectTypeGuids>{69878862-DA7D-4DC6-B0A1-50D8FAB4242F};{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}</ProjectTypeGuids>", 2);
			p("<OutputType>Exe</OutputType>", 2);
			p("<RootNamespace>PSTest</RootNamespace>", 2);
			p("<AssemblyName>PSTest</AssemblyName>", 2);
		p("</PropertyGroup>", 1);
		p("<PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' \">", 1);
			p("<DebugSymbols>true</DebugSymbols>", 2);
			p("<DebugType>full</DebugType>", 2);
			p("<Optimize>false</Optimize>", 2);
			p("<OutputPath>bin\\Debug</OutputPath>", 2);
			p("<DefineConstants>DEBUG;</DefineConstants>", 2);
			p("<ErrorReport>prompt</ErrorReport>", 2);
			p("<WarningLevel>4</WarningLevel>", 2);
			p("<ConsolePause>false</ConsolePause>", 2);
		p("</PropertyGroup>", 1);
		p("<PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Release|AnyCPU' \">", 1);
			p("<DebugType>none</DebugType>", 2);
			p("<Optimize>true</Optimize>", 2);
			p("<OutputPath>bin\\Release</OutputPath>", 2);
			p("<ErrorReport>prompt</ErrorReport>", 2);
			p("<WarningLevel>4</WarningLevel>", 2);
			p("<ConsolePause>false</ConsolePause>", 2);
		p("</PropertyGroup>", 1);
		p("<ItemGroup>", 1);
			p("<Reference Include=\"System\" />", 2);
			p("<Reference Include=\"System.Xml\" />", 2);
			p("<Reference Include=\"System.Core\" />", 2);
			p("<Reference Include=\"Sce.PlayStation.Core\" />", 2);
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			includeFiles(directory.resolve(Paths::get("build", "Sources", "src")), directory.resolve(Paths::get("build")));
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			p("<ShaderProgram Include=\"shaders\\Simple.fcg\" />", 2);
			p("<ShaderProgram Include=\"shaders\\Simple.vcg\" />", 2);
			p("<ShaderProgram Include=\"shaders\\Texture.fcg\" />", 2);
			p("<ShaderProgram Include=\"shaders\\Texture.vcg\" />", 2);
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			p("<Folder Include=\"resources\\\" />", 2);
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			for (Path file : files) {
				p("<Content Include=\"bin\\" + file.toString() + "\">", 2);
					p("<Link>resources\\" + file.toString() + "</Link>", 3);
				p("</Content>", 2);
			}
		p("</ItemGroup>", 1);
		p("<Import Project=\"$(MSBuildExtensionsPath)\\Sce\\Sce.Psm.CSharp.targets\" />", 1);
	p("</Project>");
	closeFile();
}
