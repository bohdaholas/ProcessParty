#ifndef PROCESS_PARTY_SYSTEM_H
#define PROCESS_PARTY_SYSTEM_H

#include <vector>
#include <filesystem>

namespace process_party::process {
    // single line command execution
    // TODO: windows & macos
    int system(const std::string &cmd);

    // exe-args style
    // command name is either string or std::path
    // TODO: windows & macos
    int system(const std::string &exe_path,
               const std::vector<std::string> &args);
    // TODO: windows & macos
    int system(const std::filesystem::path &exe_path,
               const std::vector<std::string> &args);

    // exe-args style with opportunity of I/O redirection
    // TODO: this function is not implemented :(
    int system(const std::string &path,
               const std::vector<std::string> &args,
               const std::vector<std::pair<int, int>> &redirection_list);
}

#endif //PROCESS_PARTY_SYSTEM_H
