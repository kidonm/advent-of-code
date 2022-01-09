from itertools import product
from functools import lru_cache


def play(pos, score, roll):
    """Roll the dice, baby!"""

    new_pos = ((pos - 1 + roll) % 10) + 1
    new_score = score + new_pos
    return new_pos, new_score


target = 21

@lru_cache(maxsize=None)
def count_wins(player, pos0, score0, pos1, score1):
    """For the given state, count in how many wolds each player will win."""

    if score0 >= target:
        return 1, 0
    elif score1 >= target:
        return 0, 1

    wins = [0, 0]
    for rolls in product(range(1, 4), repeat=3):
        if player == 0:
            new_pos, new_score = play(pos0, score0, sum(rolls))
            wins0, wins1 = count_wins(1, new_pos, new_score, pos1, score1)
        else:
            new_pos, new_score = play(pos1, score1, sum(rolls))
            wins0, wins1 = count_wins(0, pos0, score0, new_pos, new_score)

        wins[0] += wins0
        wins[1] += wins1

    return wins


starts = [3, 6]
wins = count_wins(0, starts[0], 0, starts[1], 0)
print(wins)