#include <iostream>
#include <process_party/process/system.h>
#include <process_party/common.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#if IS_WINDOWS
#elif IS_LINUX
#include <unistd.h>
#include <sys/wait.h>
#elif IS_MACOS
#endif

using std::cout, std::cerr, std::endl;

int process_party::process::system(const std::string &cmd) {
    int status_code;
    pid_t pid;
#if IS_WINDOWS
#elif IS_LINUX
    pid = fork();

    if (pid == UNIX_ERR_CODE) {
        cerr << "Failed to fork()" << endl;
        return EXIT_FAILURE;
    } else if (pid > 0) {
        // Parent process
        waitpid(pid, &status_code, 0);
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
        return EXIT_FAILURE;
    }

    if (WIFEXITED(status_code)) {
        return WEXITSTATUS(status_code);
    }
#elif IS_MACOS
#endif
    return status_code;
}

int process_party::process::system(const std::string &exe_path,
                                   const std::vector<std::string> &args) {
    std::stringstream ss;

    ss << exe_path << " ";
    for (const auto &arg: args) {
        ss << arg << " ";
    }

    std::string cmd{ss.str()};
    cmd.pop_back();
    return process_party::process::system(cmd);
}

int process_party::process::system(const std::filesystem::path &exe_path,
                                   const std::vector<std::string> &args)
{
    return system(exe_path.string(), args);
}

int process_party::process::system(const std::string &exe_path,
                                   const std::vector<std::string> &args,
                                   const std::vector<std::pair<int, int>> &redirection_list) {
    return 0;
}

