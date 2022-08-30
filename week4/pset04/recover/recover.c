#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// number of bytes in FAT file system
const int BLOCK_SIZE = 512;

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // check for right usage
    if (argc != 2)
    {
        printf("Usage: .recover IMAGE\n");
        return 1;
    }

    // open files
    FILE *jpeg_file = fopen(argv[1], "r");
    if (!jpeg_file)
    {
        printf("Could not open file.\n");
        return 1;
    }

    int counter = 0;
    BYTE jpeg[BLOCK_SIZE];
    while (fread(jpeg, sizeof(BYTE), BLOCK_SIZE, jpeg_file) == BLOCK_SIZE)
    {
        char jpeg_number[8];
        if (jpeg[0] == 0xff && jpeg[1] == 0xd8 && jpeg[2] == 0xff && (jpeg[3] & 0xf0) == 0xe0)
        {
            sprintf(jpeg_number, "%03i.jpg", counter);
            // first jpeg
            if (counter == 0)
            {
                FILE *img = fopen(jpeg_number, "w");
                if (img == NULL)
                    return 1;
                fwrite(jpeg, sizeof(BYTE), BLOCK_SIZE, img);
                fclose(img);
            }
            // write if new jpeg
            else
            {
                FILE *img = fopen(jpeg_number, "w");
                if (img == NULL)
                    return 1;
                fwrite(jpeg, sizeof(BYTE), BLOCK_SIZE, img);
                fclose(img);
            }
            counter++;
        }
        else
        {
            // continue writing if jpeg already found
            if (counter > 0)
            {
                FILE *img = fopen(jpeg_number, "a");
                if (img == NULL)
                    return 1;
                fwrite(jpeg, sizeof(BYTE), BLOCK_SIZE, img);
                fclose(img);
            }
        }
    }
    fclose(jpeg_file);
}