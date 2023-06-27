// Simule a herança genética do tipo sanguíneo

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cada pessoa tem dois pais e dois alelos
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Gerador de números aleatórios de sementes
    srand(time(0));

    // Criar uma nova família com três gerações
    person *p = create_family(GENERATIONS);

    // Imprima a árvore genealógica dos tipos sanguíneos
    print_family(p, 0);

    free_family(p);
}

// Crie um novo indivíduo com `gerações`
person *create_family(int generations)
{
    // Alocar memória para nova pessoa
    person *p = malloc(sizeof(person));

    // Se ainda restam gerações para criar
    if (generations > 1)
    {
        // Crie dois novos pais para a pessoa atual chamando recursivamente create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Definir ponteiros dos pais para a pessoa atual

        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Atribua aleatoriamente os alelos da pessoa atual com base nos alelos de seus pais
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];

    }

    // Se não houver gerações para criar
    else
    {
        // Definir ponteiros pai para NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // Atribuir alelos aleatoriamente
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();

    }

    // Retornar pessoa recém-criada
    return p;
}

// Livre `p` e todos os ancestrais de `p`.
void free_family(person *p)
{
    // Lidar com caixa básica
    if (p == NULL)
    {
        return;
    }

    // Pais livres recursivamente
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    free(p);

}

// Imprima cada membro da família e seus alelos.
void print_family(person *p, int generation)
{
    // Lidar com caixa básica
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print pais da atual geração
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Escolhe aleatoriamente um alelo de tipo sanguíneo.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}