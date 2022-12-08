#include <iostream>
#include <process_party/common.h>
#include <process_party/process.h>

using std::cout, std::cerr, std::endl;

NUM_T process_party::process::spawn(const std::string &cmd) {
    return launch_process(cmd, false);
}

NUM_T process_party::process::spawn(const std::string &exe_path,
                                   const std::vector<std::string> &args) {
    std::string cmd = get_cmd(exe_path, args);
    return process_party::process::spawn(cmd);
}

NUM_T process_party::process::spawn(const std::filesystem::path &exe_path,
                                   const std::vector<std::string> &args) {
    std::string cmd = get_cmd(exe_path, args);
    return process_party::process::spawn(cmd);
}

NUM_T process_party::process::spawn(const std::string &exe_path,
                                   const std::vector<std::string> &args,
                                   const std::vector<std::pair<int, int>> &redirection_list) {
    return 0;
}
