import pandas as pd
from prettytable import PrettyTable
pd.options.display.max_columns = None
pd.options.display.width = None
pd.options.display.max_rows = None

SIM = "s"
NAO = "n"

#importar as tabelastra
vencimentos = pd.read_csv("listacalibracoes.csv")

#Funções
def obter_resposta(codigo):
  resposta = vencimentos.loc[vencimentos['Código'] == codigo]
  return resposta

def exibir_tabela(resposta):
  x = PrettyTable(resposta.columns.tolist())
  for row in resposta.itertuples():
    x.add_row(row[1:])
  print(x)

#interação com usuário
consulta_codigo = input("Código: ")
resposta = obter_resposta(consulta_codigo)

if resposta.empty:
  print("Não foi encontrado o código")
  exit()
else:
  exibir_tabela(resposta)

  nova_observacao = input("Deseja adicionar uma nova observação na coluna? (s/n) ")
  if nova_observacao == SIM:
    resposta = resposta.copy()
    resposta = resposta.sort_values("Data de calibração")
    resposta = resposta.iloc[0:1, :]
    resposta.loc[:, "Observação"] = input("Informe a observação: ")
    exibir_tabela(resposta)
  else:
    print("Finalizando.")
    exit()