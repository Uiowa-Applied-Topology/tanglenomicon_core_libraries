/* */
/* Created by joe on 6/23/25. */
/* */

#include "test_storage_stubs.h"
#include "stdbool.h"
#include "stdio.h"

#define HASHSIZE    (100 * UTIL_TANG_DEFS_MAX_CROSSINGNUM)


char buffer[1024];

typedef struct idxlist {  /* table entry: */
    struct idxlist *next; /* next entry in chain */
    char *          name; /* defined name */
    char *          defn; /* replacement text */
} idxlist;

typedef struct keylist {
    struct keylist *next;             /* next entry in chain */
    char *          name;             /* defined name */
    idxlist *       idxtab[HASHSIZE]; /* pointer table */
} keylist;

static keylist *keytab[HASHSIZE]; /* pointer table */

static keylist keytab_buffer[HASHSIZE]            = { { NULL, NULL, NULL } };
static idxlist idxtab_buffer[HASHSIZE * HASHSIZE] = { { NULL, NULL, NULL } };
static size_t  keytab_buffer_idx = 0;
static size_t  idxtab_buffer_idx = 0;
void test_stub_storage_clear_buffers(void)
{
    keytab_buffer_idx = 0;
    idxtab_buffer_idx = 0;
    size_t i;
    for (i = 0; i < HASHSIZE; i++)
    {
        keytab[i] = NULL;
        size_t j;
        for (j = 0; j < HASHSIZE; j++)
        {
            keytab_buffer[i].idxtab[j] = NULL;
        }
        keytab_buffer[i].name = NULL;
        keytab_buffer[i].next = NULL;
    }

    for (i = 0; i < HASHSIZE; i++)
    {
        idxtab_buffer[i].defn = NULL;
        idxtab_buffer[i].name = NULL;
        idxtab_buffer[i].next = NULL;
    }
}

/* hash: form hash value for string s */
static size_t str_hash(const char *s)
{
    size_t hash = 5381;
    int    c;

    while (c = *s++)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    hash = hash % HASHSIZE;
    return hash;
}

/* lookup: look for s in hashtab */
static idxlist *idx_lookup(idxlist **li, const char *s)
{
    idxlist *np;
    size_t   hash = str_hash(s);

    for (np = li[hash]; np != NULL; np = np->next)
    {
        if (strcmp(s, np->name) == 0)
        {
            return np; /* found */
        }
    }
    return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
static idxlist *idx_install(idxlist **li, const char *name, const char *defn)
{
    idxlist *np;

    if ((np = idx_lookup(li, name)) == NULL)
    { /* not found */
        unsigned hashval;
        if ((HASHSIZE * HASHSIZE) <= idxtab_buffer_idx)
        {
            return NULL;
        }
        np = &idxtab_buffer[idxtab_buffer_idx];
        idxtab_buffer_idx++;
        hashval     = str_hash(name);
        np->name    = strdup(name);
        np->next    = li[hashval];
        li[hashval] = np;
    }
    if ((np->defn = strdup(defn)) == NULL)
    {
        return NULL;
    }
    return np;
}

/* lookup: look for s in hashtab */
static keylist *key_lookup(const char *s)
{
    keylist *np;
    size_t   hash = str_hash(s);

    for (np = keytab[hash]; np != NULL; np = np->next)
    {
        if ((np->name != NULL) && (strcmp(s, np->name) == 0))
        {
            return np; /* found */
        }
    }
    return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
static keylist *key_install(const char *name)
{
    keylist *np = NULL;

    if ((np = key_lookup(name)) == NULL)
    { /* not found */
        unsigned hashval;
        if (HASHSIZE <= keytab_buffer_idx)
        {
            return NULL;
        }
        np = &keytab_buffer[keytab_buffer_idx];
        keytab_buffer_idx++;
        hashval         = str_hash(name);
        np->name        = strdup(name);
        np->next        = keytab[hashval];
        keytab[hashval] = np;
        size_t i;
        for (i = 0; i < HASHSIZE; i++)
        {
            np->idxtab[i] = NULL;
        }
    } /* already there */
    return np;
}

const char *test_stub_read_success(const char *key, const char *index)
{
    char *   ret_val = NULL;
    keylist *np      = key_lookup(key);

    if (NULL != np)
    {
        idxlist **     li = np->idxtab;
        const idxlist *l  = idx_lookup(li, index);
        if (l != NULL)
        {
            ret_val = l->defn;
        }
    }
    return ret_val;
}

const char *test_stub_read_success_msg(const char *key, const char *index)
{
    char *   ret_val = NULL;
    keylist *np      = key_lookup(key);

    if (NULL != np)
    {
        idxlist **     li = np->idxtab;
        const idxlist *l  = idx_lookup(li, index);
        if (l != NULL)
        {
            ret_val = l->defn;
        }
        else
        {
            snprintf(buffer, sizeof(buffer), "Cant find index %s for %s", index, key);
            return buffer;
        }
    }
    else
    {
        snprintf(buffer, sizeof(buffer), "Cant find %s", key);
        return buffer;
    }
    return ret_val;
}

const bool test_stub_read_exists(const char *key, const char *index)
{
    bool     ret_val = false;
    keylist *np      = key_lookup(key);

    if (NULL != np)
    {
        idxlist **     li = np->idxtab;
        const idxlist *l  = idx_lookup(li, index);
        if (l != NULL)
        {
            ret_val = true;
        }
    }
    return ret_val;
}

uint8_t test_stub_write_success(const char *key,
                                const char *index,
                                const char *value)
{
    keylist *np = key_install(key);

    if (NULL != np)
    {
        idxlist **li = np->idxtab;
        idx_install(li, index, value);
    }
    return STORE_DEFS_WRITE_SUCCESS;
}

uint8_t test_stub_write_fail(const char *key,
                             const char *index,
                             const char *value)
{
    idx_install(key_install(key)->idxtab, index, value);
    return STORE_DEFS_WRITE_FAIL;
}
