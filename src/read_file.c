#include <stdio.h>

int main()
{
    int data[5];

    FILE *file;
    file = fopen("test.txt", "r");

    if (file == NULL) {
        printf("Error, cant open file \n");
        return 1;
    }

    fread(data, sizeof(data), 1, file);
    fclose(file);

    for (int i = 0; i < 5; i++) {
        printf("data[%i]=%i\n", i, data[i]);
    }

    return 0;
}