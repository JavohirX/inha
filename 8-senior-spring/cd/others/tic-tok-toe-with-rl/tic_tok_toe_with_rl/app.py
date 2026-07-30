"""
Flask Backend for RL Tic-Tac-Toe
==================================
Serves the game UI and handles all game logic, training,
and agent state via REST API endpoints.
"""

from flask import Flask, render_template, jsonify, request
from agent import QLearningAgent, check_winner, get_available_actions, train_agents
import os
import json

app = Flask(__name__)

# ── Global State ──────────────────────────────────────────
game_state = {
    "board": [None] * 9,
    "current_player": "X",
    "result": None,
    "win_line": None,
    "mode": None,            # "human-human", "human-agent", "agent-agent"
    "human_symbol": "X",
    "game_count": 0,
}

agents = {
    "X": None,
    "O": None,
}

SAVE_DIR = os.path.join(os.path.dirname(__file__), "saved_models")
os.makedirs(SAVE_DIR, exist_ok=True)


def reset_board():
    game_state["board"] = [None] * 9
    game_state["current_player"] = "X"
    game_state["result"] = None
    game_state["win_line"] = None
    for sym in ["X", "O"]:
        if agents[sym]:
            agents[sym].reset_episode()


def process_result(board):
    """Check the board for a winner and update game state."""
    from agent import WINNING_LINES
    for a, b, c in WINNING_LINES:
        if board[a] and board[a] == board[b] == board[c]:
            game_state["result"] = board[a]
            game_state["win_line"] = [a, b, c]
            game_state["game_count"] += 1
            # End game for agents
            for sym in ["X", "O"]:
                if agents[sym]:
                    if board[a] == sym:
                        agents[sym].end_game("win")
                    else:
                        agents[sym].end_game("loss")
            return True
    if all(cell is not None for cell in board):
        game_state["result"] = "draw"
        game_state["win_line"] = None
        game_state["game_count"] += 1
        for sym in ["X", "O"]:
            if agents[sym]:
                agents[sym].end_game("draw")
        return True
    return False


# ── Routes ────────────────────────────────────────────────

@app.route("/")
def index():
    return render_template("index.html")


@app.route("/api/start", methods=["POST"])
def start_game():
    data = request.json
    mode = data.get("mode", "human-human")
    human_symbol = data.get("human_symbol", "X")

    game_state["mode"] = mode
    game_state["human_symbol"] = human_symbol
    game_state["game_count"] = 0

    # Initialize agents
    agents["X"] = None
    agents["O"] = None

    if mode == "human-agent":
        agent_sym = "O" if human_symbol == "X" else "X"
        # Check for saved agent
        save_path = os.path.join(SAVE_DIR, f"agent_{agent_sym}.json")
        if os.path.exists(save_path):
            agents[agent_sym] = QLearningAgent.load(save_path)
            agents[agent_sym].epsilon = 0.0  # greedy for play
        else:
            agents[agent_sym] = QLearningAgent(agent_sym)
    elif mode == "agent-agent":
        for sym in ["X", "O"]:
            save_path = os.path.join(SAVE_DIR, f"agent_{sym}.json")
            if os.path.exists(save_path):
                agents[sym] = QLearningAgent.load(save_path)
            else:
                agents[sym] = QLearningAgent(sym)

    reset_board()
    return jsonify({"ok": True, "state": get_full_state()})


@app.route("/api/state")
def get_state():
    return jsonify(get_full_state())


@app.route("/api/move", methods=["POST"])
def make_move():
    """Human makes a move."""
    data = request.json
    cell = data.get("cell")

    board = game_state["board"]
    if game_state["result"] or board[cell] is not None:
        return jsonify({"ok": False, "error": "Invalid move"})

    current = game_state["current_player"]

    # Record step for the agent that's observing (if any)
    opponent_sym = "O" if current == "X" else "X"
    if agents[opponent_sym]:
        # The opponent agent needs to know this state for learning
        pass

    board[cell] = current
    game_state["board"] = board

    if process_result(board):
        return jsonify({"ok": True, "state": get_full_state()})

    game_state["current_player"] = "O" if current == "X" else "X"
    return jsonify({"ok": True, "state": get_full_state()})


@app.route("/api/agent_move", methods=["POST"])
def agent_move():
    """Agent makes a move."""
    current = game_state["current_player"]
    agent = agents[current]

    if not agent or game_state["result"]:
        return jsonify({"ok": False, "error": "No agent or game over"})

    board = game_state["board"]
    action = agent.choose_action(board, training=False)

    if action == -1:
        return jsonify({"ok": False, "error": "No moves available"})

    agent.record_step(list(board), action)
    board[action] = current
    game_state["board"] = board

    if process_result(board):
        return jsonify({"ok": True, "state": get_full_state()})

    game_state["current_player"] = "O" if current == "X" else "X"
    return jsonify({"ok": True, "state": get_full_state()})


@app.route("/api/reset", methods=["POST"])
def reset():
    reset_board()
    return jsonify({"ok": True, "state": get_full_state()})


@app.route("/api/train", methods=["POST"])
def train():
    """Train agents for N episodes."""
    data = request.json
    episodes = min(data.get("episodes", 500), 50000)
    mode = game_state["mode"]

    if mode == "human-agent":
        agent_sym = "O" if game_state["human_symbol"] == "X" else "X"
        if not agents[agent_sym]:
            agents[agent_sym] = QLearningAgent(agent_sym)
        # Restore epsilon for training
        agents[agent_sym].epsilon = max(agents[agent_sym].epsilon, 0.3)
        # Train vs random
        if agent_sym == "X":
            train_agents(agents[agent_sym], None, episodes)
        else:
            train_agents(None, agents[agent_sym], episodes)
        # Save
        agents[agent_sym].save(os.path.join(SAVE_DIR, f"agent_{agent_sym}.json"))
        # Set greedy for play
        agents[agent_sym].epsilon = 0.0

    elif mode == "agent-agent":
        if not agents["X"]:
            agents["X"] = QLearningAgent("X")
        if not agents["O"]:
            agents["O"] = QLearningAgent("O")
        agents["X"].epsilon = max(agents["X"].epsilon, 0.3)
        agents["O"].epsilon = max(agents["O"].epsilon, 0.3)
        train_agents(agents["X"], agents["O"], episodes)
        agents["X"].save(os.path.join(SAVE_DIR, "agent_X.json"))
        agents["O"].save(os.path.join(SAVE_DIR, "agent_O.json"))

    reset_board()
    return jsonify({"ok": True, "state": get_full_state()})


@app.route("/api/stats")
def get_stats():
    """Return agent training statistics."""
    result = {}
    for sym in ["X", "O"]:
        if agents[sym]:
            result[sym] = agents[sym].get_stats_snapshot()
    return jsonify(result)


@app.route("/api/save", methods=["POST"])
def save_agents():
    for sym in ["X", "O"]:
        if agents[sym]:
            agents[sym].save(os.path.join(SAVE_DIR, f"agent_{sym}.json"))
    return jsonify({"ok": True})


@app.route("/api/reset_agents", methods=["POST"])
def reset_agents():
    """Delete saved models and create fresh agents."""
    for sym in ["X", "O"]:
        path = os.path.join(SAVE_DIR, f"agent_{sym}.json")
        if os.path.exists(path):
            os.remove(path)
        agents[sym] = None
    return jsonify({"ok": True})


def get_full_state():
    stats = {}
    for sym in ["X", "O"]:
        if agents[sym]:
            stats[sym] = agents[sym].get_stats_snapshot()
    return {
        "board": game_state["board"],
        "current_player": game_state["current_player"],
        "result": game_state["result"],
        "win_line": game_state["win_line"],
        "mode": game_state["mode"],
        "human_symbol": game_state["human_symbol"],
        "game_count": game_state["game_count"],
        "agent_stats": stats,
    }


if __name__ == "__main__":
    print("\n🎮 RL Tic-Tac-Toe Server Starting...")
    print("   Open http://localhost:5000 in your browser\n")
    app.run(debug=True, port=5000)
