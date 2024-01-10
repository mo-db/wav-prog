#include <stdio.h>

int main()
{
    int data[] = {10000000,
                10000001,
                10000002,
                10000003,
                10000004};

    FILE *file;
    file = fopen("test.bin", "wb");

    if (file == NULL) {
        printf("Error, cant open file \n");
        return 1;
    }

    fwrite(data, sizeof(data), 1, file);
    fclose(file);

    return 0;
}