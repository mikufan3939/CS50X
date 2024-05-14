# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    newDict = {}
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for i in reader:
            newDict = {"team": i["team"], "rating": int(i["rating"])}
            teams.append(newDict)

    counts = {}
    for i in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:
            counts[winner] = counts[winner]+1
        else:
            counts[winner] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N: .1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    winners = []
    tourWinner = {}
    numberTeams = len(teams)
    roundNumber = 0

    while True:
        numberTeams = numberTeams/2
        roundNumber = roundNumber+1
        if numberTeams == 1:
            break
    for i in range(roundNumber):
        if i == 0:
            winners = simulate_round(teams)
        else:
            winners = simulate_round(winners)
    tourWinner = winners[0]
    return tourWinner["team"]


if __name__ == "__main__":
    main()
