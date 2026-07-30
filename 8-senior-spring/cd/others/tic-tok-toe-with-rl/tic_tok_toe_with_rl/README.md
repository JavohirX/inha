# RL × TicTacToe

A reinforcement learning project that teaches a Q-Learning agent to play Tic-Tac-Toe. Built with **Python (Flask)** backend and a web UI.

## Features

- **Human vs Human** — Classic two-player tic-tac-toe
- **Human vs Agent** — Train the AI, then play against it to see how good it gets
- **Agent vs Agent** — Watch two AIs train and auto-play showcase games
- **Live RL Dashboard** — Real-time visualization of win rate, rewards, epsilon decay, Q-table growth

---

## Setup on macOS

### 1. Prerequisites

Make sure Python 3.9+ is installed. Check with:

```bash
python3 --version
```

If not installed, get it via Homebrew:

```bash
brew install python
```

### 2. Download the project

Copy the entire `rl-tictactoe` folder to your machine, or clone if from a repo.

### 3. Open Terminal and navigate to the project

```bash
cd /path/to/rl-tictactoe
```

### 4. Create a virtual environment (recommended)

```bash
python3 -m venv venv
source venv/bin/activate
```

### 5. Install dependencies

```bash
pip install -r requirements.txt
```

### 6. Run the server

```bash
python app.py
```

You'll see:

```
🎮 RL Tic-Tac-Toe Server Starting...
   Open http://localhost:5000 in your browser
```

### 7. Open the game

Open your browser and go to: **http://localhost:5000**

---

## How to Play

### Human vs Agent (recommended flow)

1. Select **Human vs Agent** on the menu
2. Choose X or O
3. Click **Train 1k** → the agent learns from 1,000 self-play games (takes ~1 second)
4. Now play against it — you'll notice it makes smarter moves!
5. Click **Train 5k** to make it even stronger
6. After 5k–10k total training episodes, the agent should play near-optimally (very hard to beat)

### Agent vs Agent

1. Select **Agent vs Agent**
2. Click **500 → Watch** (or any amount)
3. The agents train silently, then auto-play 10 visible showcase games
4. Watch the RL dashboard on the right — win rate climbs, epsilon decays

### What to observe

| Metric | What it means |
|--------|---------------|
| **Win Rate** | Should climb from ~33% toward 50%+ as the agent learns |
| **Avg Reward** | Increases as the agent wins more and loses less |
| **Epsilon (ε)** | Starts at 1.0 (100% random), decays toward 0.05 (95% greedy) |
| **Q-Table Size** | Number of state-action pairs the agent has seen |

### Agent persistence

Trained agents are automatically saved to `saved_models/`. When you restart the server and select Human vs Agent, your previously trained agent is loaded — no need to retrain!

---

## Project Structure

```
rl-tictactoe/
├── app.py              # Flask server + REST API
├── agent.py            # Q-Learning agent implementation
├── requirements.txt    # Python dependencies
├── saved_models/       # Auto-saved trained agents (JSON)
└── templates/
    └── index.html      # Full game UI (HTML/CSS/JS)
```

## How Q-Learning Works (briefly)

The agent maintains a **Q-table** mapping (state, action) → expected reward. After each game:

1. **Backpropagate** the final reward through all moves in the episode
2. **Update** Q-values using: `Q(s,a) ← Q(s,a) + α[r + γ·max(Q(s',a')) - Q(s,a)]`
3. **Decay epsilon** to shift from exploration → exploitation

Over thousands of games, the Q-table converges to optimal play for tic-tac-toe.
