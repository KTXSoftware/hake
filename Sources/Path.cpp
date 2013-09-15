#include "Path.h"
#include "String.h"
#include <sstream>

using namespace kake;

namespace {
	std::string concat(std::string a, std::string b) {
		while (a[a.size() - 1] == '/' || a[a.size() - 1] == '\\') a = a.substr(0, a.size() - 1);
		while (b[b.size() - 1] == '/' || b[b.size() - 1] == '\\') b = b.substr(0, b.size() - 1);
		return a + '/' + b;
	}
}

bool Path::startsWith(Path other) {
	std::string me = path;
	std::string he = other.path;
	if (he == ".") return true;
	if (me[0] == '.' && me[1] == '/') me = me.substr(2);
	if (he[0] == '.' && he[1] == '/') he = he.substr(2);
	for (unsigned i = 0; i < he.size(); ++i) {
		if (me[i] != he[i]) return false;
	}
	return true;
}

Path Path::relativize(Path other) {
	std::string me = path;
	std::string he = other.path;
	if (me == ".") return other;
	if (me[0] == '.' && me[1] == '/') me = me.substr(2);
	if (he[0] == '.' && he[1] == '/') he = he.substr(2);
	Path p;
	p.path = he.substr(me.size());
	while (p.path.size() > 0 && (p.path[0] == '/' || p.path[0] == '\\')) p.path = p.path.substr(1);
	return p;
}

Path Path::resolve(std::string subpath) {
	Path path;
	if (subpath == ".") path.path = this->path;
	else path.path = concat(this->path, subpath);
	return path;
}

Path Path::resolve(Path subpath) {
	Path path;
	if (subpath.path == ".") path.path = this->path;
	else path.path = concat(this->path, subpath.path);
	return path;
}

Path Path::parent() {
	if (this->path == ".") return toAbsolutePath().parent();
	else {
		for (int i = path.size() - 1; i >= 0; --i) {
			if (path[i] == '/' || path[i] == '\\') {
				return Paths::get(path.substr(0, i));
			}
		}
	}
	return *this;
}

std::string Path::getFileName() {
	for (int i = path.size() - 1; i >= 0; --i) {
		if (path[i] == '/' || path[i] == '\\') {
			return path.substr(i + 1);
		}
	}
	return path;
}

std::string Path::toString() {
	if (path[0] == '.' && path[1] == '/') return path.substr(2);
	else return path;
}

Path Paths::get(std::string a) {
	Path path;
	if (a[a.size() - 1] == '/' || a[a.size() - 1] == '\\') path.path = a.substr(0, a.size() - 1);
	else path.path = a;
	return path;
}

Path Paths::get(std::string a, std::string b) {
	Path path;
	if (startsWith(b, "./")) b = b.substr(2);
	if (a == ".") path.path = b;
	else path.path = concat(a, b);
	return path;
}

Path Paths::get(std::string a, std::string b, std::string c) {
	Path path;
	if (startsWith(b, "./")) b = b.substr(2);
	if (startsWith(c, "./")) c = c.substr(2);
	if (a == ".") path.path = concat(b, c);
	else path.path = concat(concat(a, b), c);
	return path;
}

Path Paths::get(std::string a, std::string b, std::string c, std::string d) {
	Path path;
	if (startsWith(b, "./")) b = b.substr(2);
	if (startsWith(c, "./")) c = c.substr(2);
	if (startsWith(d, "./")) d = d.substr(2);
	if (a == ".") path.path = concat(concat(b, c), d);
	else path.path = concat(concat(concat(a, b), c), d);
	return path;
}

#include "String.h"
#ifdef SYS_WINDOWS
#include <Windows.h>
#endif

Path Path::toAbsolutePath() {
#ifdef SYS_WINDOWS
	if (path[1] == ':') return *this;
	char buffer[1001];
	GetCurrentDirectoryA(1000, buffer);
	return Paths::get(replace(buffer, '\\', '/'), path);
#endif
#ifdef SYS_LINUX
	char buffer[1001];
	realpath(path.c_str(), buffer);
	return Paths::get(buffer);
#endif
#ifdef SYS_OSX
	char buffer[1001];
	realpath(path.c_str(), buffer);
	return Paths::get(buffer);
#endif
}
