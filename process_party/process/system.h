#ifndef PROCESS_PARTY_SYSTEM_H
#define PROCESS_PARTY_SYSTEM_H

#include <vector>
#include <filesystem>
#include "redirection_manager.h"
#include "process_party/common.h"

#if IS_WINDOWS
#include <windows.h>
#endif

namespace process_party::process {
    // single line command execution
    NUM_T system(const std::string &cmd);

    //  single line command with redirection
    NUM_T system(const std::string &cmd, const process_party::process::redirection_manager &redirection_manager);

    // exe-args style
    // command name is either string or std::path
    NUM_T system(const std::string &exe_path,
               const std::vector<std::string> &args);

    NUM_T system(const std::filesystem::path &exe_path,
               const std::vector<std::string> &args);

    // exe-args style with redirection
    NUM_T system(const std::string &exe_path, const std::vector<std::string> &args,
               const process_party::process::redirection_manager &redirection_manager);
}

#endif //PROCESS_PARTY_SYSTEM_H
