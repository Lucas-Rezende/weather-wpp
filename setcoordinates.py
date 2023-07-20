import sys
from functools import partial
from geopy.geocoders import Nominatim

geolocator = Nominatim(user_agent="weather-wpp")
geocode = partial(geolocator.geocode, language="en")

def pesquisar_localizacao(endereco):
    location = geocode(endereco)
    if location:
        latitude = location.latitude
        longitude = location.longitude
        print(f"{latitude} {longitude}")
    else:
        print("Erro.")

# Obter o valor de endereco a partir dos argumentos de linha de comando
endereco = sys.argv[1]

# Chamar a função de pesquisa
pesquisar_localizacao(endereco)
