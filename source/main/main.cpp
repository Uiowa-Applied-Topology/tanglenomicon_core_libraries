/*!
 *  @file main.cpp
 *
 *  @brief  A pattern for generator modules
 *
 *
 *  @author    Isabel Darcy
 *  @author    Ethan Rooke
 *  @author    Zachary Bryhtan
 *  @author    Joe Starr
 *
 */

#include <cxxopts.hpp>
#include <generator_rational.h>
#include <iostream>
#include <memory>

int main(int argc, char **argv)
{
    cxxopts::Options options("test", "A brief description");

    options
        .add_options() /*                                                     */
        ("r,rational", "Generate rational",
         cxxopts::value<bool>()->default_value("false")) /*                   */
        ("n,cNum", "max",
         cxxopts::value<int>()->default_value("10"))("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    bool doRational = result["rational"].as<bool>();
    if (doRational == true)
    {
        gen_rational_config_t rational_config = {10, NULL, NULL, 0, true};
        if (gen_rational_config(&rational_config) == GEN_RATIONAL_CONFIG_FAIL)
        {
            exit(1);
        }

    }

    return 0;
}