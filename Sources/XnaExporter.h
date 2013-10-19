#pragma once

#include "CSharpExporter.h"

namespace hake {
	class XnaExporter : public CSharpExporter {
	public:
		XnaExporter(kake::Path directory);
		std::string sysdir() override;
		void copyImage(kake::Platform platform, kake::Path from, kake::Path to, Json::Value& asset) override;
	protected:
		void exportResources();
		std::string backendDir() override;
		void exportSLN(kake::UUID projectUuid) override;
		void exportCsProj(kake::UUID projectUuid);
	private:
		std::vector<std::string> images;	
	};
}
