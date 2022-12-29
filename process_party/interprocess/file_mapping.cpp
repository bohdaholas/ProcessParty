#include <unistd.h>
#include <stdexcept>
#include <process_party/interprocess.h>
#include "file_mapping.h"

process_party::interprocess::file_mapping::file_mapping(
        const std::string &filename,
        access_mode_t access_mode,
        creation_mode_t creation_mode) :
        filename{filename},
        access_mode{access_mode},
        creation_mode{creation_mode}
{
    int o_flags = get_creation_mode(creation_mode, ipc_file);
    int fd = open(filename.c_str(), o_flags, access_mode);
    if (fd < 0) {
        throw std::runtime_error("unable to open a file for ipc");
    }
    file_descriptor = fd;
    ipc_type = ipc_file;
}

process_party::interprocess::file_mapping::~file_mapping() {

}

void
process_party::interprocess::file_mapping::truncate(size_t size)
{
    ftruncate(file_descriptor, (int) size);
    file_size = size;
}

const std::string &
process_party::interprocess::file_mapping::get_name() const noexcept {
    return filename;
}

size_t process_party::interprocess::file_mapping::get_size() const noexcept {
    return file_size;
}

access_mode_t
process_party::interprocess::file_mapping::get_mode() const noexcept {
    return access_mode;
}

int
process_party::interprocess::file_mapping::get_file_descriptor() const noexcept
{
    return file_descriptor;
}

bool process_party::interprocess::file_mapping::remove(
        const std::string &filename) {
    return std::remove(filename.c_str()) == EXIT_SUCCESS;
}
