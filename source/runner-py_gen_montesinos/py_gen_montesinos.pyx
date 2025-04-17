# cython: language_level=3

from libc.stddef cimport *
from libc.stdint cimport *
from cpython.mem cimport PyMem_Malloc, PyMem_Realloc, PyMem_Free

import cython



cdef extern from "generator_defs.h":
    ctypedef uint8_t (*storage_write_funptr_t)(const char *key, const char *index, const char *value)
    ctypedef const char * (*storage_read_funptr_t)(const char *key,const char *index)

cdef extern from "notation_tv.h":
    ctypedef struct note_tv_t:
        uint8_t *twist_vector
        size_t tv_length

cdef extern from "notation_att.h":

    ctypedef struct note_att_node_t:
        void *L_child
        void *R_child
        uint8_t flavor

    ctypedef struct note_att_t:
        note_att_node_t *root
        note_att_node_t *node_buffer
        size_t node_buffer_len
        note_tv_t *tv_buffer
        size_t tv_buffer_len

cdef extern from "generator_montesinos.h":
    ctypedef struct gen_montesinos_config_t:
        storage_write_funptr_t storage_write
        storage_read_funptr_t storage_read
        note_att_t *att_n
        note_tv_t **tv_sets
        size_t *tv_set_lens
        size_t tv_sets_len
        char * str_buff
        size_t str_buff_len
    uint8_t gen_montesinos_config(gen_montesinos_config_t *config_arg)
    uint8_t gen_montesinos_generate()


cdef uint8_t pywrite(const char *key,const char *index,const char *value) noexcept:
    print(key.decode('ASCII'))
    return 0

cdef const char * pyread(const char *key,const char *index) noexcept:

    return ""


def start_job():
    cdef gen_montesinos_config_t config
    cdef note_att_t att_n
    cdef note_tv_t **tv_sets
    cdef size_t *tv_set_lens

    att_n.root = cython.NULL
    att_n.node_buffer = <note_att_node_t*>PyMem_Malloc(100 * sizeof(note_att_node_t))
    att_n.node_buffer_len = 100
    att_n.tv_buffer = cython.NULL
    att_n.tv_buffer_len = 0

    tv_sets    = <note_tv_t**>PyMem_Malloc(3 * sizeof(note_tv_t*))
    tv_sets[0] = <note_tv_t* >PyMem_Malloc(3 * sizeof(note_tv_t ))
    for i in range(3):
        tv_sets[0][i].twist_vector[0] = 0
        tv_sets[0][i].twist_vector[1] = i
        tv_sets[0][i].twist_vector[2] = i
        tv_sets[0][i].tv_length = 3
    tv_sets[1] = <note_tv_t* >PyMem_Malloc(2 * sizeof(note_tv_t ))
    for i in range(2):
        tv_sets[1][i].twist_vector[0] = 1
        tv_sets[1][i].twist_vector[1] = i
        tv_sets[1][i].twist_vector[2] = i
        tv_sets[1][i].tv_length = 3
    tv_sets[2] = <note_tv_t* >PyMem_Malloc(4 * sizeof(note_tv_t ))
    for i in range(4):
        tv_sets[2][i].twist_vector[0] = 2
        tv_sets[2][i].twist_vector[1] = i
        tv_sets[2][i].twist_vector[2] = i
        tv_sets[2][i].tv_length = 3
    tv_set_lens = <size_t *>PyMem_Malloc(3 * sizeof(size_t ))
    tv_set_lens[0]=3
    tv_set_lens[1]=2
    tv_set_lens[2]=4

    config.storage_write = pywrite
    # (storage_write_funptr_t)&write
    config.storage_read = pyread
    config.att_n = &att_n
    config.tv_sets = tv_sets
    config.tv_set_lens = tv_set_lens
    config.tv_sets_len = 3
    config.str_buff = <char*>PyMem_Malloc(1000 * sizeof(char))
    config.str_buff_len = 1000

    gen_montesinos_config(&config)
    gen_montesinos_generate()

    return 0