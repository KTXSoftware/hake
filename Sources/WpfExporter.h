#pragma once

#include "CSharpExporter.h"

namespace hake {
	class WpfExporter : public CSharpExporter {
	public:
		WpfExporter(kake::Path directory);
	protected:
		void exportResources();
		std::string backendDir() override;
		void exportCsProj(kake::UUID projectUuid) override;
		void copySound(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyMusic(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
	};
}