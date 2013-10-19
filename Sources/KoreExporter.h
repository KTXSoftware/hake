#pragma once

#include "KhaExporter.h"

namespace hake {
	class KoreExporter : public KhaExporter {
	public:
		KoreExporter(kake::Path directory);
		std::string sysdir() override;
		void exportSolution(kake::Platform platform, kake::Path haxeDirectory, kake::Path from) override;
		void copyMusic(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyImage(kake::Platform platform, kake::Path from, kake::Path to, Json::Value& asset) override;
		void copyBlob(kake::Platform platform, kake::Path from, kake::Path to) override;
	private:
		kake::Path directory;
	};
}
