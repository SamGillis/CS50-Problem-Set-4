#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//definition of Byte
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //checks to see if command line arguement is correct
    if (argc != 2)
    {
        printf("Usage: ./recover forensic image\n");
        return 1;
    }
    //open memory card
    FILE *file = fopen(argv[1], "r");
    //checks that file can be read
    if (file == NULL)
    {
        printf("File cannot be read\n");
        return 1;
    }
    //Defines buffer and imagecount
    BYTE buffer[512];
    int image_count = 0;
    char *filename = malloc(8 * sizeof(char));
    FILE *img = NULL;
    //repeat until the end of card
    while (true)
    {
        //read 512 bytes (a block) into a buffer
        //break while loop if end of file
        if (fread(buffer, 512, 1, file) != 1)
        {
            break;
        }
        //look for beginning of a JPEG If yes?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if first jpeg, write to new file
            if (image_count == 0)
            {
                //open a new Jpeg file
                sprintf(filename, "%03i.jpg", image_count);
                img = fopen(filename, "w");
                //write 512 bytes until a new JPEG is found
                fwrite(buffer, 512, 1, img);
            }
            //else close file and open new file
            else if (image_count > 0)
            {
                //close old Jpeg and create new
                fclose(img);
                sprintf(filename, "%03i.jpg", image_count);
                img = fopen(filename, "w");
                //write 512 bytes until a new JPEG is found
                fwrite(buffer, 512, 1, img);
            }
            image_count = image_count + 1;
        }
        else
        {
            //if already found jpeg, continue writing to open jpeg file
            if (image_count > 0)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
    }
    printf("Image Count: %i\n", image_count);
    //close any remaining open jpeg files
    if (img != NULL)
    {
        fclose(img);
    }
    free(filename);
    fclose(file);
    return 0;
}
