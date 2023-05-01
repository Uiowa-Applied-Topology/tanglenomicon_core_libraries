/*!
 *  @file storage_JSON.c
 *
 *  @brief  Storage module for JSON files.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#include "storage_JSON.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using sj = storage_ns::storage_json_c;

char *sj::read(char *key, char *index)
{
    char *str = nullptr;
    if (this->data.contains(key))
    {
        if (this->data[key].contains(index))
        {
            *str = *(((std::string)this->data[key][index]).c_str());
        }
    }
    return str;
}

/*!
 * @brief
 * @param key
 * @param index
 * @param value
 * @return
 */
int sj::write(char *key, char *index, char *value)
{
    int ret_val = STORE_WRITE_SUCCESS;
    if (this->data.is_null())
    {
        ret_val = STORE_WRITE_FAIL;
    }
    else if (this->data.type() == json::value_t::array)
    {
        ret_val = STORE_WRITE_FAIL;
    }
    else
    {
        this->data[key][index] = value;
    }
    return ret_val;
}

/*!
 * @brief
 * @param file_path
 */
sj::storage_json_c(std::string file_path, bool newfile)
{
    this->file_path = file_path;
    if (!newfile)
    {
        std::ifstream json_file(this->file_path);
        this->data = json::parse(json_file);
        json_file.close();
    }
}
sj::~storage_json_c()
{
    std::ofstream json_file(this->file_path);
    json_file << std::setw(4) << this->data << std::endl;
    json_file.close();
}
