#include "DalvikExporter.h"
#include "Ball.h"
#include "ImageTool.h"
#include "SoundTool.h"

using namespace hake;
using namespace kake;

DalvikExporter::DalvikExporter(Path directory) : JavaExporter(directory) {

}

std::string DalvikExporter::backend() {
	return "Android";
}

std::string DalvikExporter::sysdir() {
	return "dalvik";
}

void DalvikExporter::exportEclipseProject() {
	writeFile(directory.resolve(Paths::get(sysdir(), ".classpath")));
	p("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	p("<classpath>");
		p("<classpathentry kind=\"src\" path=\"gen\"/>", 1);
		p("<classpathentry kind=\"src\" path=\"Sources/src\"/>", 1);
		p("<classpathentry kind=\"con\" path=\"com.android.ide.eclipse.adt.ANDROID_FRAMEWORK\"/>", 1);
		p("<classpathentry kind=\"output\" path=\"bin/classes\"/>", 1);
	p("</classpath>");
	closeFile();
		
	writeFile(directory.resolve(Paths::get(sysdir(), ".project")));
	p("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
	p("<projectDescription>");
		p("<name>" + getCurrentDirectoryName(directory) + "</name>", 1);
		p("<comment></comment>", 1);
		p("<projects>", 1);
		p("</projects>", 1);
		p("<buildSpec>", 1);
			p("<buildCommand>", 2);
				p("<name>com.android.ide.eclipse.adt.ResourceManagerBuilder</name>", 3);
				p("<arguments>", 3);
				p("</arguments>", 3);
			p("</buildCommand>", 2);
			p("<buildCommand>", 2);
				p("<name>com.android.ide.eclipse.adt.PreCompilerBuilder</name>", 3);
				p("<arguments>", 3);
				p("</arguments>", 3);
			p("</buildCommand>", 2);
			p("<buildCommand>", 2);
				p("<name>org.eclipse.jdt.core.javabuilder</name>", 3);
				p("<arguments>", 3);
				p("</arguments>", 3);
			p("</buildCommand>", 2);
			p("<buildCommand>", 2);
				p("<name>com.android.ide.eclipse.adt.ApkBuilder</name>", 3);
				p("<arguments>", 3);
				p("</arguments>", 3);
			p("</buildCommand>", 2);
		p("</buildSpec>", 1);
		p("<natures>", 1);
			p("<nature>com.android.ide.eclipse.adt.AndroidNature</nature>", 2);
			p("<nature>org.eclipse.jdt.core.javanature</nature>", 2);
		p("</natures>", 1);
	p("</projectDescription>");
	closeFile();
		
	writeFile(directory.resolve(Paths::get(sysdir(), "AndroidManifest.xml")));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<manifest xmlns:android=\"http://schemas.android.com/apk/res/android\" package=\"kha.android\" android:versionCode=\"1\" android:versionName=\"1.0\">");
		p("<application android:icon=\"@drawable/icon\" android:label=\"@string/app_name\">", 1);
			p("<activity android:label=\"@string/app_name\" android:screenOrientation=\"landscape\" android:name=\"kha.android.Game\" android:theme=\"@android:style/Theme.NoTitleBar.Fullscreen\">", 2);
				p("<intent-filter>", 3);
					p("<action android:name=\"android.intent.action.MAIN\" />", 4);
					p("<category android:name=\"android.intent.category.LAUNCHER\" />", 4);
				p("</intent-filter>", 3);
			p("</activity>", 2);
		p("</application>", 1);
	p("</manifest>");
	closeFile();
		
	writeFile(directory.resolve(Paths::get(sysdir(), "proguard.cfg")));
	p("-optimizationpasses 5");
	p("-dontusemixedcaseclassnames");
	p("-dontskipnonpubliclibraryclasses");
	p("-dontpreverify");
	p("-verbose");
	p("-optimizations !code/simplification/arithmetic,!field/*,!class/merging/*");
	p();
	p("-keep public class * extends android.app.Activity");
	p("-keep public class * extends android.app.Application");
	p("-keep public class * extends android.app.Service");
	p("-keep public class * extends android.content.BroadcastReceiver");
	p("-keep public class * extends android.content.ContentProvider");
	p("-keep public class * extends android.app.backup.BackupAgentHelper");
	p("-keep public class * extends android.preference.Preference");
	p("-keep public class com.android.vending.licensing.ILicensingService");
	p();
	p("-keepclasseswithmembernames class * {");
		p("native <methods>;", 1);
	p("}");
	p();
	p("-keepclasseswithmembernames class * {");
		p("public <init>(android.content.Context, android.util.AttributeSet);", 1);
	p("}");
	p();
	p("-keepclasseswithmembernames class * {");
		p("public <init>(android.content.Context, android.util.AttributeSet, int);", 1);
	p("}");
	p();
	p("-keepclassmembers enum * {");
	p("public static **[] values();");
	p("public static ** valueOf(java.lang.String);");
	p("}");
	p();
	p("-keep class * implements android.os.Parcelable {");
		p("public static final android.os.Parcelable$Creator *;", 1);
	p("}");
	closeFile();
		
	writeFile(directory.resolve(Paths::get(sysdir(), "project.properties")));
	p("target=android-7");
	closeFile();
		
	createDirectory(directory.resolve(Paths::get(sysdir(), ".settings")));
		
	writeFile(directory.resolve(Paths::get(sysdir(), ".settings", "org.eclipse.jdt.core.prefs")));
	p("#Thu Oct 20 20:02:57 CEST 2011");
	p("eclipse.preferences.version=1");
	p("org.eclipse.jdt.core.compiler.codegen.inlineJsrBytecode=enabled");
	p("org.eclipse.jdt.core.compiler.codegen.targetPlatform=1.6");
	p("org.eclipse.jdt.core.compiler.codegen.unusedLocal=preserve");
	p("org.eclipse.jdt.core.compiler.compliance=1.6");
	p("org.eclipse.jdt.core.compiler.debug.lineNumber=generate");
	p("org.eclipse.jdt.core.compiler.debug.localVariable=generate");
	p("org.eclipse.jdt.core.compiler.debug.sourceFile=generate");
	p("org.eclipse.jdt.core.compiler.problem.assertIdentifier=error");
	p("org.eclipse.jdt.core.compiler.problem.enumIdentifier=error");
	p("org.eclipse.jdt.core.compiler.source=1.6");
	closeFile();

	createDirectory(directory.resolve(Paths::get(sysdir(), "res")));
	createDirectory(directory.resolve(Paths::get(sysdir(), "res", "drawable-hdpi")));
	createDirectory(directory.resolve(Paths::get(sysdir(), "res", "drawable-mdpi")));
	createDirectory(directory.resolve(Paths::get(sysdir(), "res", "drawable-ldpi")));
	
	Ball::the()->exportTo(directory.resolve(Paths::get(sysdir(), "res", "drawable-hdpi", "icon.png")), 72, 72, Color::transparent, directory);
	Ball::the()->exportTo(directory.resolve(Paths::get(sysdir(), "res", "drawable-mdpi", "icon.png")), 48, 48, Color::transparent, directory);
	Ball::the()->exportTo(directory.resolve(Paths::get(sysdir(), "res", "drawable-ldpi", "icon.png")), 36, 36, Color::transparent, directory);
	
	createDirectory(directory.resolve(Paths::get(sysdir(), "res", "layout")));
	
	writeFile(directory.resolve(Paths::get(sysdir(), "res", "layout", "main.xml")));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<LinearLayout xmlns:android=\"http://schemas.android.com/apk/res/android\" android:orientation=\"vertical\" android:layout_width=\"fill_parent\" android:layout_height=\"fill_parent\">");
		p("<TextView android:layout_width=\"fill_parent\" android:layout_height=\"wrap_content\" android:text=\"@string/hello\" />", 1);
	p("</LinearLayout>");
	closeFile();
	
	createDirectory(directory.resolve(Paths::get(sysdir(), "res", "values")));
	
	writeFile(directory.resolve(Paths::get(sysdir(), "res", "values", "strings.xml")));
	p("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	p("<resources>");
		p("<string name=\"hello\">Hello World!</string>", 1);
		p("<string name=\"app_name\">" + getCurrentDirectoryName(directory) + "</string>", 1);
	p("</resources>");
	closeFile();
	
	createDirectory(directory.resolve(Paths::get(sysdir(), "gen")));
}

void DalvikExporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	convertSound(from, directory.resolve(Paths::get(sysdir(), "assets", to.toString() + ".ogg")), oggEncoder);
}

void DalvikExporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) {
	copyFile(from, directory.resolve(Paths::get(sysdir(), "assets", to.toString() + ".wav")));
}

void DalvikExporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) {
	exportImage(from, directory.resolve(Paths::get(sysdir(), "assets")).resolve(to), asset);
}

void DalvikExporter::copyBlob(Platform platform, Path from, Path to) {
	copyFile(from, directory.resolve(Paths::get(sysdir(), "assets")).resolve(to));
}
