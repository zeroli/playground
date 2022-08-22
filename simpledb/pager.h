#ifndef SIMPLEDB_PAGER_H_
#define SIMPLEDB_PAGER_H_

#include <cstdio>

#include "config.h"

#define TABLE_MAX_PAGES 100

struct Pager {
    FILE* fp;
    uint32_t file_length;
    uint32_t num_pages;
    void* pages[TABLE_MAX_PAGES];
};

void * get_page(Pager* pager, uint32_t page_num)
{
    if (page_num > TABLE_MAX_PAGES) {
        printf("Tried to fetch page number out of bound. %d > %d\n",
            page_num, TABLE_MAX_PAGES);
        exit(-1);
    }
    if (pager->pages[page_num] == NULL) {
        // cache miss, allocate memory and load from file
        void* page = new char[PAGE_SIZE];
        uint32_t num_pages = pager->file_length / PAGE_SIZE;
        // we might save a partial page at the end of the file
        if (pager->file_length % PAGE_SIZE) {
            num_pages += 1;
        }

        if (page_num <= num_pages) {
            fseek(pager->fp, page_num * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = fread(page, PAGE_SIZE, 1, pager->fp);
            if (bytes_read == -1) {
                printf("Error reading file: %d\n", ferror(pager->fp));
                exit(-1);
            }
        }
        pager->pages[page_num] = page;

        if (page_num >= pager->num_pages) {
            pager->num_pages = page_num + 1;
        }
    }
    return pager->pages[page_num];
}

void pager_flush(Pager* pager, uint32_t page_num)
{
    if (pager->pages[page_num] == NULL) {
        printf("Tried to flush null page\n");
        exit(1);
    }
    off_t offset = fseek(pager->fp, page_num * PAGE_SIZE, SEEK_SET);
    if (offset == -1) {
        printf("Error seeking: %d\n", ferror(pager->fp));
        exit(-1);
    }
    ssize_t bytes_written = fwrite(pager->pages[page_num], PAGE_SIZE, 1, pager->fp);
    if (bytes_written == -1) {
        printf("Error writing: %d\n", ferror(pager->fp));
        exit(-1);
    }
}

Pager* pager_open(const char* filename)
{
    FILE* fp = fopen(filename, "a+");
    if (fp == NULL) {
        printf("unable to open file %s\n", filename);
        exit(-1);
    }
    off_t file_length = fseek(fp, 0, SEEK_END);
    Pager* pager = new Pager();
    pager->fp = fp;
    pager->file_length = file_length;
    pager->num_pages = (file_length / PAGE_SIZE);
    if (file_length % PAGE_SIZE != 0) {
        printf("Db file is not a whole number of pages. Currupt file.\n");
        exit(-1);
    }

    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++) {
        pager->pages[i] = NULL;
    }
    return pager;
}

/*
 Until we start recycling free pages, new pages will always
 go onto the end of the database file
*/
uint32_t get_unused_page_num(Pager* pager)
{
    return pager->num_pages;
}

#endif  // SIMPLEDB_PAGER_H_
