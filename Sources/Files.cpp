#include "Files.h"
#include "String.h"
#ifdef SYS_WINDOWS
#include <Windows.h>
#include <Shlobj.h>
#endif
#ifdef SYS_LINUX
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <errno.h>
#endif
#ifdef SYS_OSX
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <errno.h>
#endif

using namespace kake;

bool Files::exists(Path path) {
#ifdef SYS_WINDOWS
	return GetFileAttributesA(path.toString().c_str()) != INVALID_FILE_ATTRIBUTES;
#endif
#ifdef SYS_LINUX
	struct stat sts;
	return (stat (path.path.c_str(), &sts)) != -1;
#endif
#ifdef SYS_OSX
	struct stat sts;
	return (stat (path.path.c_str(), &sts)) != -1;
#endif
}

void Files::createDirectories(Path path) {
#ifdef SYS_WINDOWS
	SHCreateDirectoryExA(nullptr, replace(path.toAbsolutePath().path, '/', '\\').c_str(), nullptr);
#endif
#ifdef SYS_LINUX
	mkdir(path.toString().c_str(), 0700);
	char* p;
	char file_path[1001];
	std::strcpy(file_path, path.toString().c_str());
	std::strcat(file_path, "/");
	for (p = std::strchr(file_path + 1, '/'); p; p = strchr(p + 1, '/')) {
		*p='\0';
		if (mkdir(file_path, 0700) == -1) {
			printf("%s\n", strerror(errno));
			if (errno != EEXIST) { *p = '/'; return; }
		}
		*p = '/';
	}
#endif
#ifdef SYS_OSX
	char* p;
	char file_path[1001];
	std::strcpy(file_path, path.path.c_str());
	std::strcat(file_path, "/");
	for (p = std::strchr(file_path + 1, '/'); p; p = strchr(p + 1, '/')) {
		*p='\0';
		if (mkdir(file_path, 0700) == -1) {
			if (errno != EEXIST) { *p = '/'; return; }
		}
		*p = '/';
	}
#endif
}

bool Files::isDirectory(Path path) {
#ifdef SYS_WINDOWS
	DWORD attribs = GetFileAttributesA(path.toString().c_str());
	if (attribs == INVALID_FILE_ATTRIBUTES) return false;
	return (attribs & FILE_ATTRIBUTE_DIRECTORY) != 0;
#endif
#ifdef SYS_LINUX
	struct stat st;
	return stat(path.path.c_str(), &st) == 0 && (st.st_mode & S_IFDIR) != 0;
#endif
#ifdef SYS_OSX
	struct stat st;
	return stat(path.path.c_str(), &st) == 0 && (st.st_mode & S_IFDIR) != 0;
#endif
}

void Files::copy(Path from, Path to, bool replace) {
	Files::createDirectories(to.parent());
#ifdef SYS_WINDOWS
	CopyFileA(from.toString().c_str(), to.toString().c_str(), replace ? FALSE : TRUE);
#endif
#ifdef SYS_LINUX
	pid_t pid = fork();
	if (pid == 0) {
		execl("/bin/cp", "/bin/cp", from.path.c_str(), to.path.c_str(), (char *)0);
	}
#endif
#ifdef SYS_OSX
	pid_t pid = fork();
	if (pid == 0) {
		execl("/bin/cp", "/bin/cp", from.path.c_str(), to.path.c_str(), (char *)0);
	}
#endif
}

std::vector<Path> Files::newDirectoryStream(Path path) {
#ifdef SYS_WINDOWS
	std::vector<Path> files;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA ffd;
	hFind = FindFirstFileA((path.toString() + "\\*").c_str(), &ffd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (strcmp(ffd.cFileName, ".") != 0 && strcmp(ffd.cFileName, "..") != 0) files.push_back(path.resolve(ffd.cFileName));
		}
		while (FindNextFileA(hFind, &ffd));
	}
	return files;
#endif
#ifdef SYS_LINUX
	std::vector<Path> files;
	struct dirent* dir;
	DIR* d = opendir(path.path.c_str());
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) files.push_back(path.resolve(dir->d_name));
		}
		closedir(d);
	}
	return files;
#endif
#ifdef SYS_OSX
	std::vector<Path> files;
	struct dirent* dir;
	DIR* d = opendir(path.path.c_str());
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) files.push_back(path.resolve(dir->d_name));
		}
		closedir(d);
	}
	return files;
#endif
}
