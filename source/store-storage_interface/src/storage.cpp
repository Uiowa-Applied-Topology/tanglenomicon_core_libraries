/*!
 *  @file store-storage_interface.hpp
 *
 *  @brief  store-storage_interface interface description.
 *
 *
 *  @author    Isabel Darcy
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#include "storage.hpp"

using namespace storage_ns;

std::random_device storage_interface_c::rd;
std::mt19937 storage_interface_c::gen(storage_interface_c::rd());
std::uniform_int_distribution<> storage_interface_c::dis(0, 15);
std::uniform_int_distribution<> storage_interface_c::dis2(8, 11);

std::string storage_interface_c::generate_uuid_v4()
{
    std::stringstream ss;
    int i;
    ss << std::hex;
    for (i = 0; i < 8; i++)
    {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 4; i++)
    {
        ss << dis(gen);
    }
    ss << "-4";
    for (i = 0; i < 3; i++)
    {
        ss << dis(gen);
    }
    ss << "-";
    ss << dis2(gen);
    for (i = 0; i < 3; i++)
    {
        ss << dis(gen);
    }
    ss << "-";
    for (i = 0; i < 12; i++)
    {
        ss << dis(gen);
    };
    return ss.str();
}
