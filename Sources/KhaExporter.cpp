#include "KhaExporter.h"
#include "Files.h"

using namespace kmd;
using namespace hake;
using namespace kake;

KhaExporter::KhaExporter() : width(640), height(480) {

}

std::string KhaExporter::getCurrentDirectoryName(kmd::Path directory) {
	return directory.getFileName();
}

void KhaExporter::copyFile(kmd::Path from, kmd::Path to) {
	kmd::Files::copy(from, to, true);
}

void KhaExporter::copyDirectory(kmd::Path from, kmd::Path to) {
	createDirectory(to);
	for (auto file : kmd::Files::newDirectoryStream(from)) {
		if (kmd::Files::isDirectory(file)) copyDirectory(file, to.resolve(file));
		else copyFile(file, to.resolve(file));
	}
}

void KhaExporter::createDirectory(kmd::Path dir) {
	if (!kmd::Files::exists(dir)) kmd::Files::createDirectories(dir);
}

void KhaExporter::setWidthAndHeight(int width, int height) {
	this->width = width;
	this->height = height;
}

void KhaExporter::copyImage(Platform platform, Path from, Path to, Json::Value& asset) { }
void KhaExporter::copyMusic(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) { }
void KhaExporter::copySound(Platform platform, Path from, Path to, std::string oggEncoder, std::string aacEncoder, std::string mp3Encoder) { }
void KhaExporter::copyVideo(kake::Platform platform, kmd::Path from, kmd::Path to, std::string mp4Encoder, std::string webmEncoder, std::string wmvEncoder) { }
void KhaExporter::copyBlob(Platform platform, Path from, Path to) { }
