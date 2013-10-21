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
		static void copyFile(kake::Path from, kake::Path to);
		void setWidthAndHeight(int width, int height);
		virtual void copyImage(kake::Platform platform, kake::Path from, kake::Path to, Json::Value& asset);
		virtual void copyMusic(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder);
		virtual void copySound(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder);
		virtual void copyBlob(kake::Platform platform, kake::Path from, kake::Path to);
		virtual std::vector<std::string> videoExtensions();
	protected:
		static std::string getCurrentDirectoryName(kake::Path directory);
		static void copyDirectory(kake::Path from, kake::Path to);
		static void createDirectory(kake::Path dir);
	};
}
