#pragma once

#include "Exporter.h"
#include "Json.h"

namespace hake {
	class KhaExporter : public kake::Exporter {
	protected:
		int width;
		int height;
	public:
		KhaExporter();
		virtual std::string sysdir() = 0;
		static void copyFile(kmd::Path from, kmd::Path to);
		void setWidthAndHeight(int width, int height);
		virtual void copyImage(kake::Platform platform, kmd::Path from, kmd::Path to, Json::Value& asset);
		virtual void copyMusic(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder);
		virtual void copySound(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder);
		virtual void copyVideo(kake::Platform platform, kmd::Path from, kmd::Path to, std::string h264Encoder, std::string webmEncoder, std::string wmvEncoder);
		virtual void copyBlob(kake::Platform platform, kmd::Path from, kmd::Path to);
		virtual void addShader(std::string shader) { }
	protected:
		static std::string getCurrentDirectoryName(kmd::Path directory);
		static void copyDirectory(kmd::Path from, kmd::Path to);
		static void createDirectory(kmd::Path dir);
	};
}
