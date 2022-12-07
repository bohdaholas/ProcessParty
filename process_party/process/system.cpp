#include <iostream>
#include <process_party/process.h>

using std::cout, std::cerr, std::endl;

NUM_T process_party::process::system(const std::string &cmd) {
    return launch_process(cmd, true);
}

//NUM_T process_party::process::system(const std::filesystem::path &exe_path) {
//    return launch_process(exe_path.string(), true);
//}

NUM_T process_party::process::system(const std::string &exe_path,
                                   const std::vector<std::string> &args) {
    std::string cmd = get_cmd(exe_path, args);
    return process_party::process::system(cmd);
}

NUM_T process_party::process::system(const std::filesystem::path &exe_path,
                                   const std::vector<std::string> &args) {
    std::string cmd = get_cmd(exe_path, args);
    return process_party::process::system(cmd);
}

NUM_T process_party::process::system(const std::string &exe_path,
                                   const std::vector<std::string> &args,
                                   const std::vector<std::pair<int, int>> &redirection_list) {
    return 0;
}
