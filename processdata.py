import json

def process_data(data):
    # Carregar o JSON
    json_data = json.loads(data)

    # Obter as informações desejadas
    daily_data = json_data['daily']
    hourly_data = json_data['hourly']

    # Organizar os dados por dia e hora
    daily_info = {}
    for i, date in enumerate(daily_data['time']):
        daily_info[date] = {
            'sunrise': daily_data['sunrise'][i],
            'sunset': daily_data['sunset'][i],
            'hourly_data': []
        }

    for i, hour in enumerate(hourly_data['time']):
        date, time = hour.split('T')
        temperature = hourly_data['temperature_2m'][i]
        precipitation_probability = hourly_data['precipitation_probability'][i]

        daily_info[date]['hourly_data'].append({
            'time': time,
            'temperature': temperature,
            'precipitation_probability': precipitation_probability
        })

    # Salvar os dados organizados em um arquivo de texto
    with open('data/datapy.txt', 'w') as file:
        for date, info in daily_info.items():
            sunrise = info['sunrise']
            sunset = info['sunset']
            hourly_data = info['hourly_data']

            file.write(f"Data: {date}\n")
            file.write(f"Sunrise: {sunrise}\n")
            file.write(f"Sunset: {sunset}\n")

            file.write("Hourly Data:\n")
            for hour_data in hourly_data:
                time = hour_data['time']
                temperature = hour_data['temperature']
                precipitation_probability = hour_data['precipitation_probability']

                file.write(f"{date} {time} {temperature} {precipitation_probability}\n")

            file.write("\n")

    print("Data saved to file.")

# Ler o JSON da API
with open('data/data.txt', 'r') as file:
    data = file.read()

# Processar os dados e salvar em um arquivo
process_data(data)

print("Dados do clima processados.")
