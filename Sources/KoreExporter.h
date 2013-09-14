#pragma once

#include "KhaExporter.h"

namespace hake {
	class KoreExporter : public KhaExporter {
	public:
		KoreExporter(kake::Path directory);
		void exportSolution(kake::Path directory, kake::Platform platform) override;
		void copyMusic(kake::Path from, kake::Path to) override;
		void copySound(kake::Path from, kake::Path to) override;
		void copyImage(kake::Path from, kake::Path to, const Json::Value& asset) override;
		void copyBlob(kake::Path from, kake::Path to) override;
	private:
		kake::Path directory;
	};
}
