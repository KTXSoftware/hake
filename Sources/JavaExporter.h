#pragma once

#include "KhaExporter.h"

namespace hake {
	class JavaExporter : public KhaExporter {
	public:
		JavaExporter(kake::Path directory);
		void exportSolution(kake::Platform platform, kake::Path haxeDirectory) override;
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
