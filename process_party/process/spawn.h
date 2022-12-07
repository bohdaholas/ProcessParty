#ifndef PROCESS_PARTY_SPAWN_H
#define PROCESS_PARTY_SPAWN_H

#include <vector>
#include <filesystem>

namespace process_party::process {
    // single line command execution
    NUM_T spawn(const std::string &cmd);

    // exe-args style
    // command name is either string or std::path
    NUM_T spawn(const std::string &exe_path,
               const std::vector<std::string> &args);
    NUM_T spawn(const std::filesystem::path &exe_path,
               const std::vector<std::string> &args);

    // exe-args style with opportunity of I/O redirection
    // TODO: this function is not implemented :(
    NUM_T spawn(const std::string &path,
               const std::vector<std::string> &args,
               const std::vector<std::pair<int, int>> &redirection_list);
}

#endif //PROCESS_PARTY_SPAWN_H
