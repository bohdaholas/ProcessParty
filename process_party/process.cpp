#include <iostream>
#include <process_party/common.h>
#include <process_party/process.h>

#if IS_WINDOWS
#include <windows.h>
#elif IS_LINUX
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <unistd.h>
#include <sys/wait.h>
#include "process_party/process/redirection_manager.h"

#elif IS_MACOS
#endif

using std::cout, std::cerr, std::endl;

NUM_T process_party::process::launch_process(const std::string &cmd,
                                           bool wait_to_finish,
                                           const redirection_manager &redirection_manager,
                                           char **environment) {
#if IS_WINDOWS
    DWORD status_code = EXIT_SUCCESS;
    bool error_occurred = false;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    LPCSTR cmd_str = cmd.c_str();
    int creation_flags = 0;
//    if (!wait_to_finish) {
//        creation_flags = (CREATE_DEFAULT_ERROR_MODE | CREATE_NO_WINDOW | DETACHED_PROCESS);
//    }

    if (!CreateProcess(nullptr, // No module name (use command line)
                       (LPSTR) cmd_str, // Command line
                       nullptr, // Process handle not inheritable
                       nullptr, // Thread handle not inheritable
                       FALSE, // Set handle inheritance to FALSE
                       CREATE_NEW_CONSOLE, // No creation flags
                       nullptr, // Use parent’ s environment block
                       nullptr, // Use parent’ s starting directory
                       &si, // Pointer to STARTUPINFO structure
                       &pi) // Pointer to PROCESS_INFORMATION structure
            ) {
        status_code = GetLastError();
        error_occurred = true;
    }
//    if (wait_to_finish) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        if (!error_occurred) {
            GetExitCodeProcess(pi.hProcess, &status_code);
        }
//    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
#elif IS_LINUX
    int status_code = EXIT_SUCCESS;
    pid_t pid = fork();

    if (pid == UNIX_ERR_CODE) {
        cerr << "Failed to fork()" << endl;
        return EXIT_FAILURE;
    } else if (pid > 0) {
        // Parent process
        if (wait_to_finish) {
            if (waitpid(pid, &status_code, 0) != -1) {
                if (WIFEXITED(status_code)) {
                    int returned = WEXITSTATUS(status_code);
                    printf("Exited normally with status_code %d\n", returned);
                } else if (WIFSIGNALED(status_code)) {
                    int signum = WTERMSIG(status_code);
                    printf("Exited due to receiving signal %d\n", signum);
                } else if (WIFSTOPPED(status_code)) {
                    int signum = WSTOPSIG(status_code);
                    printf("Stopped due to receiving signal %d\n", signum);
                } else {
                    printf("Something strange just happened.\n");
                }
            } else {
                perror("waitpid() failed");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        // Child process
        std::vector<const char *> arg_for_c;
        std::vector<std::string> args;
        boost::split(args, cmd, boost::is_any_of(" "));
        for (const auto &s: args) {
            arg_for_c.push_back(s.c_str());
        }
        arg_for_c.push_back(nullptr);
        redirection_manager.redirect();
        execvpe(args.at(0).c_str(),
                const_cast<char *const *>(arg_for_c.data()),
                environment);

        cerr << "Error occured when launching a program" << endl;
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status_code)) {
        return WEXITSTATUS(status_code);
    }
#elif IS_MACOS
#endif
    return status_code;
}

std::string process_party::process::get_cmd(const std::string &exe_path,
                                            const std::vector<std::string> &args) {
    std::stringstream ss;

    ss << exe_path << " ";
    for (const auto &arg: args) {
        ss << arg << " ";
    }

    std::string cmd = ss.str();
    cmd.pop_back();
    return cmd;
}

std::string
process_party::process::get_cmd(const std::filesystem::path &exe_path,
                                const std::vector<std::string> &args) {
    return get_cmd(exe_path.string(), args);
}

