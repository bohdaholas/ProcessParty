#include <sys/shm.h>
#include <unistd.h>
#include <stdexcept>
#include <process_party/interprocess.h>
#include "mapped_region.h"

//process_party::interprocess::mapped_region::mapped_region(
//        const process_party::interprocess::shared_memory_object &shm_obj,
//        access_mode_t access_mode)
//{
//    address = shmat(shm_obj.get_shared_block_id(), nullptr, 0);
//}
//
//process_party::interprocess::mapped_region::mapped_region(
//        const process_party::interprocess::shared_memory_object &shm_obj,
//        access_mode_t access_mode,
//        size_t offset) : mapped_region(shm_obj, access_mode)
//{
//    region_start = offset;
//    region_end = shm_obj.get_size();
//}
//
//process_party::interprocess::mapped_region::mapped_region(
//        const process_party::interprocess::shared_memory_object &shm_obj,
//        access_mode_t access_mode,
//        size_t offset,
//        size_t region_length) : mapped_region(shm_obj, access_mode)
//{
//    region_start = offset;
//    region_end = offset + region_length;
//}
//
//process_party::interprocess::mapped_region::~mapped_region() {
//    if (shmdt(address) != IPC_ERR) {
//        throw std::runtime_error("coudn't detach block");
//    }
//}
//
//std::size_t
//process_party::interprocess::mapped_region::get_size() const noexcept {
//    return region_end - region_start;
//}
//
//void *process_party::interprocess::mapped_region::get_address() const noexcept {
//    return address;
//}
//
//access_mode_t process_party::interprocess::mapped_region::get_mode() const noexcept {
//    return access_mode;
//}
//
//bool process_party::interprocess::mapped_region::flush(std::size_t, std::size_t, bool) {
//    return false;
//}
//
//bool process_party::interprocess::mapped_region::shrink_by(std::size_t, bool) {
//    return false;
//}
//
//bool process_party::interprocess::mapped_region::advise() {
//    return false;
//}
//
//std::size_t process_party::interprocess::mapped_region::get_page_size() noexcept {
//    return getpagesize();
//}
