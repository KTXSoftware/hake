#pragma once

#include "KhaExporter.h"
#include "Path.h"

namespace hake {
	class Html5Exporter : public KhaExporter {
	public:
		Html5Exporter(kmd::Path directory);
		std::string sysdir() override;
		void exportSolution(std::string name, kake::Platform platform, kmd::Path haxeDirectory, kmd::Path from) override;
		void copyImage(kake::Platform platform, kmd::Path from, kmd::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyVideo(kake::Platform platform, kmd::Path from, kmd::Path to, std::string h264Encoder, std::string webmEncoder, std::string wmvEncoder) override;
		void copyBlob(kake::Platform platform, kmd::Path from, kmd::Path to) override;
	private:
		kmd::Path directory;
		//NanoHTTPD server;
	};
}
