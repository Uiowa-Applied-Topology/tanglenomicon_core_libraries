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

/******************************************************************************/
/*******************************Defines***************************************/
/******************************************************************************/

#define STORE_WRITE_FAIL (0x1u)
#define STORE_WRITE_SUCCESS (0x0u)

/******************************************************************************/
/***************************Interface Descriptions*****************************/
/******************************************************************************/
namespace storage
{
class storage
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
    virtual char *read(char *key, char *index) = 0;

    /*!
     * @brief
     */
    bool makenewfile = false;

};
} // namespace storage
#endif /* end STORAGE_INTERFACE*/