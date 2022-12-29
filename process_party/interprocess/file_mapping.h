#ifndef PROCESS_PARTY_FILE_MAPPING_H
#define PROCESS_PARTY_FILE_MAPPING_H

#include <process_party/common.h>
#include <process_party/interprocess/shared_memory.h>
#include <string>

//namespace process_party::interprocess {
//    class mapped_region {
//    public:
//        mapped_region() = delete;
//        mapped_region(const shared_memory_object& shm_obj,
//                      access_mode_t access_mode);
//        mapped_region(const shared_memory_object& shm_obj,
//                      access_mode_t access_mode,
//                      size_t offset);
//        mapped_region(const shared_memory_object& shm_obj,
//                      access_mode_t access_mode,
//                      size_t offset,
//                      size_t size);
//
//        virtual ~mapped_region();
//
//        std::size_t get_size() const noexcept;
//        void * get_address() const noexcept;
//        access_mode_t get_mode() const noexcept;
//        bool flush(std::size_t = 0, std::size_t = 0, bool = true);
//        bool shrink_by(std::size_t, bool = true);
//        bool advise();
//        static std::size_t get_page_size() noexcept;
//    private:
//        size_t region_start;
//        size_t region_end;
//        void *address;
//        access_mode_t access_mode;
//    };
//}
//
#endif //PROCESS_PARTY_FILE_MAPPING_H
