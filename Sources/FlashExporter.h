#pragma once

#include "KhaExporter.h"
#include "Json.h"
#include "Path.h"
#include <list>

namespace hake {
	class FlashExporter : public KhaExporter {	
	public:
		FlashExporter(kmd::Path directory, bool embedflashassets);
		std::string sysdir() override;
		void exportSolution(std::string name, kake::Platform platform, kmd::Path haxeDirectory, kmd::Path from) override;
		void copyMusic(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyVideo(kake::Platform platform, kmd::Path from, kmd::Path to, std::string h264Encoder, std::string webmEncoder, std::string wmvEncoder) override;
		void copyImage(kake::Platform platform, kmd::Path from, kmd::Path to, Json::Value& asset) override;
		void copyBlob(kake::Platform platform, kmd::Path from, kmd::Path to) override;
		void addShader(std::string shader) override;
	private:
		kmd::Path directory;
		bool embed;
		std::list<std::string> images;
		std::list<std::string> sounds;
		std::list<std::string> blobs;
	};
}
