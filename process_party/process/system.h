#ifndef PROCESS_PARTY_SYSTEM_H
#define PROCESS_PARTY_SYSTEM_H

#include <vector>
#include <filesystem>

#if IS_WINDOWS
#include <windows.h>
#endif

namespace process_party::process {
    // single line command execution
    NUM_T system(const std::string &cmd);

//    NUM_T system(const std::filesystem::path &exe_path);

    // exe-args style
    // command name is either string or std::path
    NUM_T system(const std::string &exe_path,
               const std::vector<std::string> &args);
    NUM_T system(const std::filesystem::path &exe_path,
               const std::vector<std::string> &args);

    // exe-args style with opportunity of I/O redirection
    // TODO: this function is not implemented :(
    NUM_T system(const std::string &path,
               const std::vector<std::string> &args,
               const std::vector<std::pair<int, int>> &redirection_list);
}

#endif //PROCESS_PARTY_SYSTEM_H
