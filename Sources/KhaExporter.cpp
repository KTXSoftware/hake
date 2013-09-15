#include "KhaExporter.h"
#include "Files.h"

using namespace hake;
using namespace kake;

KhaExporter::KhaExporter() : width(640), height(480) {

}

std::string KhaExporter::getCurrentDirectoryName(kake::Path directory) {
	return directory.getFileName();
}

void KhaExporter::copyFile(kake::Path from, kake::Path to) {
	kake::Files::copy(from, to, true);
}

void KhaExporter::copyDirectory(kake::Path from, kake::Path to) {
	createDirectory(to);
	for (auto file : kake::Files::newDirectoryStream(from)) {
		if (kake::Files::isDirectory(file)) copyDirectory(file, to.resolve(file));
		else copyFile(file, to.resolve(file));
	}
}

void KhaExporter::createDirectory(kake::Path dir) {
	if (!kake::Files::exists(dir)) kake::Files::createDirectories(dir);
}

void KhaExporter::setWidthAndHeight(int width, int height) {
	this->width = width;
	this->height = height;
}

void KhaExporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) { }
void KhaExporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) { }
void KhaExporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) { }
void KhaExporter::copyBlob(Platform platform, Path from, Path to) { }
