#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Número máximo de candidatos
#define MAX 9

// Candidatos possuem nome e contagem de votos
typedef struct
{
string nome;
int votos;
}
candidato;

// Array de candidatos
candidato candidatos[MAX];

// Número de candidatos
int quantidade_candidatos;

// Protótipos de função
bool votar(string nome);
void imprimir_vencedor(void);

int main(int argc, string argv[])
{
// Verificar uso inválido
if (argc < 2)
{
printf("Uso: plurality [candidato...]\n");
return 1;
}