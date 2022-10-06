#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[]){
    if (argc != 2) {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    } else {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL){
            printf("INVALID FILE\n");
            return 1;
        }
        int BLOCK_SIZE = sizeof(BYTE)*512;

        int counter = 0;
        FILE *img = NULL;
        BYTE buffer[512];
        char name[8];
        while (fread(&buffer, sizeof(BYTE), 512, file) == BLOCK_SIZE){
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff){
                // JPEG
                if (counter != 0){
                    fclose(img);
                }
                sprintf(name, "%03i.jpg", counter);
                img = fopen(name, "w");
                fwrite(&buffer, sizeof(BYTE), 512, img);
                counter++;
            } else {
                // Keep going
                if (counter > 0){
                    fwrite(&buffer, sizeof(BYTE), 512, img);
                }
            }
        }
        fclose(img);
        fclose(file);
    }
}