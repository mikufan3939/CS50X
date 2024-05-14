#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    uint8_t block[512];
    char filename[8];
    int jpegcount = 0, aux = 0;
    FILE *jpeg = NULL;

    if (argc != 2)
    {
        printf("Incorrect Usage!");
        return 1;
    }

    FILE *data = fopen(argv[1], "r");

    if (data == NULL)
    {
        return 1;
    }

    while (fread(block, 1, 512, data) == 512)
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0 &&
            jpegcount == 0)
        {
            sprintf(filename, "%03i.jpg", jpegcount);
            jpeg = fopen(filename, "w");
            jpegcount = jpegcount + 1;
            aux = aux + 1;
        }
        else if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff &&
                 (block[3] & 0xf0) == 0xe0)
        {
            fclose(jpeg);
            sprintf(filename, "%03i.jpg", jpegcount);
            jpeg = fopen(filename, "w");
            jpegcount = jpegcount + 1;
            aux = aux + 1;
        }
        if (jpeg != NULL)
        {
            if ((block[0] != 0xff || block[1] != 0xd8 || block[2] != 0xff ||
                 (block[3] & 0xf0) != 0xe0 || aux == 1))
            {
                fwrite(block, 1, 512, jpeg);
                aux = 0;
            }
        }
    }
    fclose(data);
    fclose(jpeg);
}
