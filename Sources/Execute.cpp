#include "Execute.h"
#include "StringHelper.h"

#ifdef SYS_WINDOWS
#include <Windows.h>
#else
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	for (auto arg : arguments) command += " \"" + arg + "\"";
	CreateProcessA(nullptr, (char*)command.c_str(), nullptr, nullptr, FALSE, CREATE_DEFAULT_ERROR_MODE, env == "" ? nullptr : environment, nullptr, &startupInfo, &processInfo);
	WaitForSingleObject(processInfo.hProcess, INFINITE);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
#else
	//system(command.c_str());
	pid_t processId;
	int stat;
	struct sigaction sa, savintr, savequit;
	sigset_t saveblock;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigemptyset(&savintr.sa_mask);
	sigemptyset(&savequit.sa_mask);
	sigaction(SIGINT, &sa, &savintr);
	sigaction(SIGQUIT, &sa, &savequit);
	sigaddset(&sa.sa_mask, SIGCHLD);
	sigprocmask(SIG_BLOCK, &sa.sa_mask, &saveblock);
	if ((processId = fork()) == 0) {
		sigaction(SIGINT, &savintr, (struct sigaction *)0);
		sigaction(SIGQUIT, &savequit, (struct sigaction *)0);
		sigprocmask(SIG_SETMASK, &saveblock, (sigset_t *)0);

		char* cmd = new char[2000];
		strcpy(cmd, command.c_str());

		char** argv = new char*[arguments.size() + 2];
		argv[0] = new char[1000];
		strcpy(argv[0], command.c_str());
		for (size_t i = 0; i < arguments.size(); ++i) {
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
	sigaction(SIGINT, &savintr, (struct sigaction *)0);
	sigaction(SIGQUIT, &savequit, (struct sigaction *)0);
	sigprocmask(SIG_SETMASK, &saveblock, (sigset_t *)0);
	return; //stat
#endif
}
