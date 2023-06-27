import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Definição, leitura do csv dos filmes / calculo para tirar o ano em outra coluna
uri = "https://raw.githubusercontent.com/alura-cursos/introducao-a-data-science/master/aula4.1/movies.csv"
filmes = pd.read_csv(uri)
filmes.columns = ["filmeId", "titulo", "generos"]
filmes = filmes.set_index('filmeId')
filmes = filmes.join(filmes['generos'].str.get_dummies()).drop('generos', axis=1)
filmes['ano'] = filmes['titulo'].str.extract(r'.*\((\d+)\)')
filmes = filmes.dropna()

# Definição, leitura da tabela notas
uri = "https://raw.githubusercontent.com/alura-cursos/introducao-a-data-science/master/aula1.2/ratings.csv"
notas = pd.read_csv(uri)
notas.columns = ["usuarioId", "filmeId", "nota", "momento"]
arredondadas = notas['nota'].round(1)

# calculo das medias
medias = notas.groupby('filmeId')['nota'].mean()
filmes = filmes.join(medias).dropna().sort_values('nota', ascending=False).rename(columns={'nota': 'media'})

# agrupamento de tabelas
total = notas.groupby('filmeId')['momento'].count()
filmes = filmes.join(total)
filmes = filmes.rename(columns={'momento' : 'total'})
filmes = filmes.query("total > 50")
filmes['media_categoria'] = (filmes['media']).round(1).values

# seleção de filmes aleatórios
random_filmes = filmes.sample(10)

# chamar primeiros intens das tabelas
filmes.head()
notas.head()

# gráfico de comparação de filmes aleatórios pela suas médias
palette = sns.color_palette("Blues", 10)
palette = sns.cubehelix_palette(10, start=2, rot=0, dark=0, light=.4)
sns.countplot(arredondadas, palette=palette)
p = sns.barplot(data = random_filmes, x = 'titulo', y = 'media')
p.set_xticklabels(p.get_xticklabels(), rotation = 45, horizontalalignment = 'right')
plt.title("Notas médias de 10 filmes");
plt.show()