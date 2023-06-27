// Modifica o volume de um arquivo de áudio

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Número de bytes no cabeçalho .wav
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Verifique os argumentos da linha de comando
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Abra arquivos e determine o fator de escala
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copie o cabeçalho do arquivo de entrada para o arquivo de saída

    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    // Ler amostras do arquivo de entrada e gravar dados atualizados no arquivo de saída

    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
        {
            buffer *= factor;
            fwrite(&buffer, sizeof(int16_t), 1, output);
        }

    fclose(input);
    fclose(output);
}