# Importar o módulo json
import json
from datetime import datetime


# Ler o arquivo .txt com os dados em formato JSON
with open("data/data.txt") as f:
    dados = f.read()

# Converter o texto em um objeto JSON
objeto = json.loads(dados)

# Acessar os valores que você quer usando as chaves do objeto
latitude = objeto["latitude"]
longitude = objeto["longitude"]
temperatura_maxima = objeto["daily"]["temperature_2m_max"]
temperatura_minima = objeto["daily"]["temperature_2m_min"]
nascer_do_sol = objeto["daily"]["sunrise"]
por_do_sol = objeto["daily"]["sunset"]
tempo = objeto["hourly"]["time"]
temperatura = objeto["hourly"]["temperature_2m"]

# Imprimir os valores na tela
# Para cada índice na lista de tempo
for i in range(len(tempo)):
    # Converter a string de tempo em um objeto datetime
    data_hora = datetime.fromisoformat(tempo[i])

    # Acessar os atributos de data e hora do objeto datetime
    data = data_hora.date()
    hora = data_hora.time()
    # Imprimir a data, hora e temperatura correspondentes
    print(f"Data: {data}, Hora: {hora}, Temperatura: {temperatura[i]}")

# Salvar os dados filtrados no arquivo
with open("data/datapy.txt", "w") as f:
    f.write(json.dumps(objeto, indent=4))