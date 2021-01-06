#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

#define BLOCKSIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Print error if there's more than 1 command-line argument.
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // Open input file.
    FILE *inptr = fopen(argv[1], "r");
    // Print error if the image can not be opened for reading.
    if (inptr == NULL)
    {
        printf("The image cannot be opened");
        return 1;
    }

    BYTE buffer[BLOCKSIZE];
    FILE *outptr;
    bool first_jpeg = false;
    int jpeg_count = 0;
    // Open the memory card.
    // Repeat until the end of the card.
    // Read 512 bytes into a buffer.
    while (fread(buffer, BLOCKSIZE, 1, inptr))
    {
        // If start of new Jpeg.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first Jpeg.
            if (!first_jpeg)
            {
                first_jpeg = true;
            }
            // Else.
            else
            {
                // Close the current file.
                fclose(outptr);
            }
            // Open a new file.
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count);
            outptr = fopen(filename, "w");
            jpeg_count++;
            fwrite(buffer, BLOCKSIZE, 1, outptr);
        }
        // Else, if already found a Jpeg.
        else if (first_jpeg)
        {
            // Keep writing on it.
            fwrite(buffer, BLOCKSIZE, 1, outptr);
        }
    }
    // Close the infile.
    fclose(inptr);
    // CLose the outfile.
    fclose(outptr);
}