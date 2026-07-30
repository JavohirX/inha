"""
Q-Learning Agent for Tic-Tac-Toe
=================================
Implements a tabular Q-Learning RL agent that learns to play tic-tac-toe
by building a state-action value table through self-play or play against
a random opponent.
"""

import random
import json
import os
from collections import defaultdict

WINNING_LINES = [
    [0, 1, 2], [3, 4, 5], [6, 7, 8],  # rows
    [0, 3, 6], [1, 4, 7], [2, 5, 8],  # cols
    [0, 4, 8], [2, 4, 6],              # diagonals
]


def check_winner(board):
    """Returns 'X', 'O', 'draw', or None."""
    for a, b, c in WINNING_LINES:
        if board[a] and board[a] == board[b] == board[c]:
            return board[a]
    if all(cell is not None for cell in board):
        return "draw"
    return None


def get_available_actions(board):
    return [i for i, cell in enumerate(board) if cell is None]


class QLearningAgent:
    def __init__(self, symbol, lr=0.3, discount=0.95, epsilon=1.0,
                 epsilon_decay=0.9995, epsilon_min=0.05):
        self.symbol = symbol
        self.lr = lr
        self.discount = discount
        self.epsilon = epsilon
        self.epsilon_decay = epsilon_decay
        self.epsilon_min = epsilon_min
        self.q_table = defaultdict(float)
        self.history = []  # list of (state_key, action)

        # Training statistics
        self.stats = {
            "wins": 0,
            "losses": 0,
            "draws": 0,
            "games": 0,
            "rewards": [],
            "win_rates": [],
            "epsilons": [],
            "avg_rewards": [],
            "q_table_sizes": [],
        }

    def _state_key(self, board):
        return "".join(c if c else "_" for c in board)

    def _q_key(self, state, action):
        return f"{state}:{action}"

    def get_q(self, state, action):
        return self.q_table[self._q_key(state, action)]

    def set_q(self, state, action, value):
        self.q_table[self._q_key(state, action)] = value

    def choose_action(self, board, training=True):
        """Epsilon-greedy action selection."""
        state = self._state_key(board)
        actions = get_available_actions(board)
        if not actions:
            return -1

        # Exploration
        if training and random.random() < self.epsilon:
            return random.choice(actions)

        # Exploitation: pick action with highest Q-value
        best_action = actions[0]
        best_value = self.get_q(state, actions[0])
        for a in actions[1:]:
            v = self.get_q(state, a)
            if v > best_value:
                best_value = v
                best_action = a
        return best_action

    def record_step(self, board, action):
        self.history.append((self._state_key(board), action))

    def learn(self, reward):
        """Backpropagate reward through episode history using Q-learning update."""
        self.stats["rewards"].append(reward)
        r = reward
        for i in range(len(self.history) - 1, -1, -1):
            state, action = self.history[i]
            current_q = self.get_q(state, action)

            future_q = 0.0
            if i < len(self.history) - 1:
                next_state = self.history[i + 1][0]
                next_actions = [j for j, ch in enumerate(next_state) if ch == "_"]
                if next_actions:
                    future_q = max(self.get_q(next_state, a) for a in next_actions)

            new_q = current_q + self.lr * (r + self.discount * future_q - current_q)
            self.set_q(state, action, new_q)
            r *= self.discount

        self.history = []
        self.epsilon = max(self.epsilon_min, self.epsilon * self.epsilon_decay)

    def end_game(self, result):
        """Call after each game. result = 'win', 'loss', or 'draw'."""
        self.stats["games"] += 1
        if result == "win":
            self.stats["wins"] += 1
            reward = 1.0
        elif result == "loss":
            self.stats["losses"] += 1
            reward = -1.0
        else:
            self.stats["draws"] += 1
            reward = 0.3

        self.learn(reward)

        self.stats["win_rates"].append(self.stats["wins"] / self.stats["games"])
        self.stats["epsilons"].append(self.epsilon)
        self.stats["q_table_sizes"].append(len(self.q_table))
        last_50 = self.stats["rewards"][-50:]
        self.stats["avg_rewards"].append(sum(last_50) / len(last_50))

    def reset_episode(self):
        self.history = []

    def get_stats_snapshot(self, last_n=200):
        """Return stats trimmed to last N points for JSON serialization."""
        return {
            "wins": self.stats["wins"],
            "losses": self.stats["losses"],
            "draws": self.stats["draws"],
            "games": self.stats["games"],
            "epsilon": round(self.epsilon, 6),
            "q_table_size": len(self.q_table),
            "win_rates": self.stats["win_rates"][-last_n:],
            "avg_rewards": self.stats["avg_rewards"][-last_n:],
            "epsilons": self.stats["epsilons"][-last_n:],
            "q_table_sizes": self.stats["q_table_sizes"][-last_n:],
        }

    def save(self, path):
        data = {
            "symbol": self.symbol,
            "lr": self.lr,
            "discount": self.discount,
            "epsilon": self.epsilon,
            "q_table": dict(self.q_table),
            "stats": {
                "wins": self.stats["wins"],
                "losses": self.stats["losses"],
                "draws": self.stats["draws"],
                "games": self.stats["games"],
                "rewards": self.stats["rewards"][-500:],
                "win_rates": self.stats["win_rates"][-500:],
                "epsilons": self.stats["epsilons"][-500:],
                "avg_rewards": self.stats["avg_rewards"][-500:],
                "q_table_sizes": self.stats["q_table_sizes"][-500:],
            },
        }
        with open(path, "w") as f:
            json.dump(data, f)

    @classmethod
    def load(cls, path):
        with open(path, "r") as f:
            data = json.load(f)
        agent = cls(data["symbol"], lr=data["lr"], discount=data["discount"],
                     epsilon=data["epsilon"])
        agent.q_table = defaultdict(float, data["q_table"])
        agent.stats = data["stats"]
        # Ensure list keys exist
        for key in ["rewards", "win_rates", "epsilons", "avg_rewards", "q_table_sizes"]:
            if key not in agent.stats:
                agent.stats[key] = []
        return agent


def train_agents(agent_x, agent_o, episodes=1000):
    """
    Train two agents against each other (or one agent against random).
    If an agent is None, a random player is used for that side.
    Returns per-episode results for logging.
    """
    results = []
    for _ in range(episodes):
        board = [None] * 9
        current = "X"
        if agent_x:
            agent_x.reset_episode()
        if agent_o:
            agent_o.reset_episode()

        winner = None
        while winner is None:
            agent = agent_x if current == "X" else agent_o
            if agent:
                action = agent.choose_action(board, training=True)
                agent.record_step(list(board), action)
            else:
                action = random.choice(get_available_actions(board))

            board[action] = current
            winner = check_winner(board)
            current = "O" if current == "X" else "X"

        if winner == "draw":
            if agent_x:
                agent_x.end_game("draw")
            if agent_o:
                agent_o.end_game("draw")
            results.append("draw")
        else:
            if agent_x:
                agent_x.end_game("win" if winner == "X" else "loss")
            if agent_o:
                agent_o.end_game("win" if winner == "O" else "loss")
            results.append(winner)

    return results
