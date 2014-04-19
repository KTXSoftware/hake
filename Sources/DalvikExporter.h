#pragma once

#include "JavaExporter.h"

namespace hake {
	class DalvikExporter : public JavaExporter {
	public:
		DalvikExporter(kmd::Path directory);
		std::string sysdir() override;
		void copyImage(kake::Platform platform, kmd::Path from, kmd::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyBlob(kake::Platform platform, kmd::Path from, kmd::Path to) override;
	protected:
		std::string backend() override;
		void exportEclipseProject() override;
	};
}
