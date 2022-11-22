#ifndef PROCESS_PARTY_PROCESS_H
#define PROCESS_PARTY_PROCESS_H

#include <process_party/process/system.h>
#include <process_party/process/spawn.h>
#include <process_party/process/child.h>
#include <process_party/process/search_path.h>

namespace process_party::process {
    // Function used by system()/spawn() to launch a process
    // TODO: windows & macos support
    int launch_process(const std::string &cmd, bool wait_to_finish);
}

#endif //PROCESS_PARTY_PROCESS_H
