#include <unordered_map>
#include <climits>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <process_party/interprocess.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "memory_mappable.h"

//void
//process_party::interprocess::MemoryMappable::truncate(size_t region_size) {
//    if (shared_block_id > 0) {
//        throw std::runtime_error("already truncated");
//    }
//    if (region_size < getpagesize()) {
//        region_size = getpagesize();
//    }
//    shared_block_id = shmget(key,
//                              region_size,
//                             creation_mode | access_mode);
//    if (shared_block_id == IPC_ERR) {
//        throw std::runtime_error("Couldn't create block of shared memory");
//    }
//    shm_map[get_name()] = shared_block_id;
//    memory_region_size = region_size;
//}

const std::string &
process_party::interprocess::MemoryMappable::get_name() const noexcept {
    return name;
}

size_t
process_party::interprocess::MemoryMappable::get_size() const noexcept {
    return memory_region_size;
}

access_mode_t
process_party::interprocess::MemoryMappable::get_mode() const noexcept {
    return access_mode;
}
