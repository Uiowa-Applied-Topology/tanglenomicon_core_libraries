/*!
 *  @file storage.hpp
 *
 *  @brief  Storage interface description.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#ifndef STORAGE_INTERFACE
#define STORAGE_INTERFACE

/******************************************************************************/
/*******************************Includes***************************************/
/******************************************************************************/
#include <cstring>
#include <memory>
#include <random>
#include <sstream>
#include <string>

/******************************************************************************/
/*******************************Defines***************************************/
/******************************************************************************/

#define STORE_WRITE_FAIL (0x1u)
#define STORE_WRITE_SUCCESS (0x0u)

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
    virtual int write(char *key, char *index, char *value) = 0;

    /*!
     * @brief
     * @param key
     * @return
     */
    virtual const char *read(char *key, char *index) = 0;

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
#endif /* end STORAGE_INTERFACE*/