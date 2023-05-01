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
#include <storage.hpp>
#include <storage_JSON.hpp>
#include <string>

using namespace std;

class runner_main_c
{
  public:
    static storage_ns::storage_interface_c *storage_interface;
    static string file_path;
    static bool new_file;

    static int storage_write(char *key, char *index, char *value)
    {
        return storage_interface->write(key, index, value);
    }

    /*!
     * @brief
     * @param key
     * @return
     */
    static char *storage_read(char *key, char *index)
    {
        return storage_interface->read(key, index);
    }
};

bool runner_main_c::new_file = false;
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
         cxxopts::value<int>()->default_value("10")) /*                       */
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
    }
    else
    {
        runner_main_c::new_file = true;
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
        gen_rational_config_t rational_config = {
            10, /*                                                            */
            &runner_main_c::storage_write, /*                                 */
            &runner_main_c::storage_read, /*                                  */
            true};
        if (gen_rational_config(&rational_config) == GEN_RATIONAL_CONFIG_FAIL)
        {
            exit(1);
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