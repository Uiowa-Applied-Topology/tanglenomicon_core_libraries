#include "storage.hpp"
#include "storage_JSON.hpp"
#include "unity.h"
#include <cstdio>
#include <fstream>
#include <iostream>


/******************************************************************************/
/*******************************Untested Frameworks****************************/
/******************************************************************************/
// We trust that json.hpp works.
#include "json.hpp"
using json = nlohmann::json;

using namespace std;

using sj = storage_ns::storage_json_c;

/******************************************************************************/
/*******************************Test Data**************************************/
/******************************************************************************/
string testfile_good = "{\"[0]\":{\"index\":\"value\"}}";
string testfile_good_path = "testfile_good.json";

string testfile_malformed = "{";
string testfile_malformed_path = "testfile_bad.json";

/******************************************************************************/
/*******************************Test prep**************************************/
/******************************************************************************/

void setUp(void)
{
    ofstream *json_file = new ofstream(testfile_malformed_path);
    *json_file << setw(4) << testfile_malformed << endl;
    json_file->close();
    delete json_file;
    json_file = new ofstream(testfile_good_path);
    *json_file << setw(4) << testfile_good << endl;
    json_file->close();
    delete json_file;
}

void tearDown(void)
{
    // remove(testfile_malformed_path.c_str());
    // remove(testfile_good_path.c_str());
    // clean stuff up here
}

/******************************************************************************/
/*******************************Test cases*************************************/
/******************************************************************************/

/*!
 * @brief
 * @param
 */
void test_create_obj(void)
{
    sj *test_obj = nullptr;
    TEST_ASSERT_TRUE(!test_obj);
    test_obj = new sj(testfile_good_path, false);
    TEST_ASSERT_TRUE(test_obj);
    delete test_obj;
}

// char *read(char *key, char *index)

/*!
 * @brief
 * @param
 */
void test_read(void)
{
    sj *test_obj = new sj(testfile_good_path, false);
    char key[] = "[0]";
    char index[] = "index";

    TEST_ASSERT_TRUE(test_obj);
    const char *read_var;
    read_var = test_obj->read(key, index);
    TEST_ASSERT_EQUAL_STRING(read_var, "value");
    delete test_obj;
}

// char *read(char *key, char *index)

/*!
 * @brief
 * @param
 */
void test_read_malformed(void)
{
    try
    {
        sj *test_obj = new sj(testfile_malformed_path, false);
        TEST_FAIL();
        TEST_FAIL_MESSAGE("This shouldn't pass initialization.");
    }
    catch (json::parse_error &e)
    {
        TEST_ASSERT_TRUE(true);
    }
}

// int write(char *key, char *index, char *value)

/*!
 * @brief
 * @param
 */
void test_write_newkey(void)
{
    char key[] = "[1] ";
    char index[] = "index";
    char value[] = "value1";
    sj *test_obj = new sj(testfile_good_path, false);
    TEST_ASSERT_TRUE(test_obj);
    int write_res = test_obj->write(key, index, value);
    TEST_ASSERT_EQUAL(write_res, STORE_WRITE_SUCCESS);
    delete test_obj;
}

// int write(char *key, char *index, char *value)

/*!
 * @brief
 * @param
 */
void test_write_newindex(void)
{
    char key[] = "[0]";
    char index[] = "index2";
    char value[] = "value2";
    sj *test_obj = new sj(testfile_good_path, false);
    TEST_ASSERT_TRUE(test_obj);
    int write_res = test_obj->write(key, index, value);
    TEST_ASSERT_EQUAL(write_res, STORE_WRITE_SUCCESS);
    delete test_obj;
}

// int write(char *key, char *index, char *value)

/*!
 * @brief
 * @param
 */
void test_write_updateindex(void)
{
    char key[] = "[0]";
    char index[] = "index";
    char value[] = "value2";
    sj *test_obj = new sj(testfile_good_path, false);
    TEST_ASSERT_TRUE(test_obj);
    int write_res = test_obj->write(key, index, value);
    TEST_ASSERT_EQUAL(write_res, STORE_WRITE_SUCCESS);
    delete test_obj;
}


/******************************************************************************/
/*******************************Test main**************************************/
/******************************************************************************/
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_create_obj);
    RUN_TEST(test_read);
    RUN_TEST(test_read_malformed);
    RUN_TEST(test_write_newkey);
    RUN_TEST(test_write_newindex);
    RUN_TEST(test_write_updateindex);

    return UNITY_END();
}
