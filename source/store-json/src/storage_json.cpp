/**
 *  \file storage_json.cpp
 *
 *  \brief store-storage_interface module for store-json files.
 *
 *
 *  \author Isabel Darcy
 *  \author Zachary Bryhtan
 *  \author Joe Starr
 *
 */

#include <storage_json.hpp>
#include <fstream>
#include <iostream>

/**
 * \brief Reference for the JSON library
 */
using json = nlohmann::json;

/**
 * \brief Reference for the C wrapper library
 */
using sj = storage_ns::storage_json_c;

const char *sj::read(const char *key, const char *index)
{
    char *value = NULL;

    if (this->data.contains(key))
    {
        if (this->data[key].contains(index))
        {
            /* cppcheck-suppress cstyleCast*/
            value = (char *)&this->data[key][index];
        }
    }
    return value;
}

uint8_t sj::write(const char *key, const char *index, const char *value)
{
    uint8_t ret_val = STORE_DEFS_WRITE_SUCCESS;

    if (this->data.is_null())
    {
        ret_val = STORE_DEFS_WRITE_SUCCESS;
    }
    else if (this->data.type() == json::value_t::array)
    {
        ret_val = STORE_DEFS_WRITE_SUCCESS;
    }
    else
    {
        this->data[key][index] = value;
    }
    return ret_val;
}

/* cppcheck-suppress passedByValue */
sj::storage_json_c(std::string file_path, bool newfile)
{
    this->file_path = file_path;
    this->data      = json::object();
    if (!newfile)
    {
        std::ifstream json_file(this->file_path);
        if (json::accept(json_file))
        {
            json_file.clear();
            json_file.seekg(0);
            this->data = json::parse(json_file);
        }
        json_file.close();
    }
}

sj::~storage_json_c()
{
    std::ofstream json_file(this->file_path);

    json_file << std::setw(4) << this->data << std::endl;
    json_file.flush();
    json_file.close();
}
