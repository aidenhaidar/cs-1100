# Guess the Output — C++ Code Quiz Arcade

A web-based C++ quiz game for convention booths. Players read short C++ code snippets, guess what they output, and compete on a live leaderboard.

## Tech Stack

- **Backend:** 100% C++ (HTTP server, game logic, HTML generation, file I/O)
- **Frontend:** Pure HTML + CSS (no JavaScript)
- **Library:** [cpp-httplib](https://github.com/yhirose/cpp-httplib) (single-header HTTP server)

## Build & Run

```bash
make
./guess_the_output
```

Then open your browser to **http://localhost:8080**

## How It Works

1. Player enters their name
2. 5 random C++ questions are presented one at a time
3. Player types what they think the code outputs
4. Immediate feedback (correct/wrong + explanation)
5. Score saved to a persistent leaderboard

## Scoring

- Correct answer: **20 points**
- Wrong answer: **0 points** (no penalty)
- Max per round: **100 points**

## Project Structure

| File | Purpose |
|---|---|
| `main.cpp` | Server setup, HTTP routes |
| `pages.h/cpp` | HTML page generation |
| `questions.h/cpp` | Question bank (23 questions, 3 difficulty tiers) |
| `leaderboard.h/cpp` | Persistent score file I/O |
| `utils.h/cpp` | String helpers, URL decoding, form parsing |
| `httplib.h` | HTTP server library (third-party, header-only) |

## Booth Setup

1. Build the project on the booth machine
2. Run `./guess_the_output`
3. Open a browser in fullscreen/kiosk mode to `http://localhost:8080`
4. Players rotate through — the leaderboard persists across rounds
5. To reset scores: delete `leaderboard.txt` and restart

## Requirements

- g++ with C++11 support
- Linux or macOS (uses POSIX sockets)
