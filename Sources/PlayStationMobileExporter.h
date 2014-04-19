#pragma once

#include "CSharpExporter.h"

namespace hake {
	class PlayStationMobileExporter : public CSharpExporter {
	public:
		PlayStationMobileExporter(kmd::Path directory);
		std::string sysdir() override;
		void copyImage(kake::Platform platform, kmd::Path from, kmd::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyBlob(kake::Platform platform, kmd::Path from, kmd::Path to) override;
	protected:
		std::string backendDir() override;
		void exportSLN(kake::UUID projectUuid) override;
		void exportResources() override;
		void exportCsProj(kake::UUID projectUuid) override;
	private:
		std::vector<kmd::Path> files;
	};
}
