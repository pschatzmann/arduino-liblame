

#include "log.h"
#include <stdio.h>
#include <string.h>

char log_msg[MAX_LOG_LEN];

int write(char const s[static 1]) {
    for (size_t i = 0; s[i]; ++i)
        if (putchar(s[i]) == EOF) return EOF;
    return 0;
}

void print_log(const char* file, int line, const char* current_level) {
    const char* file_name = strrchr(file, '/') ? strrchr(file, '/') + 1 : file;
    write("[");
    write(current_level);
    write("] ");
    write(file_name);
    write(" : ");
    char line_str[20];
    snprintf(line_str,20,"%d",line);
    write(line_str);
    write(" - ");
    write(log_msg);
    write("\n");
}
