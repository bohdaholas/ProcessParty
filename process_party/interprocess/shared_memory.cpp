#include <unordered_map>
#include <unistd.h>
#include <process_party/interprocess.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "shared_memory.h"

#if IS_LINUX
#include <sys/ipc.h>
#include <sys/shm.h>
#endif

static std::unordered_map<std::string, int> shm_map;

process_party::interprocess::shared_memory_object::shared_memory_object(
        const std::string &shm_obj_name,
        access_mode_t access_mode,
        creation_mode_t creation_mode) :
        shm_obj_name{shm_obj_name},
        access_mode{access_mode},
        creation_mode{creation_mode}
{
//    using namespace std;
    if (shm_map.count(shm_obj_name)) {
        throw std::runtime_error("shm file already exists in this process");
    }
    if (creation_mode == create_only && file_exists(shm_obj_name)) {
        throw std::runtime_error("shm file already exists");
    }
    if (creation_mode == open_only && !file_exists(shm_obj_name)) {
        throw std::runtime_error("shm file doesn't exist");
    }

    std::ofstream shm_file(shm_obj_name, std::ios_base::app);
    if (!shm_file) {
        throw std::runtime_error("coudn't create a file for key association");
    }
    shm_file.close();

    // proj_id=0 is always used to give the same key_t for the same shm_obj_name
#if IS_LINUX
    key = ftok(shm_obj_name.c_str(), 0);
    if (key == IPC_ERR) {
        throw std::runtime_error("Couldn't create key for block of shared memory");
    }
    shm_map[shm_obj_name] = NOT_DEFINED;
    ipc_type = ipc_shared_memory;
#endif
}

process_party::interprocess::shared_memory_object::~shared_memory_object() {
//    std::remove(shm_obj_name.c_str());
}

bool process_party::interprocess::shared_memory_object::remove(
        const std::string &shm_obj_name)
{
#if IS_LINUX
    auto it = shm_map.find(shm_obj_name);
    if (it != shm_map.end()) {
        bool res =  shmctl(shm_map.at(shm_obj_name), IPC_RMID, nullptr);
        shm_map.erase(it);
        return res;
    }
    return false;
#endif
}

void
process_party::interprocess::shared_memory_object::truncate(size_t region_size) {
#if IS_LINUX
    if (shared_block_id > 0) {
        throw std::runtime_error("already truncated");
    }
    if (region_size < getpagesize()) {
        region_size = getpagesize();
    }
    int flags = get_creation_mode(creation_mode, ipc_shared_memory) | access_mode;
    shared_block_id = shmget(key,
                              region_size,
                             flags);
    if (shared_block_id == IPC_ERR) {
        throw std::runtime_error("Couldn't create block of shared memory");
    }
    shm_map[get_name()] = shared_block_id;
    memory_region_size = region_size;
#endif
}

const std::string &
process_party::interprocess::shared_memory_object::get_name() const noexcept {
    return shm_obj_name;
}

size_t
process_party::interprocess::shared_memory_object::get_size() const noexcept {
    return memory_region_size;
}

int
process_party::interprocess::shared_memory_object::get_shared_block_id() const noexcept {
    return shared_block_id;
}

access_mode_t
process_party::interprocess::shared_memory_object::get_mode() const noexcept {
    return access_mode;
}
