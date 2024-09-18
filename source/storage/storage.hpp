/*!
 *  @file storage.hpp
 *
 *  @brief  storage interface description.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef STORAGE_INTERFACE_H
#define STORAGE_INTERFACE_H

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/
#include <storage_defs.h>
#include <cstring>
#include <memory>
#include <random>
#include <sstream>
#include <string>

/******************************************************************************/
/***************************Interface Descriptions*****************************/
/******************************************************************************/
namespace storage_ns
{
/*!
 * @brief
 */
class storage_interface_c
{
  public:
    /*!
     * @brief
     * @param key
     * @param index
     * @param value
     * @return
     */
    virtual uint8_t write(char *key, char *index, char *value) = 0;

    /*!
     * @brief
     * @param key
     * @return
     */
    virtual const char *read(char *key, char *index) = 0;


    virtual ~storage_interface_c(){};

    /*!
     * @brief
     */
    bool makenewfile = false;

    /*!
     * @brief uuid
     *        from
     *        [stackOverflow](https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library)
     * @return Returns a UUID as a string.
     */
    static std::string generate_uuid_v4();

  private:
    /*!
     * @brief
     */
    static std::random_device rd;

    /*!
     * @brief
     */
    static std::mt19937 gen;

    /*!
     * @brief
     */
    static std::uniform_int_distribution<> dis;

    /*!
     * @brief
     */
    static std::uniform_int_distribution<> dis2;
};
};     // namespace storage_ns
#endif /* end STORAGE_INTERFACE_H */