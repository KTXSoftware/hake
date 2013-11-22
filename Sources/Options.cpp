#include "Options.h"
#include <iostream>

using namespace kake;

namespace {
	bool precompiledHeaders = false;
	std::string intermediateDrive;
	GraphicsApi gfxApi = Direct3D9;
	VisualStudioVersion visualStudio = VS2012;
	bool compile = true;
}

bool Options::usesPrecompiledHeaders() {
	return precompiledHeaders;
}

std::string Options::getIntermediateDrive() {
	return intermediateDrive;
}

GraphicsApi Options::getGraphicsApi() {
	return gfxApi;
}

VisualStudioVersion Options::getVisualStudioVersion() {
	return visualStudio;
}

bool Options::compilation() {
	return compile;
}

void Options::setPrecompiledHeaders(bool value) {
	precompiledHeaders = value;
}

void Options::setIntermediateDrive(std::string drive) {
	intermediateDrive = drive;
}

void Options::setGraphicsApi(std::string api) {
	if (api == "opengl") gfxApi = OpenGL;
	else if (api == "opengl2") gfxApi = OpenGL2;
	else if (api == "direct3d9") gfxApi = Direct3D9;
	else if (api == "direct3d11") gfxApi = Direct3D11;
	else std::cerr << "Unknown graphics api " << api << std::endl;
}

void Options::setVisualStudioVersion(std::string vs) {
	if (vs == "vs2010") visualStudio = VS2010;
	else if (vs == "vs2012") visualStudio = VS2012;
	else if (vs == "vs2013") visualStudio = VS2013;
	else std::cerr << "Unknown Visual Studio version " << vs << std::endl;
}

void Options::setCompilation(bool value) {
	compile = value;
}
