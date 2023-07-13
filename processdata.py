import json

def process_data(data):
    # Carregar o JSON
    json_data = json.loads(data)

    # Extrair informações diárias
    daily_data = json_data['daily']
    date = daily_data['time'][0]
    max_temp = daily_data['temperature_2m_max'][0]
    min_temp = daily_data['temperature_2m_min'][0]
    sunrise = daily_data['sunrise'][0]
    sunset = daily_data['sunset'][0]

    print(f"Data: {date}")
    print(f"Max Temp: {max_temp}")
    print(f"Min Temp: {min_temp}")
    print(f"Sunrise: {sunrise}")
    print(f"Sunset: {sunset}")

    # Extrair informações horárias
    hourly_data = json_data['hourly']
    hourly_time = hourly_data['time']
    hourly_temp = hourly_data['temperature_2m']
    hourly_humidity = hourly_data['relativehumidity_2m']
    hourly_precip_prob = hourly_data['precipitation_probability']
    hourly_weather_code = hourly_data['weathercode']

    print("Hourly Data:")
    for i in range(len(hourly_time)):
        time = hourly_time[i]
        temp = hourly_temp[i]
        humidity = hourly_humidity[i]
        precip_prob = hourly_precip_prob[i]
        weather_code = hourly_weather_code[i]

        print(f"{date} {time} {temp} {humidity} {precip_prob} {weather_code}")

    # Salvar os dados organizados em um arquivo de texto
    with open('data/datapy.txt', 'w') as file:
        file.write(f"Data: {date}\n")
        file.write(f"Max Temp: {max_temp}\n")
        file.write(f"Min Temp: {min_temp}\n")
        file.write(f"Sunrise: {sunrise}\n")
        file.write(f"Sunset: {sunset}\n")
        file.write("Hourly Data:\n")
        for i in range(len(hourly_time)):
            time = hourly_time[i]
            temp = hourly_temp[i]
            humidity = hourly_humidity[i]
            precip_prob = hourly_precip_prob[i]
            weather_code = hourly_weather_code[i]
            file.write(f"{date} {time} {temp} {humidity} {precip_prob} {weather_code}\n")

# Ler o JSON da API
with open('data/data.txt', 'r') as file:
    data = file.read()

# Processar os dados
process_data(data)

print("Dados do clima processados.")
