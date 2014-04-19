#pragma once

#include "KhaExporter.h"

namespace hake {
	class JavaExporter : public KhaExporter {
	public:
		JavaExporter(kmd::Path directory);
		std::string sysdir() override;
		void exportSolution(std::string name, kake::Platform platform, kmd::Path haxeDirectory, kmd::Path from) override;
		void copyImage(kake::Platform platform, kmd::Path from, kmd::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyBlob(kake::Platform platform, kmd::Path from, kmd::Path to) override;
	protected:
		virtual std::string backend();
		virtual void exportEclipseProject();
		kmd::Path directory;
	};
}
