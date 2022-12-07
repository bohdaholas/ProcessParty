#include <iostream>
#include <process_party/common.h>
#include <process_party/process.h>

using std::cout, std::cerr, std::endl;

NUM_T process_party::process::spawn(const std::string &cmd) {
    return launch_process(cmd, false);
}

NUM_T process_party::process::spawn(const std::string &exe_path,
                                   const std::vector<std::string> &args) {
    std::stringstream ss;

    ss << exe_path << " ";
    for (const auto &arg: args) {
        ss << arg << " ";
    }

    std::string cmd{ss.str()};
    cmd.pop_back();
    return process_party::process::spawn(cmd);
}

NUM_T process_party::process::spawn(const std::filesystem::path &exe_path,
                                   const std::vector<std::string> &args) {
    return process_party::process::spawn(exe_path.string(), args);
}

NUM_T process_party::process::spawn(const std::string &exe_path,
                                   const std::vector<std::string> &args,
                                   const std::vector<std::pair<int, int>> &redirection_list) {
    return 0;
}
