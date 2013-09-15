#pragma once

#include "CSharpExporter.h"

namespace hake {
	class PlayStationMobileExporter : public CSharpExporter {
	public:
		PlayStationMobileExporter(kake::Path directory);
		void copyImage(kake::Platform platform, kake::Path from, kake::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyBlob(kake::Platform platform, kake::Path from, kake::Path to) override;
	protected:
		std::string backendDir() override;
		void exportSLN(kake::UUID projectUuid) override;
		void exportResources() override;
		void exportCsProj(kake::UUID projectUuid) override;
	private:
		std::vector<kake::Path> files;
	};
}
