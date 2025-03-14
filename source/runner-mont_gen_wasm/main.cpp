/*!
 *  @file main.cpp
 *
 *  @brief  A pattern for generator modules
 *
 *
 *  @author    Isabel Darcy
 *  @author    Joe Starr
 *
 */
#include <generator_montesinos.h>
#include <notation_tv.h>
#include <notation_att.h>
#include <tang_defs.h>

#ifdef ENABLE_EMSCRIPTEN
#include <emscripten.h>
#include <emscripten/bind.h>
using namespace emscripten;
#endif

#include <stdio.h>
#include <string>
#include <vector>

typedef std::vector<std::string> VecString;
typedef std::vector<std::vector<std::string>> tv_lists_t;
typedef std::vector<note_tv_t> tvnote_list_t;
typedef std::vector<tvnote_list_t> tvnote_lists_t;

VecString mont_list;
tvnote_lists_t tv_sets;

uint8_t stub_write_success(char *key, char *index, char *value)
{
    mont_list.emplace_back((std::string)key);
    return STORE_DEFS_WRITE_SUCCESS;
}
const char *stub_read(char *key, char *index)
{
    fprintf(stderr, "Read: %s\n", key);
    return NULL;
}

int clear_tv()
{
    for (int i = 0; i < tv_sets.size(); i++)
    {
        tv_sets[i].clear();
    }
    tv_sets.clear();
    return 0;
}
int encode_tv(const tv_lists_t &tvs)
{
    int ret_val = 1;

    for (int i = 0; i < tvs.size(); i++)
    {
        tvnote_list_t tvset;
        tv_sets.push_back(tvset);
        for (int j = 0; j < tvs[i].size(); j++)
        {
            note_tv_t tv;
            note_tv_encode((char *)(tvs[i][j].c_str()), &tv);
            char test[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2];
            note_tv_decode(tv, test);
            tv_sets.back().push_back(tv);
        }
    }
    return ret_val;
}

int print_stuff()
{
    for (int i = 0; i < tv_sets.size(); i++)
    {
        for (int j = 0; j < tv_sets[i].size(); j++)
        {
            fprintf(stderr, "%zu\n", tv_sets[i][j].tv_length);
            std::string str = "[";
            for (int k = 0; k < tv_sets[i][j].tv_length; k++)
            {
                str.append(std::to_string(tv_sets[i][j].twist_vector[k]) + " ");
            }
            str.append("]");
            fprintf(stderr, "%s\n", str.c_str());
        }
    }
    return 0;
}

VecString generate(const tv_lists_t &tvs)
{
    mont_list.clear();
    encode_tv(tvs);
    fprintf(stderr, "Start generate");
    std::vector<note_tv_t *> tv_s;
    std::vector<size_t> tv_set_lens;
    note_att_node_t nodes[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2];
    note_att_t att_n = {NULL, nodes, UTIL_TANG_DEFS_MAX_CROSSINGNUM * 2, NULL,
                        0};

    for (int i = 0; i < tv_sets.size(); i++)
    {
        tv_s.push_back(tv_sets[i].data());
        tv_set_lens.push_back((size_t)tv_sets[i].size());
    }
    char str_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 10u];

    gen_montesinos_config_t mon_cfg = {&stub_write_success,
                                       &stub_read,
                                       &att_n,
                                       tv_s.data(),
                                       tv_set_lens.data(),
                                       tv_sets.size(),
                                       str_buff,
                                       UTIL_TANG_DEFS_MAX_CROSSINGNUM * 5};
    int ret_val = GEN_DEFS_CONFIG_FAIL;
    ret_val = gen_montesinos_config(&mon_cfg);
    if (ret_val != GEN_DEFS_CONFIG_FAIL)
    {
        ret_val = gen_montesinos_generate();
    }
    fprintf(stderr, "End generate");
    clear_tv();
    return mont_list;
}
#ifdef ENABLE_EMSCRIPTEN
EMSCRIPTEN_BINDINGS(montgen)
{
    register_vector<std::string>("VecString");
    register_vector<std::vector<std::string>>("tv_lists_t");
    function("encode_tv", &encode_tv);
    function("print_stuff", &print_stuff);
    function("generate", &generate);
    function("clear_tv", &clear_tv);
}
#else

int main()
{
    std::vector<std::string> tv1 = {"[1 1 0]"};
    std::vector<std::string> tv2 = {"[1 2 0]", "[2 1 0]"};
    std::vector<std::string> tv3 = {"[1 1 1 1 0]", "[1 3 0]", "[2 2 0]",
                                    "[3 1 0]"};
    std::vector<std::string> tv4 = {"[1 1 0]"};
    std::vector<std::string> tv5 = {"[1 1 0]"};

    std::vector<std::string> tv6 = {"[1 1 1 1 1 1 1 1 1 1 0]",
                                    "[1 1 1 1 1 1 1 3 0]",
                                    "[1 1 1 1 1 1 2 2 0]",
                                    "[1 1 1 1 1 1 3 1 0]",
                                    "[1 1 1 1 1 2 1 2 0]",
                                    "[1 1 1 1 1 2 2 1 0]",
                                    "[1 1 1 1 1 3 1 1 0]",
                                    "[1 1 1 1 1 5 0]",
                                    "[1 1 1 1 2 1 1 2 0]",
                                    "[1 1 1 1 2 1 2 1 0]",
                                    "[1 1 1 1 2 2 1 1 0]",
                                    "[1 1 1 1 2 4 0]",
                                    "[1 1 1 1 3 1 1 1 0]",
                                    "[1 1 1 1 3 3 0]",
                                    "[1 1 1 1 4 2 0]",
                                    "[1 1 1 1 5 1 0]",
                                    "[1 1 1 2 1 1 1 2 0]",
                                    "[1 1 1 2 1 1 2 1 0]",
                                    "[1 1 1 2 1 2 1 1 0]",
                                    "[1 1 1 2 1 4 0]",
                                    "[1 1 1 2 2 1 1 1 0]",
                                    "[1 1 1 2 2 3 0]",
                                    "[1 1 1 2 3 2 0]",
                                    "[1 1 1 2 4 1 0]",
                                    "[1 1 1 3 1 1 1 1 0]",
                                    "[1 1 1 3 1 3 0]",
                                    "[1 1 1 3 2 2 0]",
                                    "[1 1 1 3 3 1 0]",
                                    "[1 1 1 4 1 2 0]",
                                    "[1 1 1 4 2 1 0]",
                                    "[1 1 1 5 1 1 0]",
                                    "[1 1 1 7 0]",
                                    "[1 1 2 1 1 1 1 2 0]",
                                    "[1 1 2 1 1 1 2 1 0]",
                                    "[1 1 2 1 1 2 1 1 0]",
                                    "[1 1 2 1 1 4 0]",
                                    "[1 1 2 1 2 1 1 1 0]",
                                    "[1 1 2 1 2 3 0]",
                                    "[1 1 2 1 3 2 0]",
                                    "[1 1 2 1 4 1 0]",
                                    "[1 1 2 2 1 1 1 1 0]",
                                    "[1 1 2 2 1 3 0]",
                                    "[1 1 2 2 2 2 0]",
                                    "[1 1 2 2 3 1 0]",
                                    "[1 1 2 3 1 2 0]",
                                    "[1 1 2 3 2 1 0]",
                                    "[1 1 2 4 1 1 0]",
                                    "[1 1 2 6 0]",
                                    "[1 1 3 1 1 1 1 1 0]",
                                    "[1 1 3 1 1 3 0]",
                                    "[1 1 3 1 2 2 0]",
                                    "[1 1 3 1 3 1 0]",
                                    "[1 1 3 2 1 2 0]",
                                    "[1 1 3 2 2 1 0]",
                                    "[1 1 3 3 1 1 0]",
                                    "[1 1 3 5 0]",
                                    "[1 1 4 1 1 2 0]",
                                    "[1 1 4 1 2 1 0]",
                                    "[1 1 4 2 1 1 0]",
                                    "[1 1 4 4 0]",
                                    "[1 1 5 1 1 1 0]",
                                    "[1 1 5 3 0]",
                                    "[1 1 6 2 0]",
                                    "[1 1 7 1 0]",
                                    "[1 2 1 1 1 1 1 2 0]",
                                    "[1 2 1 1 1 1 2 1 0]",
                                    "[1 2 1 1 1 2 1 1 0]",
                                    "[1 2 1 1 1 4 0]",
                                    "[1 2 1 1 2 1 1 1 0]",
                                    "[1 2 1 1 2 3 0]",
                                    "[1 2 1 1 3 2 0]",
                                    "[1 2 1 1 4 1 0]",
                                    "[1 2 1 2 1 1 1 1 0]",
                                    "[1 2 1 2 1 3 0]",
                                    "[1 2 1 2 2 2 0]",
                                    "[1 2 1 2 3 1 0]",
                                    "[1 2 1 3 1 2 0]",
                                    "[1 2 1 3 2 1 0]",
                                    "[1 2 1 4 1 1 0]",
                                    "[1 2 1 6 0]",
                                    "[1 2 2 1 1 1 1 1 0]",
                                    "[1 2 2 1 1 3 0]",
                                    "[1 2 2 1 2 2 0]",
                                    "[1 2 2 1 3 1 0]",
                                    "[1 2 2 2 1 2 0]",
                                    "[1 2 2 2 2 1 0]",
                                    "[1 2 2 3 1 1 0]",
                                    "[1 2 2 5 0]",
                                    "[1 2 3 1 1 2 0]",
                                    "[1 2 3 1 2 1 0]",
                                    "[1 2 3 2 1 1 0]",
                                    "[1 2 3 4 0]",
                                    "[1 2 4 1 1 1 0]",
                                    "[1 2 4 3 0]",
                                    "[1 2 5 2 0]",
                                    "[1 2 6 1 0]",
                                    "[1 3 1 1 1 1 1 1 0]",
                                    "[1 3 1 1 1 3 0]",
                                    "[1 3 1 1 2 2 0]",
                                    "[1 3 1 1 3 1 0]",
                                    "[1 3 1 2 1 2 0]",
                                    "[1 3 1 2 2 1 0]",
                                    "[1 3 1 3 1 1 0]",
                                    "[1 3 1 5 0]",
                                    "[1 3 2 1 1 2 0]",
                                    "[1 3 2 1 2 1 0]",
                                    "[1 3 2 2 1 1 0]",
                                    "[1 3 2 4 0]",
                                    "[1 3 3 1 1 1 0]",
                                    "[1 3 3 3 0]",
                                    "[1 3 4 2 0]",
                                    "[1 3 5 1 0]",
                                    "[1 4 1 1 1 2 0]",
                                    "[1 4 1 1 2 1 0]",
                                    "[1 4 1 2 1 1 0]",
                                    "[1 4 1 4 0]",
                                    "[1 4 2 1 1 1 0]",
                                    "[1 4 2 3 0]",
                                    "[1 4 3 2 0]",
                                    "[1 4 4 1 0]",
                                    "[1 5 1 1 1 1 0]",
                                    "[1 5 1 3 0]",
                                    "[1 5 2 2 0]",
                                    "[1 5 3 1 0]",
                                    "[1 6 1 2 0]",
                                    "[1 6 2 1 0]",
                                    "[1 7 1 1 0]",
                                    "[1 9 0]",
                                    "[2 1 1 1 1 1 1 2 0]",
                                    "[2 1 1 1 1 1 2 1 0]",
                                    "[2 1 1 1 1 2 1 1 0]",
                                    "[2 1 1 1 1 4 0]",
                                    "[2 1 1 1 2 1 1 1 0]",
                                    "[2 1 1 1 2 3 0]",
                                    "[2 1 1 1 3 2 0]",
                                    "[2 1 1 1 4 1 0]",
                                    "[2 1 1 2 1 1 1 1 0]",
                                    "[2 1 1 2 1 3 0]",
                                    "[2 1 1 2 2 2 0]",
                                    "[2 1 1 2 3 1 0]",
                                    "[2 1 1 3 1 2 0]",
                                    "[2 1 1 3 2 1 0]",
                                    "[2 1 1 4 1 1 0]",
                                    "[2 1 1 6 0]",
                                    "[2 1 2 1 1 1 1 1 0]",
                                    "[2 1 2 1 1 3 0]",
                                    "[2 1 2 1 2 2 0]",
                                    "[2 1 2 1 3 1 0]",
                                    "[2 1 2 2 1 2 0]",
                                    "[2 1 2 2 2 1 0]",
                                    "[2 1 2 3 1 1 0]",
                                    "[2 1 2 5 0]",
                                    "[2 1 3 1 1 2 0]",
                                    "[2 1 3 1 2 1 0]",
                                    "[2 1 3 2 1 1 0]",
                                    "[2 1 3 4 0]",
                                    "[2 1 4 1 1 1 0]",
                                    "[2 1 4 3 0]",
                                    "[2 1 5 2 0]",
                                    "[2 1 6 1 0]",
                                    "[2 2 1 1 1 1 1 1 0]",
                                    "[2 2 1 1 1 3 0]",
                                    "[2 2 1 1 2 2 0]",
                                    "[2 2 1 1 3 1 0]",
                                    "[2 2 1 2 1 2 0]",
                                    "[2 2 1 2 2 1 0]",
                                    "[2 2 1 3 1 1 0]",
                                    "[2 2 1 5 0]",
                                    "[2 2 2 1 1 2 0]",
                                    "[2 2 2 1 2 1 0]",
                                    "[2 2 2 2 1 1 0]",
                                    "[2 2 2 4 0]",
                                    "[2 2 3 1 1 1 0]",
                                    "[2 2 3 3 0]",
                                    "[2 2 4 2 0]",
                                    "[2 2 5 1 0]",
                                    "[2 3 1 1 1 2 0]",
                                    "[2 3 1 1 2 1 0]",
                                    "[2 3 1 2 1 1 0]",
                                    "[2 3 1 4 0]",
                                    "[2 3 2 1 1 1 0]",
                                    "[2 3 2 3 0]",
                                    "[2 3 3 2 0]",
                                    "[2 3 4 1 0]",
                                    "[2 4 1 1 1 1 0]",
                                    "[2 4 1 3 0]",
                                    "[2 4 2 2 0]",
                                    "[2 4 3 1 0]",
                                    "[2 5 1 2 0]",
                                    "[2 5 2 1 0]",
                                    "[2 6 1 1 0]",
                                    "[2 8 0]",
                                    "[3 1 1 1 1 1 1 1 0]",
                                    "[3 1 1 1 1 3 0]",
                                    "[3 1 1 1 2 2 0]",
                                    "[3 1 1 1 3 1 0]",
                                    "[3 1 1 2 1 2 0]",
                                    "[3 1 1 2 2 1 0]",
                                    "[3 1 1 3 1 1 0]",
                                    "[3 1 1 5 0]",
                                    "[3 1 2 1 1 2 0]",
                                    "[3 1 2 1 2 1 0]",
                                    "[3 1 2 2 1 1 0]",
                                    "[3 1 2 4 0]",
                                    "[3 1 3 1 1 1 0]",
                                    "[3 1 3 3 0]",
                                    "[3 1 4 2 0]",
                                    "[3 1 5 1 0]",
                                    "[3 2 1 1 1 2 0]",
                                    "[3 2 1 1 2 1 0]",
                                    "[3 2 1 2 1 1 0]",
                                    "[3 2 1 4 0]",
                                    "[3 2 2 1 1 1 0]",
                                    "[3 2 2 3 0]",
                                    "[3 2 3 2 0]",
                                    "[3 2 4 1 0]",
                                    "[3 3 1 1 1 1 0]",
                                    "[3 3 1 3 0]",
                                    "[3 3 2 2 0]",
                                    "[3 3 3 1 0]",
                                    "[3 4 1 2 0]",
                                    "[3 4 2 1 0]",
                                    "[3 5 1 1 0]",
                                    "[3 7 0]",
                                    "[4 1 1 1 1 2 0]",
                                    "[4 1 1 1 2 1 0]",
                                    "[4 1 1 2 1 1 0]",
                                    "[4 1 1 4 0]",
                                    "[4 1 2 1 1 1 0]",
                                    "[4 1 2 3 0]",
                                    "[4 1 3 2 0]",
                                    "[4 1 4 1 0]",
                                    "[4 2 1 1 1 1 0]",
                                    "[4 2 1 3 0]",
                                    "[4 2 2 2 0]",
                                    "[4 2 3 1 0]",
                                    "[4 3 1 2 0]",
                                    "[4 3 2 1 0]",
                                    "[4 4 1 1 0]",
                                    "[4 6 0]",
                                    "[5 1 1 1 1 1 0]",
                                    "[5 1 1 3 0]",
                                    "[5 1 2 2 0]",
                                    "[5 1 3 1 0]",
                                    "[5 2 1 2 0]",
                                    "[5 2 2 1 0]",
                                    "[5 3 1 1 0]",
                                    "[5 5 0]",
                                    "[6 1 1 2 0]",
                                    "[6 1 2 1 0]",
                                    "[6 2 1 1 0]",
                                    "[6 4 0]",
                                    "[7 1 1 1 0]",
                                    "[7 3 0]",
                                    "[8 2 0]",
                                    "[9 1 0]"};
    tv_lists_t sadfd = {tv1, tv2, tv3, tv4, tv5, tv6};
    //    encode_tv(sadfd);
    // print_stuff();

    generate(sadfd);
    printf("%zu\n", mont_list.size());
    return 0;
}

#endif
