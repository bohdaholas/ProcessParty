#include <iostream>
#include <process_party/common.h>
#include <process_party/process.h>

using std::cout, std::cerr, std::endl;

NUM_T process_party::process::spawn(const std::string &cmd) {
    return launch_process(cmd, false);
}

NUM_T process_party::process::spawn(const std::string &cmd, const redirection_manager &redirection_manager) {
    return launch_process(cmd, false, redirection_manager);
}

NUM_T process_party::process::spawn(const std::string &exe_path,
                                   const std::vector<std::string> &args) {
    return process_party::process::spawn(get_cmd(exe_path, args));
}

NUM_T process_party::process::spawn(const std::filesystem::path &exe_path,
                                   const std::vector<std::string> &args) {
    return process_party::process::spawn(get_cmd(exe_path, args));
}

NUM_T process_party::process::spawn(const std::string &exe_path,
                                   const std::vector<std::string> &args,
                                   const redirection_manager &redirection_manager) {
    return process_party::process::spawn(get_cmd(exe_path, args), redirection_manager);
}

NUM_T process_party::process::spawn(const std::filesystem::path &exe_path,
                                  const std::vector<std::string> &args,
                                  const redirection_manager &redirection_manager) {
    return process_party::process::spawn(get_cmd(exe_path, args), redirection_manager);
}