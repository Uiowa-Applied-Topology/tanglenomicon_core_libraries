/* */
/* Created by joe on 6/23/25. */
/* */
#include "storage_defs.h"
#include "string.h"
#include "stdint.h"
#include "stdbool.h"

#ifndef TANGLENOMICON_STORAGE_STUBS_H
#define TANGLENOMICON_STORAGE_STUBS_H

typedef struct {
    char   key_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u]
    [UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u];
    char   index_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u]
    [UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u];
    char   value_buff[UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u]
    [UTIL_TANG_DEFS_MAX_CROSSINGNUM * 100u];
    size_t key_idx;
    size_t index_idx;
    size_t value_idx;
} test_stub_storage_buffers_t;

uint8_t test_stub_write_success(const char *key,
                                const char *index,
                                const char *value);
uint8_t test_stub_write_fail(const char *key,
                             const char *index,
                             const char *value);
uint8_t test_stub_write_dedup_success(const char *key,
                                      const char *index,
                                      const char *value);
void test_stub_storage_clear_buffers(void);
const char *test_stub_read_success(const char *key, const char *index);
const char *test_stub_read_success_msg(const char *key, const char *index);
const bool test_stub_read_exists(const char *key, const char *index);

#endif /* TANGLENOMICON_STORAGE_STUBS_H */