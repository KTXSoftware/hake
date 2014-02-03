#pragma once

#include "KhaExporter.h"
#include "Path.h"

namespace hake {
	class Html5Exporter : public KhaExporter {
	public:
		Html5Exporter(kake::Path directory);
		std::string sysdir() override;
		void exportSolution(std::string name, kake::Platform platform, kake::Path haxeDirectory, kake::Path from) override;
		void copyImage(kake::Platform platform, kake::Path from, kake::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyVideo(kake::Platform platform, kake::Path from, kake::Path to, std::string h264Encoder, std::string webmEncoder, std::string wmvEncoder) override;
		void copyBlob(kake::Platform platform, kake::Path from, kake::Path to) override;
	private:
		kake::Path directory;
		//NanoHTTPD server;
	};
}
