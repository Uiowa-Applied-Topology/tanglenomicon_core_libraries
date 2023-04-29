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
    virtual int write(char *key, char *index, char *value);

    /*!
     * @brief
     * @param key
     * @return
     */
    virtual char *read(char *key);
};

#endif /* end STORAGE_INTERFACE*/