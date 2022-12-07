#ifndef PROCESS_PARTY_PROCESS_H
#define PROCESS_PARTY_PROCESS_H

#include <process_party/common.h>
#include <process_party/process/system.h>
#include <process_party/process/spawn.h>
#include <process_party/process/child.h>
#include <process_party/process/search_path.h>
#include <process_party/process/environment.h>

#if IS_WINDOWS
#include <windows.h>
#endif

namespace process_party::process {
    // Function used by system()/spawn() to launch a process
    // TODO: check if works for macos
    NUM_T launch_process(const std::string &cmd,
                       bool wait_to_finish,
                       char **environment = environ);

    std::string get_cmd(const std::string &exe_path,
                        const std::vector<std::string> &args);
    std::string get_cmd(const std::filesystem::path &exe_path,
                        const std::vector<std::string> &args);
    std::string get_cmd(const std::string &exe_path,
                        const std::vector<std::string> &args,
                        const std::vector<std::pair<int, int>> &redirection_list);

}

#endif //PROCESS_PARTY_PROCESS_H
