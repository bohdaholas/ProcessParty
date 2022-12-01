#ifndef PROCESS_PARTY_PROCESS_H
#define PROCESS_PARTY_PROCESS_H

#include <unistd.h>
#include <process_party/process/system.h>
#include <process_party/process/spawn.h>
#include <process_party/process/child.h>
#include <process_party/process/search_path.h>
#include <process_party/process/environment.h>

namespace process_party::process {
    // Function used by system()/spawn() to launch a process
    // TODO: windows & macos support
    int launch_process(const std::string &cmd,
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
