#pragma once

#include "KhaExporter.h"
#include "UUID.h"

namespace hake {
	class CSharpExporter : public KhaExporter {
	public:
		CSharpExporter(kmd::Path directory);
		void exportSolution(std::string name, kake::Platform platform, kmd::Path haxeDirectory, kmd::Path from) override;
		void copyImage(kake::Platform platform, kmd::Path from, kmd::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kmd::Path from, kmd::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyBlob(kake::Platform platform, kmd::Path from, kmd::Path to) override;
	protected:
		void includeFiles(kmd::Path dir, kmd::Path baseDir);
		virtual std::string backendDir() = 0;
		virtual void exportResources() = 0;
		virtual void exportSLN(kake::UUID projectUuid);
		virtual void exportCsProj(kake::UUID projectUuid) = 0;
		kmd::Path directory;
	};
}
