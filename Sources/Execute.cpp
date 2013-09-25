#include "Execute.h"
#include "String.h"

#ifdef SYS_WINDOWS
#include <Windows.h>
#endif

void hake::executeSync(std::string command, std::string env) {
#ifdef SYS_WINDOWS
	STARTUPINFOA startupInfo;
	PROCESS_INFORMATION processInfo;
	memset(&startupInfo, 0, sizeof(startupInfo));
	memset(&processInfo, 0, sizeof(processInfo));
	startupInfo.cb = sizeof(startupInfo);
	env = replace(env, '/', '\\');
	char* environment = new char[2000];
	for (int i = 0; i < 2000; ++i) environment[i] = 0;
	strcpy(environment, env.c_str());
	CreateProcessA(nullptr, (char*)command.c_str(), nullptr, nullptr, FALSE, CREATE_DEFAULT_ERROR_MODE, environment, nullptr, &startupInfo, &processInfo);
	WaitForSingleObject(processInfo.hProcess, INFINITE);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
#else
	system(command.c_str());
#endif
}
