/*!
 *  @file storage_JSON.h
 *
 *  @brief  Storage module for JSON files.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef STORAGE_JSON_H
#define STORAGE_JSON_H

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/
#include "json.hpp"
#include "storage.hpp"
#include <cstring>
#include <string>

/******************************************************************************/
/*******************************Typedefs***************************************/
/******************************************************************************/

/******************************************************************************/
/*******************************Defines***************************************/
/******************************************************************************/

/******************************************************************************/
/***************************Function Declarations******************************/
/******************************************************************************/
namespace storage_ns
{
/*!
 * @brief
 */
class storage_json_c : public storage_interface_c
{
  public:
    /*!
     * @brief
     * @param file_path
     * @param makenewfile
     */
    storage_json_c(std::string file_path, bool newfile);

    /*!
     * @brief
     */
    ~storage_json_c();

    /*!
     * @brief
     * @param key
     * @param index
     * @return
     */
    const char *read(char *key, char *index);

    /*!
     * @brief
     * @param key
     * @param index
     * @param value
     * @return
     */
    uint8_t write(char *key, char *index, char *value);

  private:
    /*!
     * @brief
     */
    nlohmann::json data = NULL;

    /*!
     * @brief
     */
    std::string file_path = "";
};
} // namespace storage_ns
#endif /* end STORAGE_JSON_H */