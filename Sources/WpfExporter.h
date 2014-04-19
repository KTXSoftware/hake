#pragma once

#include "CSharpExporter.h"

namespace hake {
	class WpfExporter : public CSharpExporter {
	public:
		WpfExporter(kmd::Path directory);
		std::string sysdir() override;
	protected:
		void exportResources();
		std::string backendDir() override;
		void exportCsProj(kake::UUID projectUuid) override;
		void copySound(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyMusic(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyVideo(kake::Platform platform, kmd::Path from, kmd::Path to, std::string mp4Encoder, std::string webmEncoder, std::string wmvEncoder) override;
	};
}
