#pragma once

#include "KhaExporter.h"

namespace hake {
	class JavaExporter : public KhaExporter {
	public:
		JavaExporter(kake::Path directory);
		std::string sysdir() override;
		void exportSolution(std::string name, kake::Platform platform, kake::Path haxeDirectory, kake::Path from) override;
		void copyImage(kake::Platform platform, kake::Path from, kake::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyBlob(kake::Platform platform, kake::Path from, kake::Path to) override;
	protected:
		virtual std::string backend();
		virtual void exportEclipseProject();
		kake::Path directory;
	};
}
