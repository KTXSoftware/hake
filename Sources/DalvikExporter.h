#pragma once

#include "JavaExporter.h"

namespace hake {
	class DalvikExporter : public JavaExporter {
	public:
		DalvikExporter(kake::Path directory);
		std::string sysdir() override;
		void copyImage(kake::Platform platform, kake::Path from, kake::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyBlob(kake::Platform platform, kake::Path from, kake::Path to) override;
	protected:
		std::string backend() override;
		void exportEclipseProject() override;
	};
}
