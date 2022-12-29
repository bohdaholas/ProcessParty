#ifndef PROCESS_PARTY_FILE_MAPPING_H
#define PROCESS_PARTY_FILE_MAPPING_H

#include <string>
#include "memory_mappable.h"

namespace process_party::interprocess {
    class file_mapping : MemoryMappable {
    public:
        file_mapping() = delete;
        virtual ~file_mapping();
        explicit file_mapping(const std::string &filename,
                              access_mode_t access_mode = read_write,
                              creation_mode_t creation_mode = open_or_create,
                              bool destroy_on_exit = false);

        [[nodiscard]] const std::string &get_name() const noexcept override;
        [[nodiscard]] access_mode_t get_mode() const noexcept override;

        static bool remove(const std::string &shm_obj_name);
    private:
        key_t key;
        creation_mode_t creation_mode;
        access_mode_t access_mode;
        int shared_block_id = NOT_DEFINED;
        std::string filename;
        size_t memory_region_size = 0;
        bool destroy_on_exit;

        bool is_file_ok(const std::string &basicString, access_mode_t mode,
                        creation_mode_t mode1);
    };
}

#endif //PROCESS_PARTY_FILE_MAPPING_H
