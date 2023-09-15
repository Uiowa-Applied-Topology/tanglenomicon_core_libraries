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

#include <generator_rational.h>
#include <comp_rational_data.h>
#include <notation_tv.h>
#include <storage.hpp>
#include <storage_JSON.hpp>
#include <tang_defs.h>

#include <cxxopts.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

using namespace std;

class runner_main_c
{
  public:
    static storage_ns::storage_interface_c *storage_interface;
    static string file_path;
    static bool new_file;
    static bool init_file;
    static void deconstruct_ptr() { delete storage_interface; }

    static int storage_write(char *key, char *index, char *value)
    {
        return storage_interface->write(key, index, value);
    }

    /*!
     * @brief
     * @param key
     * @return
     */
    static const char *storage_read(char *key, char *index)
    {
        return storage_interface->read(key, index);
    }
};

bool runner_main_c::new_file = false;
bool runner_main_c::init_file = false;
string runner_main_c::file_path = "";
storage_ns::storage_interface_c *runner_main_c::storage_interface = nullptr;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

int main(int argc, char **argv)
{
    cxxopts::Options options("test", "A brief description");

    /* clang-format off */
    options
        .add_options()
        /**********************************************************************/
        ("r,rational", "Generate rational",
         cxxopts::value<bool>()->default_value("false"))
        /**********************************************************************/
        ("d,rational_dat", "Compute rational data",
         cxxopts::value<bool>()->default_value("false"))
        /**********************************************************************/
        ("t,twistvec", "A twist vector to work on",
         cxxopts::value<string>())
        /**********************************************************************/
        ("n,cNum", "Crossing number to target",
         cxxopts::value<uint8_t>()->default_value("10"))
        /**********************************************************************/
        ("j,json", "Store as json",
         cxxopts::value<bool>()->default_value("false"))
        /**********************************************************************/
        ("f,file", "File for storage",
         cxxopts::value<string>())
        /**********************************************************************/
        ("h,help", "Print usage");

    /* clang-format on */

    auto comand_args = options.parse(argc, argv);

    /**************************************************************************/
    /********************************Runner CFG********************************/
    /**************************************************************************/
    if (comand_args.count("help"))
    {
        cout << options.help() << endl;
        exit(0);
    }

    if (comand_args.count("file"))
    {
        runner_main_c::file_path = comand_args["file"].as<string>();
    }
    else
    {
        runner_main_c::new_file = true;
        runner_main_c::init_file = true;
        runner_main_c::file_path =
            storage_ns::storage_interface_c::generate_uuid_v4();
    }
    /**************************************************************************/
    /********************************Storage***********************************/
    /**************************************************************************/

    bool dojson = comand_args["json"].as<bool>();
    if (dojson == true)
    {

        if (runner_main_c::new_file)
        {
            runner_main_c::file_path += ".json";
        }

        runner_main_c::storage_interface = new storage_ns::storage_json_c(
            runner_main_c::file_path, runner_main_c::new_file);
    }

    /**************************************************************************/
    /********************************Computations******************************/
    /**************************************************************************/

    bool doRational_dat = comand_args["rational_dat"].as<bool>();
    if (doRational_dat == true)
    {
        if (comand_args.count("twistvec"))
        {
            note_tv_t tv_n;
            char tv_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u];
            (void)note_tv_encode(
                (char *)(comand_args["twistvec"].as<string>().c_str()), &tv_n);
            /* clang-format off */
            comp_rational_data_config_t rational_dat_config = {
                &runner_main_c::storage_write,
                &runner_main_c::storage_read,
                &tv_n,
                tv_str,
                UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u};
            /* clang-format on */

            uint8_t result = comp_rational_data_config(&rational_dat_config);
            if ((result & GEN_DEFS_CONFIG_FAIL) == GEN_DEFS_CONFIG_FAIL)
            {
                exit(1);
            }
            else
            {
                result = comp_rational_data_compute();
                runner_main_c::deconstruct_ptr();
                if ((result & GEN_DEFS_GENERATION_FAIL) ==
                    GEN_DEFS_GENERATION_FAIL)
                {
                    exit(1);
                }
            }
        }
        else
        {
            exit(1);
        }
    }
    /**************************************************************************/
    /********************************Generators********************************/
    /**************************************************************************/

    bool doRational = comand_args["rational"].as<bool>();
    if (doRational == true)
    {
        note_tv_t tv_n;
        char tv_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u];

        /* clang-format off */
        gen_rational_config_t rational_config = {
            comand_args["cNum"].as<uint8_t>(),
            &runner_main_c::storage_write,
            &runner_main_c::storage_read,
            &tv_n,
            tv_str,
            UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u};
        /* clang-format on */

        uint8_t result = gen_rational_config(&rational_config);
        if ((result & GEN_DEFS_CONFIG_FAIL) == GEN_DEFS_CONFIG_FAIL)
        {
            exit(1);
        }
        else
        {
            result = gen_rational_generate();
            runner_main_c::deconstruct_ptr();
            if ((result & GEN_DEFS_GENERATION_FAIL) == GEN_DEFS_GENERATION_FAIL)
            {
                exit(1);
            }
        }
    }

    /**************************************************************************/
    /********************************Translators*******************************/
    /**************************************************************************/

    /**************************************************************************/
    /********************************Notations*********************************/
    /**************************************************************************/

    return 0;
}