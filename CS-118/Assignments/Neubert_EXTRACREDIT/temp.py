from json import load

periods = []

with open("weather.json", "r") as file:
    periods_dict = load(file)
periods = periods_dict.get("properties").get("periods")
print(periods)
