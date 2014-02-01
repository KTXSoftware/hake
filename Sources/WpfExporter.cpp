#include "WpfExporter.h"
#include "Converter.h"
#include "Files.h"
#include "StringHelper.h"

using namespace hake;
using namespace kake;

WpfExporter::WpfExporter(Path directory) : CSharpExporter(directory) {
	
}

std::string WpfExporter::sysdir() {
	return "wpf";
}

void WpfExporter::exportResources() {
	Files::createDirectories(directory.resolve(Paths::get(sysdir() + "-build", "Properties")));

	std::ofstream assemblyInfo(directory.resolve(Paths::get(sysdir() + "-build", "Properties", "AssemblyInfo.cs")).toString().c_str());
	assemblyInfo
		<< "using System.Reflection;\n"
		<< "using System.Resources;\n"
		<< "using System.Runtime.CompilerServices;\n"
		<< "using System.Runtime.InteropServices;\n"
		<< "using System.Windows;\n"
		<< "\n"
		<< "[assembly: AssemblyTitle(\"HaxeProject\")]\n"
		<< "[assembly: AssemblyDescription(\"\")]\n"
		<< "[assembly: AssemblyConfiguration(\"\")]\n"
		<< "[assembly: AssemblyCompany(\"KTX Software Development\")]\n"
		<< "[assembly: AssemblyProduct(\"HaxeProject\")]\n"
		<< "[assembly: AssemblyCopyright(\"Copyright � KTX Software Development 2013\")]\n"
		<< "[assembly: AssemblyTrademark(\"\")]\n"
		<< "[assembly: AssemblyCulture(\"\")]\n"
		<< "\n"
		<< "[assembly: ComVisible(false)]\n"
		<< "\n"
		<< "//[assembly: NeutralResourcesLanguage(\"en-US\", UltimateResourceFallbackLocation.Satellite)]\n"
		<< "\n"
		<< "[assembly: ThemeInfo(ResourceDictionaryLocation.None, ResourceDictionaryLocation.SourceAssembly)]\n"
		<< "\n"
		<< "// [assembly: AssemblyVersion(\"1.0.*\")]\n"
		<< "[assembly: AssemblyVersion(\"1.0.0.0\")]\n"
		<< "[assembly: AssemblyFileVersion(\"1.0.0.0\")]\n";

	std::ofstream resourcesDesigner(directory.resolve(Paths::get(sysdir() + "-build", "Properties", "Resources.Designer.cs")).toString().c_str());
	resourcesDesigner
		<< "namespace WpfApplication1.Properties {\n"
		<< "\t[global::System.CodeDom.Compiler.GeneratedCodeAttribute(\"System.Resources.Tools.StronglyTypedResourceBuilder\", \"4.0.0.0\")]\n"
		<< "\t[global::System.Diagnostics.DebuggerNonUserCodeAttribute()]\n"
		<< "\t[global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]\n"
		<< "\tinternal class Resources\n"
		<< "\t{\n"
		<< "\t\tprivate static global::System.Resources.ResourceManager resourceMan;\n"
		<< "\t\tprivate static global::System.Globalization.CultureInfo resourceCulture;\n"
		<< "\n"
		<< "\t\t[global::System.Diagnostics.CodeAnalysis.SuppressMessageAttribute(\"Microsoft.Performance\", \"CA1811:AvoidUncalledPrivateCode\")]\n"
		<< "\t\tinternal Resources() { }\n"
		<< "\n"
		<< "\t\t[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]\n"
		<< "\t\tinternal static global::System.Resources.ResourceManager ResourceManager\n"
		<< "\t\t{\n"
		<< "\t\t\tget\n"
		<< "\t\t\t{\n"
		<< "\t\t\t\tif ((resourceMan == null))\n"
		<< "\t\t\t\t{\n"
		<< "\t\t\t\t\tglobal::System.Resources.ResourceManager temp = new global::System.Resources.ResourceManager(\"WpfApplication1.Properties.Resources\", typeof(Resources).Assembly);\n"
		<< "\t\t\t\t\tresourceMan = temp;\n"
		<< "\t\t\t\t}\n"
		<< "\t\t\t\treturn resourceMan;\n"
		<< "\t\t\t}\n"
		<< "\t\t}\n"
		<< "\n"
		<< "\t\t[global::System.ComponentModel.EditorBrowsableAttribute(global::System.ComponentModel.EditorBrowsableState.Advanced)]\n"
		<< "\t\tinternal static global::System.Globalization.CultureInfo Culture\n"
		<< "\t\t{\n"
		<< "\t\t\tget\n"
		<< "\t\t\t{\n"
		<< "\t\t\t\treturn resourceCulture;\n"
		<< "\t\t\t}\n"
		<< "\t\t\tset\n"
		<< "\t\t\t{\n"
		<< "\t\t\t\tresourceCulture = value;\n"
		<< "\t\t\t}\n"
		<< "\t\t}\n"
		<< "\t}\n"
		<< "}\n";

	std::ofstream resources(directory.resolve(Paths::get(sysdir() + "-build", "Properties", "Resources.resx")).toString().c_str());
	resources
		<< "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
		<< "<root>\n"
		<< "<xsd:schema id=\"root\" xmlns=\"\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xmlns:msdata=\"urn:schemas-microsoft-com:xml-msdata\">\n"
		<< "<xsd:element name=\"root\" msdata:IsDataSet=\"true\">\n"
		<< "<xsd:complexType>\n"
		<< "<xsd:choice maxOccurs=\"unbounded\">\n"
		<< "<xsd:element name=\"metadata\">\n"
		<< "<xsd:complexType>\n"
		<< "<xsd:sequence>\n"
		<< "<xsd:element name=\"value\" type=\"xsd:string\" minOccurs=\"0\" />\n"
		<< "</xsd:sequence>\n"
		<< "<xsd:attribute name=\"name\" type=\"xsd:string\" />\n"
		<< "<xsd:attribute name=\"type\" type=\"xsd:string\" />\n"
		<< "<xsd:attribute name=\"mimetype\" type=\"xsd:string\" />\n"
		<< "</xsd:complexType>\n"
		<< "</xsd:element>\n"
		<< "<xsd:element name=\"assembly\">\n"
		<< "<xsd:complexType>\n"
		<< "<xsd:attribute name=\"alias\" type=\"xsd:string\" />\n"
		<< "<xsd:attribute name=\"name\" type=\"xsd:string\" />\n"
		<< "</xsd:complexType>\n"
		<< "</xsd:element>\n"
		<< "<xsd:element name=\"data\">\n"
		<< "<xsd:complexType>\n"
		<< "<xsd:sequence>\n"
		<< "<xsd:element name=\"value\" type=\"xsd:string\" minOccurs=\"0\" msdata:Ordinal=\"1\" />\n"
		<< "<xsd:element name=\"comment\" type=\"xsd:string\" minOccurs=\"0\" msdata:Ordinal=\"2\" />\n"
		<< "</xsd:sequence>\n"
		<< "<xsd:attribute name=\"name\" type=\"xsd:string\" msdata:Ordinal=\"1\" />\n"
		<< "<xsd:attribute name=\"type\" type=\"xsd:string\" msdata:Ordinal=\"3\" />\n"
		<< "<xsd:attribute name=\"mimetype\" type=\"xsd:string\" msdata:Ordinal=\"4\" />\n"
		<< "</xsd:complexType>\n"
		<< "</xsd:element>\n"
		<< "<xsd:element name=\"resheader\">\n"
		<< "<xsd:complexType>\n"
		<< "<xsd:sequence>\n"
		<< "<xsd:element name=\"value\" type=\"xsd:string\" minOccurs=\"0\" msdata:Ordinal=\"1\" />\n"
		<< "</xsd:sequence>\n"
		<< "<xsd:attribute name=\"name\" type=\"xsd:string\" use=\"required\" />\n"
		<< "</xsd:complexType>\n"
		<< "</xsd:element>\n"
		<< "</xsd:choice>\n"
		<< "</xsd:complexType>\n"
		<< "</xsd:element>\n"
		<< "</xsd:schema>\n"
		<< "<resheader name=\"resmimetype\">\n"
		<< "<value>text/microsoft-resx</value>\n"
		<< "</resheader>\n"
		<< "<resheader name=\"version\">\n"
		<< "<value>2.0</value>\n"
		<< "</resheader>\n"
		<< "<resheader name=\"reader\">\n"
		<< "<value>System.Resources.ResXResourceReader, System.Windows.Forms, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089</value>\n"
		<< "</resheader>\n"
		<< "<resheader name=\"writer\">\n"
		<< "<value>System.Resources.ResXResourceWriter, System.Windows.Forms, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089</value>\n"
		<< "</resheader>\n"
		<< "</root>\n";

	std::ofstream settingsDesigner(directory.resolve(Paths::get(sysdir() + "-build", "Properties", "Settings.Designer.cs")).toString().c_str());
	settingsDesigner
		<< "namespace WpfApplication1.Properties\n"
		<< "{\n"
		<< "\t[global::System.Runtime.CompilerServices.CompilerGeneratedAttribute()]\n"
		<< "\t[global::System.CodeDom.Compiler.GeneratedCodeAttribute(\"Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator\", \"10.0.0.0\")]\n"
		<< "\tinternal sealed partial class Settings : global::System.Configuration.ApplicationSettingsBase\n"
		<< "\t{\n"
		<< "\t\tprivate static Settings defaultInstance = ((Settings)(global::System.Configuration.ApplicationSettingsBase.Synchronized(new Settings())));\n"
		<< "\n"
		<< "\t\tpublic static Settings Default\n"
		<< "\t\t{\n"
		<< "\t\t\tget\n"
		<< "\t\t\t{\n"
		<< "\t\t\t\treturn defaultInstance;\n"
		<< "\t\t\t}\n"
		<< "\t\t}\n"
		<< "\t}\n"
		<< "}\n";
	
	std::ofstream settings(directory.resolve(Paths::get(sysdir() + "-build", "Properties", "Settings.settings")).toString().c_str());
	settings
		<< "<?xml version='1.0' encoding='utf-8'?>\n"
		<< "<SettingsFile xmlns=\"uri:settings\" CurrentProfile=\"(Default)\">\n"
		<< "<Profiles>\n"
		<< "<Profile Name=\"(Default)\" />\n"
		<< "</Profiles>\n"
		<< "<Settings />\n"
		<< "</SettingsFile>\n";
}

std::string WpfExporter::backendDir() {
	return "WPF";
}

void WpfExporter::exportCsProj(UUID projectUuid) {
	writeFile(directory.resolve(Paths::get(sysdir() + "-build", "Project.csproj")));
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
			includeFiles(directory.resolve(Paths::get(sysdir() + "-build", "Sources", "src")), directory.resolve(sysdir() + "-build"));
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
	copyFile(from, directory.resolve(sysdir()).resolve(to.toString() + ".wav"));
}

void WpfExporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	Files::createDirectories(directory.resolve(sysdir()).resolve(to.toString()).parent());
	convert(from, directory.resolve(sysdir()).resolve(to.toString() + ".mp4"), aacEncoder);
}

void WpfExporter::copyVideo(kake::Platform platform, kake::Path from, kake::Path to, std::string mp4Encoder, std::string webmEncoder, std::string wmvEncoder) {
	Files::createDirectories(directory.resolve(sysdir()).resolve(to.toString()).parent());
	convert(from, directory.resolve(sysdir()).resolve(to.toString() + ".wmv"), wmvEncoder);
}
