#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

char time_buf[64];
struct tm *tm_info = NULL;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (lstat(argv[1], &st) == -1) {
        perror("lstat");
        return 1;
    }

    const char *type = "Unknown";
    if (S_ISREG(st.st_mode)) type = "Regular File";
    else if (S_ISDIR(st.st_mode)) type = "Directory";
    else if (S_ISLNK(st.st_mode)) type = "Symbolic Link";

    printf("File Path     : %s\n", argv[1]);
    printf("File Type     : %s\n", type);
    printf("Size          : %lld bytes\n", (long long)st.st_size);
    tm_info = localtime(&st.st_mtime);
    if (tm_info) {
        strftime(time_buf, sizeof time_buf, "%Y-%m-%d %H:%M:%S", tm_info);
        printf("Last Modified : %s\n", time_buf);
    } else {
        printf("Last Modified : (invalid)\n");
    }

    return 0;
}