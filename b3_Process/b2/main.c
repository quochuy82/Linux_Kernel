#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(void) {
    // Tên và giá trị của biến môi trường
    const char *env_name = "MY_COMMAND";
    const char *env_value = "ls"; // Có thể thay đổi thành "date", "whoami", v.v.

    // --- Logic của Tiến trình Cha ---
    printf("Tiến trình cha (PID: %d) đang thiết lập biến môi trường '%s=%s'\n", getpid(), env_name, env_value);

    // setenv() để thiết lập biến môi trường.
    // Tham số thứ 3 là 1 để cho phép ghi đè nếu biến đã tồn tại.
    if (setenv(env_name, env_value, 1)!= 0) {
        perror("setenv thất bại");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        // Lỗi khi gọi fork()
        perror("fork thất bại");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Đây là mã thực thi trong tiến trình cha
        printf("Tiến trình cha (PID: %d) đã tạo tiến trình con (PID: %d)\n", getpid(), pid);
        printf("Tiến trình cha đang chờ tiến trình con hoàn thành...\n");

        int status;
        // waitpid() chờ đợi tiến trình con cụ thể kết thúc.
        // Điều này ngăn tiến trình cha kết thúc trước con và tránh tạo ra zombie process.
        waitpid(pid, &status, 0);

        printf("Tiến trình cha: Tiến trình con đã kết thúc. Tiến trình cha sẽ thoát.\n");
    } else {
        // Đây là mã thực thi trong tiến trình con (pid == 0)
        printf("--> Tiến trình con (PID: %d) bắt đầu thực thi.\n", getpid());

        // getenv() để đọc giá trị của biến môi trường.
        const char *command = getenv(env_name);

        if (command == NULL) {
            fprintf(stderr, "--> Tiến trình con: Không tìm thấy biến môi trường '%s'.\n", env_name);
            exit(EXIT_FAILURE);
        }

        printf("--> Tiến trình con: Đã đọc biến môi trường: %s = %s\n", env_name, command);
        printf("--> Tiến trình con: Sẽ thực thi lệnh '%s' bằng execlp()...\n", command);
        printf("--------------------------------------------------\n");

        // Sử dụng execlp() để thực thi lệnh.
        // execlp tìm lệnh trong PATH.
        // Các đối số là: tên lệnh, đối số 0 (lặp lại tên lệnh), các đối số khác, và NULL.
        // Ví dụ, để chạy "ls -l -h", ta sẽ dùng: execlp("ls", "ls", "-l", "-h", NULL);
        if (strcmp(command, "ls") == 0) {
            execlp(command, command, "-l", "-h", NULL);
        } else {
            execlp(command, command, NULL);
        }

        // Dòng mã này CHỈ được thực thi nếu execlp() thất bại.
        // Một lời gọi exec thành công sẽ không bao giờ trả về.
        perror("execlp thất bại");
        exit(EXIT_FAILURE); // Quan trọng: thoát tiến trình con nếu exec thất bại.
    }

    return 0;
}