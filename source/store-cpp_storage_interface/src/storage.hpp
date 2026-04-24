/**
 *  @file storage.hpp
 *
 *  @brief store-cpp_storage_interface interface description.
 *
 *
 *  @author Isabel Darcy
 *  @author Zachary Bryhtan
 *  @author Joe Starr
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
/**
 * \brief Class for wrapping a C storage interface for C++
 */
class storage_interface_c
{
public:

    /**
     * \brief Standard write interface.
     * \param key The key for the write.
     * \param index The index for the write.
     * \param value The value to write.
     * \return A status indicator.
     *
     */
    virtual uint8_t write(const char *key, const char *index,
                          const char *value) = 0;

    /**
     * \brief Standard read interface.
     * \param key The key to read.
     * \param index The index to read.
     * \return The value at [key][index].
     */
    virtual const char *read(const char *key, const char *index) = 0;

    virtual ~storage_interface_c()
    {
    };

    /**
     * \brief Flag indicating if a new file should be created.
     */
    bool makenewfile = false;

    /**
     * \brief uuid generator from
     *[stackOverflow](https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library)
     * \return Returns a UUID as a string.
     */
    static std::string generate_uuid_v4();

private:

    /**
     * \brief A random device for uuid creation
     */
    static std::random_device rd;

    /**
     * \brief A random number generator.
     */
    static std::mt19937 gen;

    /**
     * \brief A uniform distribution.
     */
    static std::uniform_int_distribution <> dis;

    /**
     * \brief A uniform distribution.
     */
    static std::uniform_int_distribution <> dis2;
};
}; /* namespace storage_ns */
#endif /* end STORAGE_INTERFACE_H */
