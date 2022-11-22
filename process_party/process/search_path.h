#ifndef PROCESS_PARTY_SEARCH_PATH_H
#define PROCESS_PARTY_SEARCH_PATH_H

#include <filesystem>

namespace process_party::process {
    // TODO: Windows
    std::filesystem::path search_path(const std::string &path);
}

#endif //PROCESS_PARTY_SEARCH_PATH_H
