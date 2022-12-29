#include <process_party/interprocess.h>
#include "memory_mappable.h"


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
    return 0;
}

access_mode_t
process_party::interprocess::MemoryMappable::get_mode() const noexcept
{
    return write_only;
}
