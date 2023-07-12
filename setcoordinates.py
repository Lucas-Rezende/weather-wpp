import sys
from functools import partial
from geopy.geocoders import Nominatim

geolocator = Nominatim(user_agent="weather-wpp")
geocode = partial(geolocator.geocode, language="en")

# Função para pesquisar por cidade, estado e país
def pesquisar_localizacao(endereco):
    location = geocode(endereco)
    if location:
        latitude = location.latitude
        longitude = location.longitude
        print(f"{latitude} {longitude}")
    else:
        print("Erro.")

# Ler os valores de cidade, estado e país do C++
endereco = input()

# Chamar a função de pesquisa
pesquisar_localizacao(endereco)
