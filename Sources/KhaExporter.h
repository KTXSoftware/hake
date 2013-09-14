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
		static void copyFile(kake::Path from, kake::Path to);
		void setWidthAndHeight(int width, int height);
		virtual void copyImage(kake::Path from, kake::Path to, const Json::Value& asset);
		virtual void copyMusic(kake::Path from, kake::Path to);
		virtual void copySound(kake::Path from, kake::Path to);
		virtual void copyBlob(kake::Path from, kake::Path to);
	protected:
		static std::string getCurrentDirectoryName(kake::Path directory);
		static void copyDirectory(kake::Path from, kake::Path to);
		static void createDirectory(kake::Path dir);
	};
}
