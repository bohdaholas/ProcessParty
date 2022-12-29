#ifndef PROCESS_PARTY_FILE_MAPPING_H
#define PROCESS_PARTY_FILE_MAPPING_H

#include <string>
#include "memory_mappable.h"

namespace process_party::interprocess {
    class file_mapping : public MemoryMappable {
    public:
        file_mapping() = delete;
        virtual ~file_mapping();
        explicit file_mapping(const std::string &filename,
                              access_mode_t access_mode = read_write,
                              creation_mode_t creation_mode = open_or_create);

        void truncate(size_t memory_region_size) override;
        [[nodiscard]] const std::string &get_name() const noexcept override;
        [[nodiscard]] access_mode_t get_mode() const noexcept override;
        [[nodiscard]] int get_file_descriptor() const noexcept override;
        [[nodiscard]] size_t get_size() const noexcept override;

        static bool remove(const std::string &shm_obj_name);
    private:
        key_t key;
        creation_mode_t creation_mode;
        access_mode_t access_mode;
        std::string filename;
        int file_descriptor = NOT_DEFINED;
        size_t file_size = 0;
    };
}

#endif //PROCESS_PARTY_FILE_MAPPING_H
