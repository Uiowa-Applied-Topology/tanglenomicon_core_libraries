/**
 *  @file storage_json.hpp
 *
 *  @brief store-storage_interface module for store-json files.
 *
 *
 *  @author Isabel Darcy
 *  @author Zachary Bryhtan
 *  @author Joe Starr
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
/**
 * \brief json implementation of the storage_interface_c
 */
class storage_json_c : public storage_interface_c
{
public:

    /**
     * \brief Constructor for the class.
     * \param file_path Path to the file to output to.
     * \param newfile Flag to create new file.
     */
    /* cppcheck-suppress passedByValue */
    storage_json_c(std::string file_path, bool newfile);

    /**
     * \brief
     */
    ~storage_json_c() override;

    /**
     * \brief Standard read interface.
     * \param key The key to read.
     * \param index The index to read.
     * \return The value at [key][index].
     */
    const char *read(const char *key, const char *index) override;

    /**
     * \brief Standard write interface.
     * \param key The key for the write.
     * \param index The index for the write.
     * \param value The value to write.
     * \return A status indicator.
     *
     */
    uint8_t write(const char *key, const char *index, const char *value) override;

private:

    /**
     * \brief The data for the JSON file.
     */
    nlohmann::json data = NULL;

    /**
     * \brief The path to the JSON file.
     */
    std::string file_path = "";
};
} /* namespace storage_ns */
#endif /* end STORAGE_JSON_H */
