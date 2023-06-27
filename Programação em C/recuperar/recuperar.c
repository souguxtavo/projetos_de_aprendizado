#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //verifique se o argumento é contagem 2
    if (argc != 2)
    {
        printf("Usage: ./revocer IMAGE\n");
        return 1;
    }

    //Abra o arquivo para leitura
    FILE *input_file = fopen(argv[1], "r");

    //verifique se input_file é válido
    if(input_file == NULL)
    {
        printf("Could not open file");
        return 2;
    }

    //armazenar blocos de 512 bytes em uma array
    unsigned char buffer[512];

    //acompanhar número de imagens geradas
    int count_image = 0;

    //ponteiro de arquivo para imagens recuperadas
    FILE *output_file = NULL;
    char *filename = malloc(8 * sizeof(char));

    //leia os blocos de 512 bytes
    while (fread(buffer, sizeof(char), 512, input_file))
    {
        //checar os bytes indicados no começo do JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer [3] & 0xf0) == 0xe0)
        {
            //escreva os nomes do jpeg
            sprintf(filename, "%03i.jpg", count_image);
            output_file = fopen(filename, "w");
            count_image++;
        }

        //verifique se o output esta usando um input válido
        if (output_file != NULL)
        {
            fwrite (buffer, sizeof(char), 512, output_file);
        }
    }
    free(filename);
    fclose(output_file);
    fclose(input_file);

    return 0;
}