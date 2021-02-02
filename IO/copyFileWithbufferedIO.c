#include<stdio.h>
#include<stdlib.h>

#define MAX_BUFFER_LEN 20

int main(int argc, char const *argv[])
{
    char buffer[MAX_BUFFER_LEN];
    FILE *input = fopen("test.txt", "r");
    if (input == NULL) {
        perror("open srcFile error");
        exit(1);
    }

    FILE *output = fopen("dst.txt", "w");
    if (output == NULL) {
        perror("open dstFile error");
        exit(1);
    }
    size_t readLen;

    while ((readLen = fread(buffer, 1, MAX_BUFFER_LEN, input)) >= 0) {

        // 将缓冲区buffer中的数据写入文件output中, buffer是待写入缓冲区的地址（指针), 1 是待写入数据块的大小， readLen是待写入数据块的个数。output是待写入的文件。
        // fwrite()函数返回值是正常写入数据块的个数。如果出错，返回值会小于readLen
        int ret = fwrite(buffer, 1, readLen, output);
        if (ret < readLen) {
            perror("write error");
            exit(1);
        }
        // 当读取出错或者读到文件结尾，fread函数的返回值readLen小于MAX_BUFFER_LEN（即缓冲区数组的大小）
        if (readLen < MAX_BUFFER_LEN) break;
    }

    fclose(output);
    fclose(input);

    return 0;
}
