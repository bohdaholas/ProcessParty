#ifndef PROCESS_PARTY_MEMORY_MAPPABLE_H
#define PROCESS_PARTY_MEMORY_MAPPABLE_H

#include <process_party/common.h>
#include <string>

namespace process_party::interprocess {
    class MemoryMappable {
    public:
        virtual const std::string &get_name() const noexcept;
        virtual size_t get_size() const noexcept;
        virtual int get_shared_block_id() const noexcept;
        virtual access_mode_t get_mode() const noexcept;
    };
}

#endif //PROCESS_PARTY_MEMORY_MAPPABLE_H
