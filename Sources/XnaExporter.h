#pragma once

#include "CSharpExporter.h"

namespace hake {
	class XnaExporter : public CSharpExporter {
	public:
		XnaExporter(kmd::Path directory);
		std::string sysdir() override;
		void copyImage(kake::Platform platform, kmd::Path from, kmd::Path to, Json::Value& asset) override;
	protected:
		void exportResources();
		std::string backendDir() override;
		void exportSLN(kake::UUID projectUuid) override;
		void exportCsProj(kake::UUID projectUuid);
	private:
		std::vector<std::string> images;	
	};
}
