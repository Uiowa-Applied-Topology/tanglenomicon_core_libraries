/*!
 *  @file storage_JSON.h
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

#ifndef STORAGE_JSON
#define STORAGE_JSON

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

#define STORE_JSON_WRITE_FAIL (0x1u)
#define STORE_JSON_WRITE_SUCCESS (0x0u)

/******************************************************************************/
/***************************Function Declerations******************************/
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
    char *read(char *key, char *index);

    /*!
     * @brief
     * @param key
     * @param index
     * @param value
     * @return
     */
    int write(char *key, char *index, char *value);

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
#endif /* end STORAGE_JSON */