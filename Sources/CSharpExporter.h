#pragma once

#include "KhaExporter.h"
#include "UUID.h"

namespace hake {
	class CSharpExporter : public KhaExporter {
	public:
		CSharpExporter(kake::Path directory);
		void exportSolution(std::string name, kake::Platform platform, kake::Path haxeDirectory, kake::Path from) override;
		void copyImage(kake::Platform platform, kake::Path from, kake::Path to, Json::Value& asset) override;
		void copyMusic(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copySound(kake::Platform platform, kake::Path from, kake::Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) override;
		void copyBlob(kake::Platform platform, kake::Path from, kake::Path to) override;
	protected:
		void includeFiles(kake::Path dir, kake::Path baseDir);
		virtual std::string backendDir() = 0;
		virtual void exportResources() = 0;
		virtual void exportSLN(kake::UUID projectUuid);
		virtual void exportCsProj(kake::UUID projectUuid) = 0;
		kake::Path directory;
	};
}
