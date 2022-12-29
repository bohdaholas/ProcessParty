#include <process_party/interprocess.h>
#include "memory_mappable.h"

void
process_party::interprocess::MemoryMappable::truncate(size_t memory_region_size)
{

}

const std::string &
process_party::interprocess::MemoryMappable::get_name() const noexcept
{
    return "";
}

size_t process_party::interprocess::MemoryMappable::get_size() const noexcept
{
    return 0;
}

int
process_party::interprocess::MemoryMappable::get_shared_block_id() const noexcept
{
    return NOT_DEFINED;
}

access_mode_t
process_party::interprocess::MemoryMappable::get_mode() const noexcept
{
    return write_only;
}

int process_party::interprocess::MemoryMappable::get_ipc_type() const noexcept {
    return ipc_type;
}

int
process_party::interprocess::MemoryMappable::get_file_descriptor() const noexcept
{
    return NOT_DEFINED;
}
