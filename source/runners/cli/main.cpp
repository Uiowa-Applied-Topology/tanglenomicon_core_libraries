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

inline bool file_exists_test(const std::string &name)
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

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

    options
        .add_options() /*                                                     */
        /**********************************************************************/
        ("r,rational", "Generate rational",
         cxxopts::value<bool>()->default_value("false")) /*                   */
        /**********************************************************************/
        ("n,cNum", "maxCrossingNum",
         cxxopts::value<uint8_t>()->default_value(
             "10")) /*                       */
        /**********************************************************************/
        ("j,json", "Store as json",
         cxxopts::value<bool>()->default_value("false")) /*                   */
        /*********************************************************************/
        ("f,file", "File for storage", cxxopts::value<string>()) /*           */
        /**********************************************************************/
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    /**************************************************************************/
    /********************************Runner CFG********************************/
    /**************************************************************************/
    if (result.count("help"))
    {
        cout << options.help() << endl;
        exit(0);
    }

    if (result.count("file"))
    {
        runner_main_c::file_path = result["file"].as<string>();
        if (!file_exists_test(runner_main_c::file_path))
        {
            runner_main_c::init_file = true;
        }
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

    bool dojson = result["json"].as<bool>();
    if (dojson == true)
    {

        if (runner_main_c::new_file)
        {
            runner_main_c::file_path += ".json";
        }
        if (runner_main_c::init_file)
        {
            std::ofstream file;
            file.open(runner_main_c::file_path);
            file << "{}";
            file.close();
        }
        runner_main_c::storage_interface = new storage_ns::storage_json_c(
            runner_main_c::file_path, runner_main_c::new_file);
    }

    /**************************************************************************/
    /********************************Computations******************************/
    /**************************************************************************/

    /**************************************************************************/
    /********************************Generators********************************/
    /**************************************************************************/

    bool doRational = result["rational"].as<bool>();
    if (doRational == true)
    {
        note_tv_t tv_n;
        char tv_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u];
        gen_rational_config_t rational_config = {
            result["cNum"].as<uint8_t>(), /*                                  */
            &runner_main_c::storage_write, /*                                 */
            &runner_main_c::storage_read, /*                                  */
            &tv_n, /*                                                         */
            tv_str, /*                                                        */
            UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u};

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