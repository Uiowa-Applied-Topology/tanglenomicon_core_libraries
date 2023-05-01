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
#include <random>
#include <sstream>
#include <storage.hpp>
#include <storage_JSON.hpp>
#include <string>

using namespace std;

/*uuid from
 * https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library*/
namespace uuid
{
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<> dis(0, 15);
static std::uniform_int_distribution<> dis2(8, 11);

std::string generate_uuid_v4()
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
} // namespace uuid

class runner_main
{
  public:
    static storage::storage *storage_interface;
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

bool runner_main::new_file = false;
string runner_main::file_path = "";
storage::storage *runner_main::storage_interface = nullptr;

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
        runner_main::file_path = result["file"].as<string>();
    }
    else
    {
        runner_main::new_file = true;
        runner_main::file_path = uuid::generate_uuid_v4();
    }
    /**************************************************************************/
    /********************************Storage***********************************/
    /**************************************************************************/

    bool dojson = result["json"].as<bool>();
    if (dojson == true)
    {

        if (runner_main::new_file)
        {
            runner_main::file_path += ".json";
        }
        runner_main::storage_interface = new storage::storage_json(
            runner_main::file_path, runner_main::new_file);
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
            &runner_main::storage_write, /*                                   */
            &runner_main::storage_read, /*                                    */
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