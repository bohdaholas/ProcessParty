#ifndef PROCESS_PARTY_PROCESS_H
#define PROCESS_PARTY_PROCESS_H

#include <unistd.h>
#include <process_party/process/system.h>
#include <process_party/process/spawn.h>
#include <process_party/process/child.h>
#include <process_party/process/search_path.h>
#include <process_party/process/environment.h>
#include "process_party/process/redirection_manager.h"

#if IS_WINDOWS
#include <windows.h>
#elif IS_LINUX
#include <unistd.h>
#elif IS_MACOS
#endif

namespace process_party::process {
    // Function used by system()/spawn() to launch a process
    // TODO: check if works for macos
    NUM_T launch_process(const std::string &cmd,
                       bool wait_to_finish,
                       const redirection_manager &redirection_manager = process_party::process::redirection_manager{},
                       char **environment = environ);

    std::string get_cmd(const std::string &exe_path,
                        const std::vector<std::string> &args);
    std::string get_cmd(const std::filesystem::path &exe_path,
                        const std::vector<std::string> &args);
}

#endif //PROCESS_PARTY_PROCESS_H
