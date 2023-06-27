import pandas as pd

# Implementar as tabelas e pedir para o pandas lê-las
tabela_notas = "https://raw.githubusercontent.com/alura-cursos/introducao-a-data-science/master/aula1.2/ratings.csv"
tabela_filmes = "https://raw.githubusercontent.com/alura-cursos/introducao-a-data-science/master/aula4.1/movies.csv"
notas = pd.read_csv(tabela_notas)
filmes = pd.read_csv(tabela_filmes)

# Mudar o nome das colunas
notas.columns = ["usuarioId", "filme", "nota", "momento"]
filmes.columns = ["filme", "titulo", "genero"]

# Juntar as tabelas notas e filmes
filmes_notas = pd.merge(filmes, notas, on='filme')

# Busca do usuário
busca_por = input("Deseja buscar por título ou gênero? ")

# Filtragem de resultado e funcionalidades
if busca_por == "titulo":
    pergunta = input("Qual filme está procurando? ")
    filmes_notas = filmes_notas[filmes_notas["titulo"].str.contains(pergunta, case=False, na=False)]
elif busca_por == "genero":
    pergunta = input("Qual gênero está procurando? ")
    filmes_notas = filmes_notas[filmes_notas["genero"].str.contains(pergunta, case=False, na=False)]
else:
    print("Opção de busca inválida")

if filmes_notas.empty:
    print("Nenhum filme encontrado.")
else:
    # Agrupar as notas por título de filme
    notas_por_filme = round(filmes_notas.groupby("titulo")["nota"].mean(), 1)
    genero_por_filme = filmes_notas.groupby("titulo")["genero"].first()
    qtd_avaliacoes = filmes_notas.groupby("titulo")["nota"].count()
    for i, row in notas_por_filme.iteritems():
        print("Titulo: ", i)
        print("Gênero: ", genero_por_filme[i])
        print("Média de notas: ", row)
        print("Quantidade de avaliações: ", qtd_avaliacoes[i])
        print("Deseja ver outros títulos? Digite 's': ", end="")
        ver_notas = input()
        if ver_notas == 's':
            break
        else:
            exit()

# Agrupar as notas por título de filme
notas_por_filme = filmes_notas.groupby("titulo")["nota"].mean()

print(notas_por_filme)