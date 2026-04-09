#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>

using namespace std;

// A single leaderboard entry
struct Player {
    string name;
    int score;
    int correctCount;
    string timestamp;
};

// Read the leaderboard from a file. Returns empty vector if file doesn't exist.
vector<Player> readLeaderboard(const string& filename);

// Write the leaderboard to a file (sorted by score, capped at 100 entries).
void writeLeaderboard(const string& filename, const vector<Player>& players);

// Insert a new player, sort, and return their 1-based rank.
int insertAndRank(vector<Player>& board, const Player& newPlayer);

#endif
