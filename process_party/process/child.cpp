#include <iostream>
#include <process_party/process.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <unistd.h>
#include "child.h"
#include "process_party/common.h"

#if IS_WINDOWS
#elif IS_LINUX
#include <sys/wait.h>
#elif IS_MACOS
#endif

using std::cout, std::cerr, std::endl;

process_party::process::child::child(const std::string &cmd) :
                                        cmd{cmd}, exit_code{0}, child_pid{0} {
    launch_child(cmd);
}

process_party::process::child::child(const std::string &exe_path,
                                     const std::vector<std::string> &args)
                                     : child(get_cmd(exe_path, args)) {}

process_party::process::child::child(const std::filesystem::path &exe_path,
                                     const std::vector<std::string> &args)
                                     : child(get_cmd(exe_path, args)) {}

process_party::process::child::child(const std::string &exe_path,
                                     const std::vector<std::string> &args,
                                     const std::vector<std::pair<int, int>> &redirection_list) {}

void process_party::process::child::launch_child(const std::string &cmd) {
#if IS_WINDOWS
#elif IS_LINUX
    pid_t pid = fork();

    if (pid == UNIX_ERR_CODE) {
        cerr << "Failed to fork()" << endl;
        return;
    } else if (pid > 0) {
        // Parent process
        child_pid = pid;
    } else {
        // Child process
        std::vector<const char *> arg_for_c;
        std::vector<std::string> args;
        boost::split(args, cmd, boost::is_any_of(" "));
        for (const auto &s: args) {
            arg_for_c.push_back(s.c_str());
        }
        arg_for_c.push_back(nullptr);

        execvp(args.at(0).c_str(),
               const_cast<char *const *>(arg_for_c.data()));

        cerr << "Error occured when launching a program" << endl;
        exit(EXIT_FAILURE);
    }
#elif IS_MACOS
#endif
}

bool process_party::process::child::running() {
#if IS_WINDOWS
#elif IS_LINUX
    int res = waitpid(child_pid, nullptr, WNOHANG);
    if (res == 0) {
        return true;
    } else {
        return false;
    }
#elif IS_MACOS
#endif
}

void process_party::process::child::detach() {
#if IS_WINDOWS
#elif IS_LINUX
    signal(SIGCHLD, SIG_IGN);
    exit_code = EXIT_SUCCESS;
#elif IS_MACOS
#endif
}

void process_party::process::child::wait() {
#if IS_WINDOWS
#elif IS_LINUX
    waitpid(child_pid, &exit_code, 0);
    if (WIFEXITED(exit_code)) {
        exit_code = WEXITSTATUS(exit_code);
    }
#elif IS_MACOS
#endif
}

int process_party::process::child::get_exit_code() const {
    return exit_code;
}

void process_party::process::child::terminate() const {
#if IS_WINDOWS
#elif IS_LINUX
    kill(child_pid, SIGTERM);
#elif IS_MACOS
#endif
}


