#include <sys/types.h>
#include <sys/stat.h>  // 提供mode_t类型
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

#define MAX_BUFFER_LEN 20
/*
* 在 Windows下不能正常运行，因为Windows下系统调用IO与Unix不同
*/
int main(int argc, char const *argv[])
{
    char buffer[MAX_BUFFER_LEN];
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("open srcFile error");
        exit(1);
    }
    // O_WRONLY表示只写，O_CREAT表示文件不存在则创建，O_TRUNC表示清空文件内容，将其长度置为0
    int dstFd = open("dst.txt", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRUSR | S_IWUSR);
    if (dstFd < 0) {
        perror("open dstFile error");
        exit(1);
    }
    int len;
    while ((len = read(fd, buffer, MAX_BUFFER_LEN)) >= 0) {
        if (len == 0) break;
        int ret = write(dstFd, buffer, len);
        if (ret < 0) {
            perror("write error");
            exit(1);
        }
    }
    if (len < 0) {
        perror("read error");
        exit(1);
    }

    close(dstFd);
    close(fd);

    return 0;
}
