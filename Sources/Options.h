#pragma once

#include <string>

namespace kake {
	enum VisualStudioVersion {
		VS2010,
		VS2012,
		VS2013
	};

	enum GraphicsApi {
		OpenGL,
		OpenGL2,
		Direct3D9,
		Direct3D11
	};

	namespace Options {
		bool usesPrecompiledHeaders();
		std::string getIntermediateDrive();
		GraphicsApi getGraphicsApi();
		VisualStudioVersion getVisualStudioVersion();
		bool compilation();

		void setPrecompiledHeaders(bool value);
		void setIntermediateDrive(std::string drive);
		void setGraphicsApi(std::string api);
		void setVisualStudioVersion(std::string vs);
		void setCompilation(bool value);
	}
}
