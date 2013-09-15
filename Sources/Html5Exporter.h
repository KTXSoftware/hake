#pragma once

#include "KhaExporter.h"
#include "Path.h"

namespace hake {
	class Html5Exporter : public KhaExporter {
	public:
		Html5Exporter(kake::Path directory);
		void exportSolution(kake::Platform platform, kake::Path haxeDirectory) override;
		void copyImage(kake::Platform platform, kake::Path from, kake::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyBlob(kake::Platform platform, kake::Path from, kake::Path to) override;
	private:
		kake::Path directory;
		//NanoHTTPD server;
	};
}
