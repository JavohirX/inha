# =============================================================================
#  DQN CartPole — CSE4020 Capstone Design
#  Deep Q-Network from scratch using PyTorch + Gymnasium
#
#  HOW TO RUN:
#    pip install gymnasium torch matplotlib numpy
#    python dqn_cartpole.py
#
#  WHAT YOU WILL SEE:
#    - Live reward graph updated every episode
#    - Console logs showing training progress
#    - A final demo of the trained agent balancing the pole
# =============================================================================

import random
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from collections import deque
import gymnasium as gym
import time

# ─────────────────────────────────────────────────────────────────────────────
# SECTION 1 — HYPERPARAMETERS
# All in one place so students can easily experiment
# ─────────────────────────────────────────────────────────────────────────────

# Environment
ENV_NAME        = "CartPole-v1"   # The Gymnasium environment
MAX_STEPS       = 500             # Max steps per episode (CartPole-v1 default)

# Replay Buffer
BUFFER_SIZE     = 10_000          # How many experiences to store
BATCH_SIZE      = 64              # How many to sample for each training step
MIN_BUFFER      = 500             # Don't start training until buffer has this many

# Neural Network
HIDDEN_SIZE     = 64              # Neurons in each hidden layer
LEARNING_RATE   = 1e-3            # Neural network optimizer learning rate (α_NN)

# Q-Learning
GAMMA           = 0.99            # Discount factor (γ) — how much we value future rewards
TAU             = 0.005           # Soft update rate for target network

# Exploration (ε-greedy)
EPS_START       = 1.0             # Start with 100% exploration
EPS_END         = 0.05            # Never go below 5% exploration
EPS_DECAY       = 0.995           # Multiply ε by this each episode

# Training
NUM_EPISODES    = 500             # Total episodes to train
TARGET_SCORE    = 475             # Stop early if we hit this average score
SOLVED_WINDOW   = 20              # Average over this many episodes to check TARGET_SCORE

# Demo
DEMO_EPISODES   = 3               # How many episodes to show after training


# ─────────────────────────────────────────────────────────────────────────────
# SECTION 2 — THE NEURAL NETWORK
# This REPLACES the Q-table from our maze example
# Input:  4 values (CartPole state)
# Output: 2 values (Q-values for Left and Right)
# ─────────────────────────────────────────────────────────────────────────────

class DQNNetwork(nn.Module):
    """
    The Q-Network: approximates Q(s, a) for all actions at once.

    Architecture:
        Input(4)  →  Hidden(64, ReLU)  →  Hidden(64, ReLU)  →  Output(2)

    CartPole state (4 inputs):
        [0] cart position       (−4.8  to  +4.8)
        [1] cart velocity       (−inf  to  +inf)
        [2] pole angle          (−0.418 to +0.418 radians)
        [3] pole angular velocity (−inf to +inf)

    Output (2 values):
        [0] Q(s, push_left)
        [1] Q(s, push_right)
    """

    def __init__(self, state_size, action_size, hidden_size=HIDDEN_SIZE):
        super(DQNNetwork, self).__init__()

        self.network = nn.Sequential(
            nn.Linear(state_size, hidden_size),   # Layer 1: Input → Hidden1
            nn.ReLU(),                             # ReLU activation
            nn.Linear(hidden_size, hidden_size),  # Layer 2: Hidden1 → Hidden2
            nn.ReLU(),                             # ReLU activation
            nn.Linear(hidden_size, action_size)   # Layer 3: Hidden2 → Output (no activation!)
        )

    def forward(self, state):
        """
        Forward pass: state vector → Q-values for all actions
        This is called automatically by PyTorch during training.
        """
        return self.network(state)


# ─────────────────────────────────────────────────────────────────────────────
# SECTION 3 — EXPERIENCE REPLAY BUFFER
# Stores (s, a, r, s', done) tuples and samples random batches
# This solves the "correlated data" problem from our DQN lecture
# ─────────────────────────────────────────────────────────────────────────────

class ReplayBuffer:
    """
    Circular buffer storing past experiences.
    When full, oldest experiences are automatically overwritten.

    Each experience = (state, action, reward, next_state, done)
    - state      : the observation before the action
    - action     : what the agent did (0=left, 1=right)
    - reward     : +1 for every step the pole stays up
    - next_state : the observation after the action
    - done       : True if the episode ended (pole fell or max steps reached)
    """

    def __init__(self, capacity):
        self.buffer = deque(maxlen=capacity)  # deque auto-removes oldest when full

    def push(self, state, action, reward, next_state, done):
        """Store one experience."""
        self.buffer.append((state, action, reward, next_state, done))

    def sample(self, batch_size):
        """Sample a random batch of experiences — this breaks correlations."""
        batch = random.sample(self.buffer, batch_size)
        # Unzip: list of tuples → separate lists
        states, actions, rewards, next_states, dones = zip(*batch)
        return (
            np.array(states,      dtype=np.float32),
            np.array(actions,     dtype=np.int64),
            np.array(rewards,     dtype=np.float32),
            np.array(next_states, dtype=np.float32),
            np.array(dones,       dtype=np.float32)
        )

    def __len__(self):
        return len(self.buffer)


# ─────────────────────────────────────────────────────────────────────────────
# SECTION 4 — THE DQN AGENT
# Combines: network, target network, replay buffer, ε-greedy, training
# ─────────────────────────────────────────────────────────────────────────────

class DQNAgent:
    """
    The complete DQN agent.

    Key components:
        online_net   : The network we train every step (the learner)
        target_net   : Frozen copy, used only to compute stable targets
        replay_buffer: Stores experiences for random batch training
        epsilon      : Current exploration rate (decays over time)
        optimizer    : Adam optimizer for gradient descent
    """

    def __init__(self, state_size, action_size):
        self.state_size  = state_size
        self.action_size = action_size
        self.epsilon     = EPS_START

        # ── Two Networks (DQN Innovation #2: Target Network) ──
        self.online_net = DQNNetwork(state_size, action_size)
        self.target_net = DQNNetwork(state_size, action_size)

        # Target starts as an exact copy of online
        self.target_net.load_state_dict(self.online_net.state_dict())
        self.target_net.eval()  # Target never gets gradient updates directly

        # ── Optimizer (Adam is better than plain SGD) ──
        self.optimizer = optim.Adam(self.online_net.parameters(), lr=LEARNING_RATE)

        # ── Loss Function (MSE between prediction and target) ──
        self.loss_fn = nn.MSELoss()

        # ── Replay Buffer (DQN Innovation #1) ──
        self.replay_buffer = ReplayBuffer(BUFFER_SIZE)

        # ── Tracking ──
        self.training_steps = 0

    # ── ACTION SELECTION: ε-greedy ─────────────────────────────────────────
    def select_action(self, state, training=True):
        """
        ε-greedy policy — exactly the same as our maze example!
        With prob ε  → explore: pick random action
        With prob 1-ε → exploit: pick argmax Q(s, a)
        """
        if training and random.random() < self.epsilon:
            # EXPLORE: random action
            return random.randint(0, self.action_size - 1)
        else:
            # EXPLOIT: best action from Q-network
            with torch.no_grad():  # No gradient needed for action selection
                state_tensor = torch.FloatTensor(state).unsqueeze(0)  # Add batch dimension
                q_values = self.online_net(state_tensor)               # Forward pass
                return q_values.argmax().item()                        # argmax Q(s, a)

    # ── STORE EXPERIENCE ───────────────────────────────────────────────────
    def store_experience(self, state, action, reward, next_state, done):
        """Add one (s, a, r, s', done) tuple to the replay buffer."""
        self.replay_buffer.push(state, action, reward, next_state, done)

    # ── TRAIN: ONE BELLMAN UPDATE STEP ─────────────────────────────────────
    def train_step(self):
        """
        One complete DQN training step:
        1. Sample random batch from replay buffer
        2. Compute Q-predictions (online network, forward pass)
        3. Compute Q-targets (target network, Bellman equation)
        4. Compute loss (MSE)
        5. Backpropagate and update online network weights
        6. Soft-update target network

        This is the core of DQN — identical to our hand calculation!
        """
        if len(self.replay_buffer) < MIN_BUFFER:
            return None  # Not enough experience yet

        # ── Step 1: Sample random batch ──────────────────────────────────
        states, actions, rewards, next_states, dones = self.replay_buffer.sample(BATCH_SIZE)

        # Convert numpy arrays to PyTorch tensors
        states_t      = torch.FloatTensor(states)
        actions_t     = torch.LongTensor(actions)
        rewards_t     = torch.FloatTensor(rewards)
        next_states_t = torch.FloatTensor(next_states)
        dones_t       = torch.FloatTensor(dones)

        # ── Step 2: Compute Q-predictions (online network) ────────────────
        # online_net gives Q-values for ALL actions
        # We select only the Q-value for the action that was actually taken
        all_q_values    = self.online_net(states_t)               # shape: [batch, 2]
        q_predictions   = all_q_values.gather(1, actions_t.unsqueeze(1)).squeeze(1)
        # q_predictions shape: [batch] — one Q-value per experience

        # ── Step 3: Compute Q-targets using Bellman equation ──────────────
        with torch.no_grad():  # Target network — no gradient
            # Target network gives Q-values for next states
            next_q_values   = self.target_net(next_states_t)       # shape: [batch, 2]
            max_next_q      = next_q_values.max(1)[0]              # max Q(s', a')
            # Bellman: y = R + γ * max Q(s', a')  [if not done]
            #          y = R                       [if done — no future]
            q_targets = rewards_t + GAMMA * max_next_q * (1 - dones_t)

        # ── Step 4: Compute loss ──────────────────────────────────────────
        loss = self.loss_fn(q_predictions, q_targets)
        # loss = mean of (q_targets - q_predictions)²

        # ── Step 5: Backpropagation + weight update ───────────────────────
        self.optimizer.zero_grad()   # Clear old gradients
        loss.backward()              # Compute gradients (chain rule)
        # Gradient clipping: prevents exploding gradients (good practice)
        torch.nn.utils.clip_grad_norm_(self.online_net.parameters(), max_norm=1.0)
        self.optimizer.step()        # Update weights: W ← W - α × gradient

        # ── Step 6: Soft update of target network ─────────────────────────
        # Instead of hard copy every N steps, we blend weights gradually:
        # target_weights ← τ * online_weights + (1-τ) * target_weights
        # This is smoother than the hard copy described in our lecture
        for target_param, online_param in zip(
            self.target_net.parameters(), self.online_net.parameters()
        ):
            target_param.data.copy_(
                TAU * online_param.data + (1.0 - TAU) * target_param.data
            )

        self.training_steps += 1
        return loss.item()

    # ── DECAY EPSILON ──────────────────────────────────────────────────────
    def decay_epsilon(self):
        """Reduce ε each episode so agent explores less as it learns more."""
        self.epsilon = max(EPS_END, self.epsilon * EPS_DECAY)


# ─────────────────────────────────────────────────────────────────────────────
# SECTION 5 — LIVE VISUALIZATION
# Shows reward curve updating in real time during training
# ─────────────────────────────────────────────────────────────────────────────

class LivePlot:
    """Live matplotlib plot that updates during training."""

    def __init__(self):
        plt.ion()  # Interactive mode ON
        self.fig, (self.ax1, self.ax2) = plt.subplots(2, 1, figsize=(10, 7))
        self.fig.suptitle("DQN Training — CartPole-v1\nCSE4020 Capstone Design",
                           fontsize=14, fontweight='bold', color='#1F4E79')

        # Top plot: Episode rewards
        self.ax1.set_xlabel("Episode")
        self.ax1.set_ylabel("Score (steps survived)")
        self.ax1.set_title("Episode Reward", fontsize=11, color='#2E75B6')
        self.ax1.axhline(y=TARGET_SCORE, color='green', linestyle='--',
                         alpha=0.7, label=f'Target ({TARGET_SCORE})')
        self.ax1.axhline(y=200, color='orange', linestyle='--',
                         alpha=0.5, label='Good (200)')
        self.ax1.legend(fontsize=9)
        self.ax1.set_ylim(0, MAX_STEPS + 10)
        self.ax1.grid(True, alpha=0.3)

        # Bottom plot: Epsilon decay
        self.ax2.set_xlabel("Episode")
        self.ax2.set_ylabel("ε (exploration rate)")
        self.ax2.set_title("Exploration Rate (ε) Decay", fontsize=11, color='#C55A11')
        self.ax2.set_ylim(0, 1.05)
        self.ax2.axhline(y=EPS_END, color='red', linestyle='--',
                         alpha=0.5, label=f'Minimum ε ({EPS_END})')
        self.ax2.legend(fontsize=9)
        self.ax2.grid(True, alpha=0.3)

        self.episodes   = []
        self.scores     = []
        self.avg_scores = []
        self.epsilons   = []

        plt.tight_layout()
        plt.show(block=False)
        plt.pause(0.01)

    def update(self, episode, score, avg_score, epsilon):
        self.episodes.append(episode)
        self.scores.append(score)
        self.avg_scores.append(avg_score)
        self.epsilons.append(epsilon)

        # Clear and redraw (more reliable across platforms)
        self.ax1.cla()
        self.ax1.set_xlabel("Episode")
        self.ax1.set_ylabel("Score (steps survived)")
        self.ax1.set_title("Episode Reward", fontsize=11, color='#2E75B6')
        self.ax1.axhline(y=TARGET_SCORE, color='green', linestyle='--',
                         alpha=0.7, label=f'Target ({TARGET_SCORE})')
        self.ax1.axhline(y=200, color='orange', linestyle='--',
                         alpha=0.5, label='Good (200)')
        self.ax1.plot(self.episodes, self.scores, color='#93C5FD',
                      alpha=0.5, linewidth=0.8, label='Episode score')
        self.ax1.plot(self.episodes, self.avg_scores, color='#1D4ED8',
                      linewidth=2.0, label=f'Avg ({SOLVED_WINDOW} ep)')
        self.ax1.set_ylim(0, MAX_STEPS + 10)
        self.ax1.legend(fontsize=9)
        self.ax1.grid(True, alpha=0.3)

        self.ax2.cla()
        self.ax2.set_xlabel("Episode")
        self.ax2.set_ylabel("ε (exploration rate)")
        self.ax2.set_title("Exploration Rate (ε) Decay", fontsize=11, color='#C55A11')
        self.ax2.plot(self.episodes, self.epsilons, color='#F97316', linewidth=2.0)
        self.ax2.axhline(y=EPS_END, color='red', linestyle='--',
                         alpha=0.5, label=f'Minimum ε ({EPS_END})')
        self.ax2.set_ylim(0, 1.05)
        self.ax2.legend(fontsize=9)
        self.ax2.grid(True, alpha=0.3)

        plt.tight_layout()
        self.fig.canvas.draw()
        self.fig.canvas.flush_events()
        plt.pause(0.001)

    def save(self, path):
        plt.ioff()
        self.fig.savefig(path, dpi=120, bbox_inches='tight')
        print(f"  Training plot saved to: {path}")


# ─────────────────────────────────────────────────────────────────────────────
# SECTION 6 — MAIN TRAINING LOOP
# ─────────────────────────────────────────────────────────────────────────────

def train():
    print("=" * 60)
    print("  DQN CartPole Training — CSE4020 Capstone Design")
    print("=" * 60)
    print(f"  Environment  : {ENV_NAME}")
    print(f"  Episodes     : {NUM_EPISODES}")
    print(f"  Architecture : 4 → {HIDDEN_SIZE} → {HIDDEN_SIZE} → 2")
    print(f"  Buffer size  : {BUFFER_SIZE}")
    print(f"  Batch size   : {BATCH_SIZE}")
    print(f"  γ (discount) : {GAMMA}")
    print(f"  ε start→end  : {EPS_START} → {EPS_END}")
    print("=" * 60)

    # ── Setup ──────────────────────────────────────────────────────────────
    env   = gym.make(ENV_NAME)
    agent = DQNAgent(
        state_size  = env.observation_space.shape[0],  # 4
        action_size = env.action_space.n               # 2
    )
    plot     = LivePlot()
    scores   = []
    solved   = False
    start_t  = time.time()

    # ── Episode Loop ───────────────────────────────────────────────────────
    for episode in range(1, NUM_EPISODES + 1):

        state, _ = env.reset()      # Reset environment, get initial state
        episode_score = 0
        episode_loss  = []

        # ── Step Loop (one episode) ──────────────────────────────────────
        for step in range(MAX_STEPS):

            # 1. Agent selects action (ε-greedy)
            action = agent.select_action(state)

            # 2. Environment executes action, returns feedback
            next_state, reward, terminated, truncated, _ = env.step(action)
            done = terminated or truncated

            # 3. Store experience in replay buffer
            agent.store_experience(state, action, reward, next_state, done)

            # 4. Train the network (one Bellman update)
            loss = agent.train_step()
            if loss is not None:
                episode_loss.append(loss)

            # 5. Advance state
            state          = next_state
            episode_score += reward

            if done:
                break

        # ── End of Episode ────────────────────────────────────────────────
        scores.append(episode_score)
        agent.decay_epsilon()

        avg_score = np.mean(scores[-SOLVED_WINDOW:]) if len(scores) >= SOLVED_WINDOW \
                    else np.mean(scores)
        avg_loss  = np.mean(episode_loss) if episode_loss else 0.0

        # Update live plot
        plot.update(episode, episode_score, avg_score, agent.epsilon)

        # Console log
        status = ""
        if avg_score >= TARGET_SCORE and len(scores) >= SOLVED_WINDOW and not solved:
            status = "  ★ SOLVED!"
            solved = True

        if episode % 10 == 0 or solved:
            elapsed = time.time() - start_t
            print(
                f"  Ep {episode:4d}/{NUM_EPISODES} | "
                f"Score: {episode_score:5.0f} | "
                f"Avg({SOLVED_WINDOW}): {avg_score:6.1f} | "
                f"ε: {agent.epsilon:.3f} | "
                f"Loss: {avg_loss:.4f} | "
                f"Time: {elapsed:5.1f}s"
                f"{status}"
            )

        if solved:
            print(f"\n  ✅ Environment solved after {episode} episodes!")
            break

    env.close()
    elapsed = time.time() - start_t
    print(f"\n  Training complete in {elapsed:.1f}s | "
          f"Buffer: {len(agent.replay_buffer)} | "
          f"Training steps: {agent.training_steps}")

    plot.save("training_plot.png")
    return agent, scores, plot


# ─────────────────────────────────────────────────────────────────────────────
# SECTION 7 — POST-TRAINING DEMO
# Renders the trained agent using matplotlib — works on ALL platforms.
# No pygame, no display server, no OpenGL required.
# ─────────────────────────────────────────────────────────────────────────────

def draw_cartpole_frame(ax, state, step, score, action, episode, total_ep):
    """
    Draw one CartPole frame onto a matplotlib axis.
    Called every step to animate the trained agent.

    Physics layout (matches Gymnasium CartPole exactly):
      - Cart slides left/right on a track
      - Pole is a rigid rod attached to the cart top
      - Pole angle = 0 means perfectly upright
    """
    ax.cla()
    ax.set_xlim(-3.0, 3.0)
    ax.set_ylim(-0.5, 2.2)
    ax.set_aspect('equal')
    ax.set_facecolor('#0f172a')
    ax.axis('off')

    cart_x, cart_v, pole_angle, pole_v = state
    pole_len = 1.0   # Visual length (Gymnasium uses 0.5m half-length)

    # ── Track ──────────────────────────────────────────────────────────────
    ax.plot([-2.8, 2.8], [0.0, 0.0], color='#334155', linewidth=3, zorder=1)
    ax.plot([-2.4, -2.4], [-0.05, 0.15], color='#ef4444', linewidth=2,
            linestyle='--', alpha=0.6)  # Left boundary
    ax.plot([ 2.4,  2.4], [-0.05, 0.15], color='#ef4444', linewidth=2,
            linestyle='--', alpha=0.6)  # Right boundary

    # ── Cart ───────────────────────────────────────────────────────────────
    cart_w, cart_h = 0.5, 0.25
    cart_rect = plt.Rectangle(
        (cart_x - cart_w/2, 0.0), cart_w, cart_h,
        color='#2563eb', zorder=3, linewidth=1.5,
        edgecolor='#3b82f6'
    )
    ax.add_patch(cart_rect)

    # Wheels
    for wx in [cart_x - 0.15, cart_x + 0.15]:
        wheel = plt.Circle((wx, -0.06), 0.07, color='#1e293b',
                            zorder=4, linewidth=1.5, edgecolor='#64748b')
        ax.add_patch(wheel)
        hub = plt.Circle((wx, -0.06), 0.03, color='#475569', zorder=5)
        ax.add_patch(hub)

    # ── Pole ───────────────────────────────────────────────────────────────
    pole_base_y = cart_h
    pole_tip_x  = cart_x + pole_len * np.sin(pole_angle)
    pole_tip_y  = pole_base_y + pole_len * np.cos(pole_angle)

    # Color: green=safe, yellow=warning, red=danger
    danger = min(abs(pole_angle) / 0.2095, 1.0)
    r = int(34  + danger * 220)
    g = int(197 - danger * 180)
    b = int(94  - danger * 60)
    pole_color = f'#{r:02x}{g:02x}{b:02x}'

    ax.plot([cart_x, pole_tip_x], [pole_base_y, pole_tip_y],
            color=pole_color, linewidth=8, solid_capstyle='round', zorder=5)
    # Pole tip ball
    ax.plot(pole_tip_x, pole_tip_y, 'o',
            color=pole_color, markersize=10, zorder=6)
    # Pivot
    ax.plot(cart_x, pole_base_y, 'o',
            color='#94a3b8', markersize=7, zorder=7)

    # ── Action Arrow ───────────────────────────────────────────────────────
    arrow_dx = 0.35 if action == 1 else -0.35
    arrow_x  = cart_x + (0.32 if action == 1 else -0.32)
    arrow_color = '#f97316' if action == 1 else '#3b82f6'
    ax.annotate('', xy=(arrow_x + arrow_dx, cart_h/2 + 0.02),
                 xytext=(arrow_x, cart_h/2 + 0.02),
                 arrowprops=dict(arrowstyle='->', color=arrow_color,
                                 lw=2.5, mutation_scale=16))
    action_txt = '→ Push RIGHT' if action == 1 else '← Push LEFT'
    ax.text(cart_x, -0.35, action_txt,
            ha='center', fontsize=9, color=arrow_color,
            fontfamily='monospace', fontweight='bold')

    # ── State Values (teaching overlay) ────────────────────────────────────
    info = (
        f"cart pos:  {cart_x:+.3f}\n"
        f"cart vel:  {cart_v:+.3f}\n"
        f"pole ang:  {pole_angle:+.4f} rad\n"
        f"pole vel:  {pole_v:+.3f}"
    )
    ax.text(-2.85, 2.1, info, fontsize=8.5, color='#94a3b8',
            fontfamily='monospace', va='top',
            bbox=dict(boxstyle='round,pad=0.4', facecolor='#1e293b',
                      edgecolor='#334155', alpha=0.9))

    # ── Score + Episode header ──────────────────────────────────────────────
    ax.set_title(
        f"DEMO — Episode {episode}/{total_ep}   |   "
        f"Step: {step}   |   Score: {score}   |   ε = 0.0 (pure exploit)",
        fontsize=11, color='#e2e8f0', pad=10,
        fontfamily='monospace'
    )

    # ── Angle danger bar ───────────────────────────────────────────────────
    bar_x = np.linspace(2.0, 2.7, 100)
    bar_y = np.linspace(0.1, 1.8, 100)
    bar_fill = int(danger * 100)
    ax.barh(1.0, danger * 0.6, left=2.05, height=1.5,
            color=pole_color, alpha=0.3)
    ax.text(2.35, -0.3, 'danger', ha='center', fontsize=7.5,
            color='#64748b', fontfamily='monospace')


def demo_agent(agent, num_episodes=DEMO_EPISODES):
    """
    Visualise the trained agent using matplotlib animation.
    Works on every platform — no pygame, no OpenGL, no display server needed.
    ε is forced to 0.0 so agent always exploits (no random actions).
    """
    print("\n" + "=" * 60)
    print("  DEMO: Trained Agent — Matplotlib Visualisation")
    print("  (ε = 0.0 — pure exploitation, no random actions)")
    print("  Close the window to exit.")
    print("=" * 60)

    env = gym.make(ENV_NAME)   # No render_mode — we draw ourselves

    saved_epsilon = agent.epsilon
    agent.epsilon = 0.0        # Pure exploitation

    # ── Set up figure ──────────────────────────────────────────────────────
    plt.ion()
    fig, ax = plt.subplots(figsize=(10, 5))
    fig.patch.set_facecolor('#0a0e1a')
    fig.suptitle(
        "DQN CartPole Demo — CSE4020 Capstone Design\n"
        "Trained agent balancing the pole (close window when done)",
        fontsize=11, color='#e2e8f0', fontfamily='monospace'
    )
    plt.tight_layout(pad=2.0)

    demo_scores = []

    for ep in range(1, num_episodes + 1):
        state, _ = env.reset()
        score     = 0
        action    = 1  # default for first frame

        for step in range(1, MAX_STEPS + 1):
            # Draw current frame
            draw_cartpole_frame(ax, state, step, score, action,
                                ep, num_episodes)
            fig.canvas.draw()
            fig.canvas.flush_events()
            plt.pause(0.02)   # ~50 fps — smooth and clear for students

            # Agent picks action (no randomness — ε=0)
            action     = agent.select_action(state, training=False)
            next_state, reward, terminated, truncated, _ = env.step(action)
            done       = terminated or truncated
            state      = next_state
            score     += int(reward)

            if done:
                # Show the final (failed) frame briefly
                draw_cartpole_frame(ax, state, step, score, action,
                                    ep, num_episodes)
                ax.text(0, 1.6,
                        f'Episode {ep} ended — score: {score}',
                        ha='center', fontsize=13, color='#a78bfa',
                        fontfamily='monospace', fontweight='bold',
                        bbox=dict(boxstyle='round,pad=0.5',
                                  facecolor='#1e293b', edgecolor='#7c3aed'))
                fig.canvas.draw()
                fig.canvas.flush_events()
                plt.pause(1.2)
                break

        demo_scores.append(score)
        print(f"  Demo Episode {ep}: Score = {score} steps")

    agent.epsilon = saved_epsilon
    env.close()

    avg = np.mean(demo_scores)
    print(f"\n  Average demo score : {avg:.1f} steps")
    print(f"  (Maximum possible  : {MAX_STEPS} steps)")

    # Final summary frame
    ax.cla()
    ax.set_facecolor('#0f172a')
    ax.axis('off')
    summary = (
        f"Training Complete!\n\n"
        f"Demo scores:  {demo_scores}\n"
        f"Average:      {avg:.1f} / {MAX_STEPS} steps\n\n"
        f"The network learned to balance the pole\n"
        f"purely from reward signals — no physics knowledge!"
    )
    ax.text(0.5, 0.5, summary, transform=ax.transAxes,
            ha='center', va='center', fontsize=12, color='#e2e8f0',
            fontfamily='monospace',
            bbox=dict(boxstyle='round,pad=1.0', facecolor='#1e293b',
                      edgecolor='#3b82f6', linewidth=2))
    ax.set_title("CSE4020 — DQN CartPole Summary",
                 color='#3b82f6', fontsize=13, fontfamily='monospace')
    fig.canvas.draw()
    plt.pause(0.1)


# ─────────────────────────────────────────────────────────────────────────────
# SECTION 8 — WHAT EACH STATE VALUE MEANS (Teaching Helper)
# ─────────────────────────────────────────────────────────────────────────────

def explain_state(state):
    """Print a human-readable explanation of a CartPole state vector."""
    cart_pos, cart_vel, pole_angle, pole_vel = state
    print(f"  Cart position      : {cart_pos:+.4f}  (0 = center, ±4.8 = boundary)")
    print(f"  Cart velocity      : {cart_vel:+.4f}  (positive = moving right)")
    print(f"  Pole angle (rad)   : {pole_angle:+.4f}  (0 = upright, ±0.418 = fallen)")
    print(f"  Pole angular vel   : {pole_vel:+.4f}  (positive = falling right)")


# ─────────────────────────────────────────────────────────────────────────────
# SECTION 9 — ENTRY POINT
# ─────────────────────────────────────────────────────────────────────────────

if __name__ == "__main__":

    # Show what the untrained agent looks like first
    print("\n─── UNTRAINED AGENT (before training) ───")
    print("Observe how quickly the pole falls without training.\n")
    untrained_env   = gym.make(ENV_NAME)
    untrained_state, _ = untrained_env.reset()
    untrained_agent = DQNAgent(
        state_size  = untrained_env.observation_space.shape[0],
        action_size = untrained_env.action_space.n
    )
    ut_score = 0
    print("  Sample initial state:")
    explain_state(untrained_state)
    for _ in range(MAX_STEPS):
        a = untrained_agent.select_action(untrained_state)
        s, r, term, trunc, _ = untrained_env.step(a)
        ut_score += r
        untrained_state = s
        if term or trunc:
            break
    untrained_env.close()
    print(f"\n  Untrained agent survived: {ut_score:.0f} steps (random walk)")
    print(f"  (A random agent typically survives 8–15 steps)\n")

    # TRAIN
    agent, scores, plot = train()

    # DEMO the trained agent
    demo_agent(agent)

    print("\n" + "=" * 60)
    print("  SUMMARY FOR CLASS DISCUSSION")
    print("=" * 60)
    print(f"  Before training : ~{ut_score:.0f} steps  (random)")
    print(f"  After training  : ~{np.mean(scores[-20:]):.0f} steps  (learned!)")
    print(f"  Improvement     : {np.mean(scores[-20:])/max(ut_score,1):.0f}x better")
    print()
    print("  What the network learned:")
    print("  → If pole falling right: push cart right to compensate")
    print("  → If pole falling left : push cart left to compensate")
    print("  → Balance velocity AND position simultaneously")
    print("=" * 60)

    plt.ioff()
    plt.show()
