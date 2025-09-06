#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

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
    printf("Last Modified : %s", ctime(&st.st_mtime));

    return 0;
}