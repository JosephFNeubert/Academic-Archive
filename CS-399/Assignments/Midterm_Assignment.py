"""
File: Midterm_Assignment.py
Author: Joseph Neubert
Description: Program that allows for the game Chicago and its variant Double-Roll to be played
"""

from abc import ABC, abstractmethod
from dataclasses import dataclass
from random import randint


@dataclass
class Player:
    name: str

    def __str__(self) -> str:
        return f"{self.name}"


class Game:
    games_played = 0

    def __init__(self, players: [Player]) -> None:
        self.players = players

    def champions(self, results: {Player: int}) -> [Player]:
        """:return: list of player(s), with the highest score, or an empty list, if nobody scored."""
        max_score = max(results.values())
        champions_dict = {x: y for x, y in results.items() if y == max_score}
        return list(champions_dict.items())

    @abstractmethod
    def play(self) -> [Player]: ...


class Chicago(Game):
    def __init__(self, players: [Player]) -> None:
        super().__init__(players)

    def play(self) -> [Player]:
        gameplay = {}
        for i in self.players:
            score = 0
            for j in range(11):
                dice1 = randint(1, 6)
                dice2 = randint(1, 6)
                dice_total = dice1 + dice2
                if dice_total == j + 2:
                    score += dice_total
            gameplay.update({str(i): score})
        return super().champions(gameplay)


class DoubleRoll(Game):
    def __init__(self, players: [Player]) -> None:
        super().__init__(players)

    def play(self) -> [Player]:
        gameplay = {}
        for i in self.players:
            score = 0
            for j in range(11):
                dice1 = randint(1, 6)
                dice2 = randint(1, 6)
                dice_total = dice1 + dice2
                if dice_total == j + 2:
                    score += dice_total
                else:
                    dice2 = randint(1, 6)
                    dice_total = dice1 + dice2
                    if dice_total == j + 2:
                        score += dice_total
            gameplay.update({str(i): score})
        return super().champions(gameplay)


contestants = [
    Player("Ricky Bell"),
    Player("Michael Bivins"),
    Player("Bobby Brown"),
    Player("Ronnie DeVoe"),
    Player("Johnny Gill"),
    Player("Ralph Tresvant"),
]

winners_list = []
for game in (Chicago(contestants), DoubleRoll(contestants)):
    while True:
        winners = game.play()
        Game.games_played += 1
        if len(winners) > 1:
            winners_list.append([winners, Game.games_played])
            Game.games_played = 0
            break

first_game_winners = winners_list[0][0]
second_game_winners = winners_list[1][0]
first_games_played = winners_list[0][1]
second_games_played = winners_list[1][1]
print(
    f"After {first_games_played} Chicago games played, a single game had multiple winners:"
)
for i in first_game_winners:
    print(f"{i[0]}, Score: {i[1]}")
print(
    f"After {second_games_played} Double-Roll games played, a single game had multiple winners:"
)
for i in second_game_winners:
    print(f"{i[0]}, Score: {i[1]}")
