#ifndef PROCESS_PARTY_MEMORY_MAPPABLE_H
#define PROCESS_PARTY_MEMORY_MAPPABLE_H

#include <process_party/common.h>
#include <string>

namespace process_party::interprocess {
    class MemoryMappable {
    public:
//        MemoryMappable() = delete;
//        virtual ~MemoryMappable();

        virtual void truncate(size_t memory_region_size) = 0;
        [[nodiscard]] const std::string &get_name() const noexcept;
        [[nodiscard]] size_t get_size() const noexcept;
        [[nodiscard]] access_mode_t get_mode() const noexcept;

    private:
        access_mode_t access_mode;
        std::string name;
        size_t memory_region_size = 0;
    };
}

#endif //PROCESS_PARTY_MEMORY_MAPPABLE_H
