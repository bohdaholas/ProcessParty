#include <iostream>
#include <process_party/process.h>

using std::cout, std::cerr, std::endl;

NUM_T process_party::process::system(const std::string &cmd) {
    return launch_process(cmd, true);
}

NUM_T process_party::process::system(const std::string &cmd, const redirection_manager &redirection_manager) {
    return launch_process(cmd, true, redirection_manager);
}

NUM_T process_party::process::system(const std::string &exe_path,
                                   const std::vector<std::string> &args) {
    std::string cmd = get_cmd(exe_path, args);
    return process_party::process::system(cmd, redirection_manager{});
}

NUM_T process_party::process::system(const std::filesystem::path &exe_path,
                                   const std::vector<std::string> &args) {
    std::string cmd = get_cmd(exe_path, args);
    return process_party::process::system(cmd, redirection_manager{});
}

NUM_T process_party::process::system(const std::string &exe_path,
                                   const std::vector<std::string> &args,
                                   const redirection_manager &redirection_manager) {
    std::string cmd = get_cmd(exe_path, args);
    return process_party::process::system(cmd, redirection_manager);
}
