#pragma once

#include "KhaExporter.h"
#include "Json.h"
#include "Path.h"

namespace hake {
	class FlashExporter : public KhaExporter {	
	public:
		FlashExporter(kake::Path directory);
		void exportSolution(kake::Path directory, kake::Platform platform) override;
		void copyMusic(kake::Path from, kake::Path to) override;
		void copySound(kake::Path from, kake::Path to) override;
		void copyImage(kake::Path from, kake::Path to, const Json::Value& asset) override;
		void copyBlob(kake::Path from, kake::Path to) override;
	private:
		kake::Path directory;
	};
}
