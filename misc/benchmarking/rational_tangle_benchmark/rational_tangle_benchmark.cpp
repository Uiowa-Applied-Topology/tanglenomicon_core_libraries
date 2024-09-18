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
    static size_t gen_counter;
    static size_t crossing_num;
    static size_t size_bytes;

    static void deconstruct_ptr() { delete storage_interface; }
    static void reinit()
    {
        // reset counts on CN change.
        gen_counter = 0;
        size_bytes = 0;
    }
    static void write_results()
    {
        // The rational tangle generator calls write twice for each TV.
        // we need to divide count by two.
        gen_counter >>= 1;
        // Write data to json writer.
        std::string str_cnt = std::to_string(gen_counter);
        std::string str_cn = std::to_string(crossing_num);
        std::string str_bytes = std::to_string(size_bytes);
        std::string str_idx_1 = "generation_count";
        std::string str_idx_2 = "size_bytes";
        storage_interface->write((char *)(str_cn.c_str()),
                                 (char *)(str_idx_1.c_str()),
                                 (char *)(str_cnt.c_str()));
        storage_interface->write((char *)(str_cn.c_str()),
                                 (char *)(str_idx_2.c_str()),
                                 (char *)(str_bytes.c_str()));
    }

    static uint8_t storage_write(char *key, char *index, char *value)
    {
        // Stub te write function just keep count.
        gen_counter++;
        std::string key_s(key);
        std::string index_s(index);
        std::string value_s(value);
        size_bytes += key_s.size();
        size_bytes += index_s.size();
        size_bytes += value_s.size();
        return STORE_DEFS_WRITE_SUCCESS;
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
size_t runner_main_c::gen_counter = 0;
size_t runner_main_c::size_bytes = 0;
size_t runner_main_c::crossing_num = 0;
string runner_main_c::file_path = "";
storage_ns::storage_interface_c *runner_main_c::storage_interface = nullptr;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

int main(int argc, char **argv)
{
    cxxopts::Options options("test", "A brief description");

    /* clang-format off */
    options.add_options()
        /**********************************************************************/
        ("n,cNum", "Crossing number to target",
         cxxopts::value<uint8_t>()->default_value("10"))
        /**********************************************************************/
        ("u,upto", "upto",
         cxxopts::value<bool>()->default_value("false"))
        /**********************************************************************/
        ("f,file", "File for storage",
         cxxopts::value<string>())
        /**********************************************************************/
        ("h,help", "Print usage");

    /* clang-format on */

    auto command_args = options.parse(argc, argv);

    /**************************************************************************/
    /********************************Runner CFG********************************/
    /**************************************************************************/
    if (command_args.count("help"))
    {
        cout << options.help() << endl;
        exit(0);
    }

    if (command_args.count("file"))
    {
        runner_main_c::file_path = command_args["file"].as<string>();
    }
    else
    {
        runner_main_c::new_file = true;
        runner_main_c::file_path =
            storage_ns::storage_interface_c::generate_uuid_v4();
        runner_main_c::file_path += ".json";
    }
    /**************************************************************************/
    /********************************storage***********************************/
    /**************************************************************************/

    runner_main_c::storage_interface = new storage_ns::storage_json_c(
        runner_main_c::file_path, runner_main_c::new_file);

    /**************************************************************************/
    /********************************computations******************************/
    /**************************************************************************/

    /**************************************************************************/
    /********************************generators********************************/
    /**************************************************************************/

    note_tv_t tv_n;
    char tv_str[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u];
    bool upto = command_args["upto"].as<bool>();
    // Are we getting numbers for 1 CN or up to the CN
    if (upto)
    {
        for (uint8_t i = 1; i <= command_args["cNum"].as<uint8_t>(); i++)
        {
            runner_main_c::crossing_num = i;
            /* clang-format off */
            gen_rational_config_t rational_config = {
                            i,
                            &runner_main_c::storage_write,
                            &runner_main_c::storage_read,
                            &tv_n,
                            tv_str,
                            UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u};
            /* clang-format on */

            uint8_t result = gen_rational_config(&rational_config);
            result = gen_rational_generate();
            runner_main_c::write_results();
            runner_main_c::reinit();

        }
    }
    else
    {
        runner_main_c::crossing_num = command_args["cNum"].as<uint8_t>();
        /* clang-format off */
        gen_rational_config_t rational_config = {
        command_args["cNum"].as<uint8_t>(),
        &runner_main_c::storage_write,
        &runner_main_c::storage_read,
        &tv_n,
        tv_str,
        UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2u};
        /* clang-format on */

        uint8_t result = gen_rational_config(&rational_config);
        result = gen_rational_generate();
        runner_main_c::write_results();
    }

    /**************************************************************************/
    /********************************translators*******************************/
    /**************************************************************************/
    // write to file
    runner_main_c::deconstruct_ptr();

    /**************************************************************************/
    /********************************notations*********************************/
    /**************************************************************************/

    return 0;
}