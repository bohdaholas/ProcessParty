#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdexcept>
#include <process_party/interprocess.h>
#include "mapped_region.h"

process_party::interprocess::mapped_region::mapped_region(
        const process_party::interprocess::MemoryMappable &ipc_obj,
        size_t offset,
        size_t region_length)
{
    if (offset + region_length > ipc_obj.get_size()) {
        throw std::runtime_error("Invalid region bounds");
    }
    ipc_type = ipc_obj.get_ipc_type();
    if (ipc_type == ipc_shared_memory) {
        address = shmat(ipc_obj.get_shared_block_id(), nullptr, 0);
    } else if (ipc_type == ipc_file) {
        address = mmap(nullptr,
                       region_length,
                       PROT_READ | PROT_WRITE,
                       MAP_SHARED,
                       ipc_obj.get_file_descriptor(),
                       (int) offset);
    } else if (ipc_type == ipc_anonymous) {
        address = mmap(nullptr,
                       region_length,
                       PROT_READ | PROT_WRITE,
                       MAP_SHARED | MAP_ANONYMOUS,
                       -1,
                       (int) offset);
    }
    if (address == MAP_FAILED) {
        throw std::runtime_error("failed to set up address for ipc");
    }
    region_start = region_end = reinterpret_cast<size_t>(address);
    region_start += offset;
    region_end += ipc_obj.get_size();
}

process_party::interprocess::mapped_region::~mapped_region() {
    if (ipc_type == ipc_shared_memory && shmdt(address) == IPC_ERR) {
//        throw std::runtime_error("coudn't detach block");
    } else if ((ipc_type == ipc_file || ipc_type == ipc_anonymous) &&
                munmap(get_address(), get_size()) == IPC_ERR) {
//        throw std::runtime_error("coudn't detach block");
    }
}

std::size_t
process_party::interprocess::mapped_region::get_size() const noexcept {
    return region_end - region_start;
}

void *process_party::interprocess::mapped_region::get_address() const noexcept {
    return address;
}

bool process_party::interprocess::mapped_region::flush() const {
    if (ipc_type == ipc_file) {
        return msync(get_address(), get_size(), MS_SYNC) == EXIT_SUCCESS;
    }
    return true;
}
