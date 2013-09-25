#include "Execute.h"
#include "String.h"

#ifdef SYS_WINDOWS
#include <Windows.h>
#else
#include <errno.h>
#include <signal.h>
#endif

void hake::executeSync(std::string command, std::vector<std::string> arguments, std::string env) {
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
	//system(command.c_str());
	pid_t processId;
	int stat;
	if ((processId = fork()) == 0) {
		char* cmd = new char[2000];
		strcpy(cmd, command.c_str());
		
		char** argv = new char*[arguments.size() + 2];
		argv[0] = new char[1000];
		strcpy(argv[0], command.c_str());
		for (int i = 0; i < arguments.size(); ++i) {
			argv[i + 1] = new char[1000]; //leak
			strcpy(argv[i + 1], arguments[i].c_str());
		}
		argv[arguments.size() + 1] = 0;
		
		char* environment = new char[2000];
		for (int i = 0; i < 2000; ++i) environment[i] = 0;
		strcpy(environment, env.c_str());
		char* const envarray[] = {environment, 0};
		
		execve(cmd, argv, envarray);
		_exit(127);
	}
	if (processId == -1) {
        stat = -1; /* errno comes from fork() */
    }
	else {
        while (waitpid(processId, &stat, 0) == -1) {
            if (errno != EINTR) {
                stat = -1;
                break;
            }
        }
    }
	return; //stat
#endif
}
