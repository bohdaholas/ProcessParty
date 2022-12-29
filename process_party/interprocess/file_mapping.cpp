#include <unistd.h>
#include <stdexcept>
#include <process_party/interprocess.h>
#include "file_mapping.h"

bool process_party::interprocess::file_mapping::is_file_ok(
        const std::string &filename,
        access_mode_t access_mode,
        creation_mode_t creation_mode)
{
    int o_flags = get_creation_mode(creation_mode, ipc_file);
    int fd = open(filename.c_str(), o_flags, access_mode);
    if (fd < 0) {
        return false;
    }
    close(fd);
    return true;
}

process_party::interprocess::file_mapping::file_mapping(
        const std::string &filename,
        access_mode_t access_mode,
        creation_mode_t creation_mode,
        bool destroy_on_exit) :
        filename{filename},
        access_mode{access_mode},
        creation_mode{creation_mode},
        destroy_on_exit{destroy_on_exit}
{
    if (!is_file_ok(filename, access_mode, creation_mode)) {
        throw std::runtime_error("unable to open a file for ipc");
    }
}

process_party::interprocess::file_mapping::~file_mapping() {

}

const std::string &
process_party::interprocess::file_mapping::get_name() const noexcept {
    return filename;
}

access_mode_t
process_party::interprocess::file_mapping::get_mode() const noexcept {
    return access_mode;
}

bool process_party::interprocess::file_mapping::remove(
        const std::string &filename) {
    return std::remove(filename.c_str()) == EXIT_SUCCESS;
}
