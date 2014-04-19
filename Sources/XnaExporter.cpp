#include "XnaExporter.h"
#include "Ball.h"
#include "ImageTool.h"
#include "StringHelper.h"

using namespace kmd;
using namespace hake;
using namespace kake;

XnaExporter::XnaExporter(Path directory) : CSharpExporter(directory) {

}

std::string XnaExporter::sysdir() {
	return "xna";
}

void XnaExporter::exportResources() {
	createDirectory(directory.resolve(Paths::get(sysdir() + "-build", "Properties")));
	std::ofstream assemblyInfo(directory.resolve(Paths::get(sysdir() + "-build", "Properties", "AssemblyInfo.cs")).toString().c_str());
	assemblyInfo
		<< "using System.Reflection;\n"
		<< "using System.Runtime.CompilerServices;\n"
		<< "using System.Runtime.InteropServices;\n"
		<< "\n"
		<< "[assembly: AssemblyTitle(\"WindowsGame1\")]\n"
		<< "[assembly: AssemblyProduct(\"WindowsGame1\")]\n"
		<< "[assembly: AssemblyDescription(\"\")]\n"
		<< "[assembly: AssemblyCompany(\"KTX Software Development\")]\n"
		<< "[assembly: AssemblyCopyright(\"Copyright � KTX Software Development 2013\")]\n"
		<< "[assembly: AssemblyTrademark(\"\")]\n"
		<< "[assembly: AssemblyCulture(\"\")]\n"
		<< "\n"
		<< "[assembly: ComVisible(false)]\n"
		<< "\n"
		<< "[assembly: Guid(\"9bc720e6-1f41-4daa-9629-0bc91d061f28\")]\n"
		<< "\n"
		<< "[assembly: AssemblyVersion(\"1.0.0.0\")]\n";
}

std::string XnaExporter::backendDir() {
	return "XNA";
}

void XnaExporter::exportSLN(UUID projectUuid) {
	writeFile(directory.resolve(Paths::get(sysdir() + "-build", "Project.sln")));
	UUID solutionUuid = UUID::randomUUID();
	UUID contentUuid = UUID::randomUUID();
		
	p("Microsoft Visual Studio Solution File, Format Version 11.00");
	p("# Visual Studio 2010");
	p("Project(\"{" + toUpperCase(solutionUuid.toString()) + "}\") = \"HaxeProject\", \"Project.csproj\", \"{" + toUpperCase(projectUuid.toString()) + "}\"");
	p("EndProject");
	p("Project(\"{" + toUpperCase(UUID::randomUUID().toString()) + "}\") = \"ProjectContent\", \"ProjectContent.contentproj\", \"{" + toUpperCase(contentUuid.toString()) + "}\"");
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
			p("{" + toUpperCase(contentUuid.toString()) + "}.Debug|x86.ActiveCfg = Debug|x86", 2);
			p("{" + toUpperCase(contentUuid.toString()) + "}.Release|x86.ActiveCfg = Release|x86", 2);
		p("EndGlobalSection", 1);
		p("GlobalSection(SolutionProperties) = preSolution", 1);
			p("HideSolutionNode = FALSE", 2);
		p("EndGlobalSection", 1);
	p("EndGlobal");
	closeFile();
		
	writeFile(directory.resolve(Paths::get(sysdir() + "-build", "ProjectContent.contentproj")));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<Project DefaultTargets=\"Build\" ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">");
		p("<PropertyGroup>", 1);
			p("<ProjectGuid>{4D596EAA-8942-4AAD-967E-4D2A08374564}</ProjectGuid>", 2);
			p("<ProjectTypeGuids>{96E2B04D-8817-42c6-938A-82C39BA4D311};{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}</ProjectTypeGuids>", 2);
			p("<Configuration Condition=\" '$(Configuration)' == '' \">Debug</Configuration>", 2);
			p("<Platform Condition=\" '$(Platform)' == '' \">x86</Platform>", 2);
			p("<OutputType>Library</OutputType>", 2);
			p("<AppDesignerFolder>Properties</AppDesignerFolder>", 2);
			p("<TargetFrameworkVersion>v4.0</TargetFrameworkVersion>", 2);
			p("<XnaFrameworkVersion>v4.0</XnaFrameworkVersion>", 2);
			p("<OutputPath>bin\\$(Platform)\\$(Configuration)</OutputPath>", 2);
			p("<ContentRootDirectory>Content</ContentRootDirectory>", 2);
		p("</PropertyGroup>", 1);
		p("<PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Debug|x86'\">", 1);
			p("<PlatformTarget>x86</PlatformTarget>", 2);
		p("</PropertyGroup>", 1);
		p("<PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Release|x86'\">", 1);
			p("<PlatformTarget>x86</PlatformTarget>", 2);
		p("</PropertyGroup>", 1);
		p("<PropertyGroup>", 1);
			p("<RootNamespace>KhaContent</RootNamespace>", 2);
		p("</PropertyGroup>", 1);
		p("<ItemGroup>", 1);
			p("<Reference Include=\"Microsoft.Xna.Framework.Content.Pipeline.EffectImporter, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=MSIL\" />", 2);
			p("<Reference Include=\"Microsoft.Xna.Framework.Content.Pipeline.FBXImporter, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=MSIL\" />", 2);
			p("<Reference Include=\"Microsoft.Xna.Framework.Content.Pipeline.TextureImporter, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=MSIL\" />", 2);
			p("<Reference Include=\"Microsoft.Xna.Framework.Content.Pipeline.XImporter, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=MSIL\" />", 2);
			p("<Reference Include=\"Microsoft.Xna.Framework.Content.Pipeline.AudioImporters, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=MSIL\" />", 2);
			p("<Reference Include=\"Microsoft.Xna.Framework.Content.Pipeline.VideoImporters, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=MSIL\" />", 2);
		p("</ItemGroup>", 1);
		for (auto image : images) {
			p("<ItemGroup>", 1);
				p("<Compile Include=\"bin\\" + image + "\">", 2);
					p("<Name>" + image.substr(0, image.length() - 4) + "</Name>", 3);
					p("<Importer>TextureImporter</Importer>", 3);
					p("<Processor>TextureProcessor</Processor>", 3);
				p("</Compile>", 2);
			p("</ItemGroup>", 1);
		}
		p("<Import Project=\"$(MSBuildExtensionsPath)\\Microsoft\\XNA Game Studio\\$(XnaFrameworkVersion)\\Microsoft.Xna.GameStudio.ContentPipeline.targets\" />", 1);
	p("</Project>");
	closeFile();
}

void XnaExporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) {
	exportImage(from, directory.resolve("xna").resolve(to), asset);
	images.push_back(asset["file"].string());
}

void XnaExporter::exportCsProj(UUID projectUuid) {
	Ball::the()->exportTo(directory.resolve(Paths::get(sysdir() + "-build", "GameThumbnail.png")), 64, 64, Color::transparent, directory);
	Ball::the()->exportToWindowsIcon(directory.resolve(Paths::get(sysdir() + "-build", "Game.ico")), directory);
		
	writeFile(directory.resolve(Paths::get(sysdir() + "-build", "Project.csproj")));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<Project DefaultTargets=\"Build\" ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">");
		p("<PropertyGroup>", 1);
			p("<ProjectGuid>{" + toUpperCase(projectUuid.toString()) + "}</ProjectGuid>", 2);
			p("<ProjectTypeGuids>{6D335F3A-9D43-41b4-9D22-F6F17C4BE596};{FAE04EC0-301F-11D3-BF4B-00C04F79EFBC}</ProjectTypeGuids>", 2);
			p("<Configuration Condition=\" '$(Configuration)' == '' \">Debug</Configuration>", 2);
			p("<Platform Condition=\" '$(Platform)' == '' \">x86</Platform>", 2);
			p("<OutputType>WinExe</OutputType>", 2);
			p("<AppDesignerFolder>Properties</AppDesignerFolder>", 2);
			p("<RootNamespace>WindowsGame1</RootNamespace>", 2);
			p("<AssemblyName>KhaGame</AssemblyName>", 2);
			p("<TargetFrameworkVersion>v4.0</TargetFrameworkVersion>", 2);
			p("<TargetFrameworkProfile>Client</TargetFrameworkProfile>", 2);
			p("<XnaFrameworkVersion>v4.0</XnaFrameworkVersion>", 2);
			p("<XnaPlatform>Windows</XnaPlatform>", 2);
			p("<XnaProfile>Reach</XnaProfile>", 2);
			p("<XnaCrossPlatformGroupID>d431ff8d-bafa-420e-8740-c2c1114d7ac2</XnaCrossPlatformGroupID>", 2);
			p("<XnaOutputType>Game</XnaOutputType>", 2);
			p("<ApplicationIcon>Game.ico</ApplicationIcon>", 2);
			p("<Thumbnail>GameThumbnail.png</Thumbnail>", 2);
			p("<PublishUrl>publish\\</PublishUrl>", 2);
			p("<Install>true</Install>", 2);
			p("<InstallFrom>Disk</InstallFrom>", 2);
			p("<UpdateEnabled>false</UpdateEnabled>", 2);
			p("<UpdateMode>Foreground</UpdateMode>", 2);
			p("<UpdateInterval>7</UpdateInterval>", 2);
			p("<UpdateIntervalUnits>Days</UpdateIntervalUnits>", 2);
			p("<UpdatePeriodically>false</UpdatePeriodically>", 2);
			p("<UpdateRequired>false</UpdateRequired>", 2);
			p("<MapFileExtensions>true</MapFileExtensions>", 2);
			p("<ApplicationRevision>0</ApplicationRevision>", 2);
			p("<ApplicationVersion>1.0.0.%2a</ApplicationVersion>", 2);
			p("<IsWebBootstrapper>false</IsWebBootstrapper>", 2);
			p("<UseApplicationTrust>false</UseApplicationTrust>", 2);
			p("<BootstrapperEnabled>true</BootstrapperEnabled>", 2);
		p("</PropertyGroup>", 1);
		p("<PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Debug|x86' \">", 1);
			p("<DebugSymbols>true</DebugSymbols>", 2);
			p("<DebugType>full</DebugType>", 2);
			p("<Optimize>false</Optimize>", 2);
			p("<OutputPath>bin\\x86\\Debug</OutputPath>", 2);
			p("<DefineConstants>DEBUG;TRACE;WINDOWS</DefineConstants>", 2);
			p("<ErrorReport>prompt</ErrorReport>", 2);
			p("<WarningLevel>4</WarningLevel>", 2);
			p("<NoStdLib>true</NoStdLib>", 2);
			p("<UseVSHostingProcess>false</UseVSHostingProcess>", 2);
			p("<PlatformTarget>x86</PlatformTarget>", 2);
			p("<XnaCompressContent>false</XnaCompressContent>", 2);
		p("</PropertyGroup>", 1);
		p("<PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Release|x86' \">", 1);
			p("<DebugType>pdbonly</DebugType>", 2);
			p("<Optimize>true</Optimize>", 2);
			p("<OutputPath>bin\\x86\\Release</OutputPath>", 2);
			p("<DefineConstants>TRACE;WINDOWS</DefineConstants>", 2);
			p("<ErrorReport>prompt</ErrorReport>", 2);
			p("<WarningLevel>4</WarningLevel>", 2);
			p("<NoStdLib>true</NoStdLib>", 2);
			p("<UseVSHostingProcess>false</UseVSHostingProcess>", 2);
			p("<PlatformTarget>x86</PlatformTarget>", 2);
			p("<XnaCompressContent>true</XnaCompressContent>", 2);
		p("</PropertyGroup>", 1);
		p("<ItemGroup>", 1);
			p("<Reference Include=\"Microsoft.Xna.Framework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=x86\" />", 2);
			p("<Reference Include=\"Microsoft.Xna.Framework.Game, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=x86\" />", 2);
			p("<Reference Include=\"Microsoft.Xna.Framework.Graphics, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=x86\" />", 2);
			p("<Reference Include=\"Microsoft.Xna.Framework.GamerServices, Version=4.0.0.0, Culture=neutral, PublicKeyToken=842cf8be1de50553, processorArchitecture=x86\" />", 2);
			p("<Reference Include=\"mscorlib\" />", 2);
			p("<Reference Include=\"System\" />", 2);
			p("<Reference Include=\"System.Xml\" />", 2);
			p("<Reference Include=\"System.Core\" />", 2);
			p("<Reference Include=\"System.Xml.Linq\" />", 2);
			p("<Reference Include=\"System.Net\" />", 2);
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			p("<Compile Include=\"Properties\\AssemblyInfo.cs\" />", 2);
			includeFiles(directory.resolve(Paths::get(sysdir() + "-build", "Sources", "src")), directory.resolve(sysdir() + "-build"));
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			p("<Content Include=\"Game.ico\" />", 2);
			p("<Content Include=\"GameThumbnail.png\">", 2);
				p("<XnaPlatformSpecific>true</XnaPlatformSpecific>", 3);
			p("</Content>", 2);
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			p("<ProjectReference Include=\"ProjectContent.contentproj\">", 2);
				p("<Name>ProjectContent</Name>", 3);
				p("<XnaReferenceType>Content</XnaReferenceType>", 3);
			p("</ProjectReference>", 2);
		p("</ItemGroup>", 1);
		p("<ItemGroup>", 1);
			p("<BootstrapperPackage Include=\".NETFramework,Version=v4.0,Profile=Client\">", 2);
				p("<Visible>False</Visible>", 3);
				p("<ProductName>Microsoft .NET Framework 4 Client Profile %28x86 und x64%29</ProductName>", 3);
				p("<Install>true</Install>", 3);
			p("</BootstrapperPackage>", 2);
			p("<BootstrapperPackage Include=\"Microsoft.Net.Client.3.5\">", 2);
				p("<Visible>False</Visible>", 3);
				p("<ProductName>.NET Framework 3.5 SP1 Client Profile</ProductName>", 3);
				p("<Install>false</Install>", 3);
			p("</BootstrapperPackage>", 2);
			p("<BootstrapperPackage Include=\"Microsoft.Net.Framework.3.5.SP1\">", 2);
				p("<Visible>False</Visible>", 3);
				p("<ProductName>.NET Framework 3.5 SP1</ProductName>", 3);
				p("<Install>false</Install>", 3);
			p("</BootstrapperPackage>", 2);
			p("<BootstrapperPackage Include=\"Microsoft.Windows.Installer.3.1\">", 2);
				p("<Visible>False</Visible>", 3);
				p("<ProductName>Windows Installer 3.1</ProductName>", 3);
				p("<Install>true</Install>", 3);
			p("</BootstrapperPackage>", 2);
			p("<BootstrapperPackage Include=\"Microsoft.Xna.Framework.4.0\">", 2);
				p("<Visible>False</Visible>", 3);
				p("<ProductName>Microsoft XNA Framework Redistributable 4.0</ProductName>", 3);
				p("<Install>true</Install>", 3);
			p("</BootstrapperPackage>", 2);
		p("</ItemGroup>", 1);
		p("<Import Project=\"$(MSBuildBinPath)\\Microsoft.CSharp.targets\" />", 1);
		p("<Import Project=\"$(MSBuildExtensionsPath)\\Microsoft\\XNA Game Studio\\Microsoft.Xna.GameStudio.targets\" />", 1);
	p("</Project>");
	closeFile();
}
