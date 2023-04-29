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
#include "json.hpp"
#include "storage.hpp"
#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;

/*!
 * @brief
 */
class storage_json : public storage
{
  public:
    /*!
     * @brief
     * @param key
     * @param index
     * @return
     */
    char *read(char *key, char *index)
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
    int write(char *key, char *index, char *value)
    {
        int ret_val = STORE_JSON_WRITE_SUCCESS;
        if (this->data.is_null())
        {
            ret_val = STORE_JSON_WRITE_FAIL;
        }
        else if (this->data.type() == json::value_t::array)
        {
            ret_val = STORE_JSON_WRITE_FAIL;
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
    storage_json(std::string file_path, bool makenewfile = false)
    {
        this->file_path = file_path;
        if (!makenewfile)
        {
            std::ifstream json_file(this->file_path);
            this->data = json::parse(json_file);
            json_file.close();
        }
    }
    ~storage_json()
    {
        std::ofstream json_file(this->file_path);
        json_file << std::setw(4) << this->data << std::endl;
        json_file.close();
    }

  private:
    /*!
     * @brief
     */
    json data = NULL;

    /*!
     * @brief
     */
    std::string file_path = "";
};
