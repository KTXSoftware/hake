#include "WpfExporter.h"
#include "SoundTool.h"
#include "String.h"

using namespace hake;
using namespace kake;

WpfExporter::WpfExporter(Path directory) : CSharpExporter(directory) {
	
}

void WpfExporter::exportResources() {
	//Tools.copyFile(getClass().getResourceAsStream("/com/ktxsoftware/wpf/AssemblyInfo.cs"), directory.resolve(Paths.get("build", "Properties", "AssemblyInfo.cs")));
	//Tools.copyFile(getClass().getResourceAsStream("/com/ktxsoftware/wpf/Resources.Designer.cs"), directory.resolve(Paths.get("build", "Properties", "Resources.Designer.cs")));
	//Tools.copyFile(getClass().getResourceAsStream("/com/ktxsoftware/wpf/Resources.resx"), directory.resolve(Paths.get("build", "Properties", "Resources.resx")));
	//Tools.copyFile(getClass().getResourceAsStream("/com/ktxsoftware/wpf/Settings.Designer.cs"), directory.resolve(Paths.get("build", "Properties", "Settings.Designer.cs")));
	//Tools.copyFile(getClass().getResourceAsStream("/com/ktxsoftware/wpf/Settings.settings"), directory.resolve(Paths.get("build", "Properties", "Settings.settings")));
}

std::string WpfExporter::backendDir() {
	return "WPF";
}

void WpfExporter::exportCsProj(UUID projectUuid) {
	writeFile(directory.resolve(Paths::get("build", "Project.csproj")));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<Project ToolsVersion=\"4.0\" DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">");
		p("<PropertyGroup>", 1);
			p("<Configuration Condition=\" '$(Configuration)' == '' \">Debug</Configuration>", 2);
			p("<Platform Condition=\" '$(Platform)' == '' \">x86</Platform>", 2);
			p("<ProductVersion>8.0.30703</ProductVersion>", 2);
			p("<SchemaVersion>2.0</SchemaVersion>", 2);
			p("<ProjectGuid>{" + toUpperCase(projectUuid.toString()) + "}</ProjectGuid>", 2);
			p("<OutputType>Library</OutputType>", 2);
			p("<AppDesignerFolder>Properties</AppDesignerFolder>", 2);
			p("<RootNamespace>WpfApplication1</RootNamespace>", 2);
			p("<AssemblyName>WpfApplication1</AssemblyName>", 2);
			p("<TargetFrameworkVersion>v4.0</TargetFrameworkVersion>", 2);
			p("<TargetFrameworkProfile>Client</TargetFrameworkProfile>", 2);
			p("<FileAlignment>512</FileAlignment>", 2);
			p("<ProjectTypeGuids>{60dc8134-eba5-43b8-bcc9-bb4bc16c2548};{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}</ProjectTypeGuids>", 2);
			p("<WarningLevel>4</WarningLevel>", 2);
		p("</PropertyGroup>", 1);
		p("<PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Debug|x86' \">", 1);
			p("<PlatformTarget>x86</PlatformTarget>", 2);
			p("<DebugSymbols>true</DebugSymbols>", 2);
			p("<DebugType>full</DebugType>", 2);
			p("<Optimize>false</Optimize>", 2);
			p("<OutputPath>bin\\Debug\\</OutputPath>", 2);
			p("<DefineConstants>DEBUG;TRACE</DefineConstants>", 2);
			p("<ErrorReport>prompt</ErrorReport>", 2);
			p("<WarningLevel>4</WarningLevel>", 2);
		p("</PropertyGroup>", 1);
		p("<PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Release|x86' \">", 1);
			p("<PlatformTarget>x86</PlatformTarget>", 2);
			p("<DebugType>pdbonly</DebugType>", 2);
			p("<Optimize>true</Optimize>", 2);
			p("<OutputPath>bin\\Release\\</OutputPath>", 2);
			p("<DefineConstants>TRACE</DefineConstants>", 2);
			p("<ErrorReport>prompt</ErrorReport>", 2);
			p("<WarningLevel>4</WarningLevel>", 2);
		p("</PropertyGroup>", 1);
		p("<ItemGroup>", 1);
			p("<Reference Include=\"System\" />", 2);
			p("<Reference Include=\"System.Data\" />", 2);
			p("<Reference Include=\"System.Xml\" />", 2);
			p("<Reference Include=\"Microsoft.CSharp\" />", 2);
			p("<Reference Include=\"System.Core\" />", 2);
			p("<Reference Include=\"System.Xml.Linq\" />", 2);
			p("<Reference Include=\"System.Data.DataSetExtensions\" />", 2);
			p("<Reference Include=\"System.Xaml\">", 2);
				p("<RequiredTargetFramework>4.0</RequiredTargetFramework>", 3);
			p("</Reference>", 2);
			p("<Reference Include=\"WindowsBase\" />", 2);
			p("<Reference Include=\"PresentationCore\" />", 2);
			p("<Reference Include=\"PresentationFramework\" />", 2);
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			includeFiles(directory.resolve(Paths::get("build", "Sources", "src")), directory.resolve(Paths::get("build")));
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			p("<Compile Include=\"Properties\\AssemblyInfo.cs\">", 2);
				p("<SubType>Code</SubType>", 3);
			p("</Compile>", 2);
			p("<Compile Include=\"Properties\\Resources.Designer.cs\">", 2);
				p("<AutoGen>True</AutoGen>", 3);
				p("<DesignTime>True</DesignTime>", 3);
				p("<DependentUpon>Resources.resx</DependentUpon>", 3);
			p("</Compile>", 2);
			p("<Compile Include=\"Properties\\Settings.Designer.cs\">", 2);
				p("<AutoGen>True</AutoGen>", 3);
				p("<DependentUpon>Settings.settings</DependentUpon>", 3);
				p("<DesignTimeSharedInput>True</DesignTimeSharedInput>", 3);
			p("</Compile>", 2);
			p("<EmbeddedResource Include=\"Properties\\Resources.resx\">", 2);
				p("<Generator>ResXFileCodeGenerator</Generator>", 3);
				p("<LastGenOutput>Resources.Designer.cs</LastGenOutput>", 3);
			p("</EmbeddedResource>", 2);
			p("<None Include=\"Properties\\Settings.settings\">", 2);
				p("<Generator>SettingsSingleFileGenerator</Generator>", 3);
				p("<LastGenOutput>Settings.Designer.cs</LastGenOutput>", 3);
			p("</None>", 2);
			p("<AppDesigner Include=\"Properties\\\" />", 2);
		p("</ItemGroup>", 1);
		p("<Import Project=\"$(MSBuildToolsPath)\\Microsoft.CSharp.targets\" />", 1);
	p("</Project>");
	closeFile();
}

void WpfExporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	copyFile(directory.resolve(from.toString() + ".wav"), directory.resolve("build").resolve(to.toString() + ".wav"));
}

void WpfExporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	convertSound(directory.resolve(from.toString() + ".wav"), directory.resolve(Paths::get("build", "bin")).resolve(to.toString() + ".mp4"), aacEncoder);
}
