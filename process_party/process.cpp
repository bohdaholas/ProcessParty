#include <iostream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <process_party/common.h>
#include <process_party/process.h>

#if IS_WINDOWS
#elif IS_LINUX
#include <unistd.h>
#include <sys/wait.h>
#elif IS_MACOS
#endif

using std::cout, std::cerr, std::endl;

int process_party::process::launch_process(const std::string &cmd, bool wait_to_finish) {
    int status_code = EXIT_SUCCESS;
    pid_t pid;

    signal(SIGCHLD, SIG_IGN);
#if IS_WINDOWS
#elif IS_LINUX
    pid = fork();

    if (pid == UNIX_ERR_CODE) {
        cerr << "Failed to fork()" << endl;
        return EXIT_FAILURE;
    } else if (pid > 0) {
        // Parent process
        if (wait_to_finish) {
            waitpid(pid, &status_code, 0);
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

        execvp(args.at(0).c_str(),
               const_cast<char *const *>(arg_for_c.data()));

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

std::string process_party::process::get_cmd(const std::string &exe_path,
                                            const std::vector<std::string> &args,
                                            const std::vector<std::pair<int, int>> &redirection_list) {
    return std::string();
}

