#include "leaderboard.h"
#include <fstream>
#include <sstream>
#include <algorithm>

vector<Player> readLeaderboard(const string& filename) {
    vector<Player> players;
    ifstream file(filename);

    if (!file.is_open()) {
        return players;  // File doesn't exist yet, return empty
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        // Parse: Name,Score,Correct,Timestamp
        stringstream ss(line);
        Player p;
        string scoreStr, correctStr;

        if (getline(ss, p.name, ',') &&
            getline(ss, scoreStr, ',') &&
            getline(ss, correctStr, ',') &&
            getline(ss, p.timestamp)) {

            p.score = atoi(scoreStr.c_str());
            p.correctCount = atoi(correctStr.c_str());
            players.push_back(p);
        }
    }

    file.close();
    return players;
}

// Helper for sorting: higher scores come first
bool compareByScore(const Player& a, const Player& b) {
    return a.score > b.score;
}

void writeLeaderboard(const string& filename, const vector<Player>& players) {
    // Sort a copy
    vector<Player> sorted = players;
    sort(sorted.begin(), sorted.end(), compareByScore);

    // Cap at 100 entries
    int limit = 100;
    if ((int)sorted.size() > limit) {
        sorted.resize(limit);
    }

    ofstream file(filename);
    for (int i = 0; i < (int)sorted.size(); i++) {
        file << sorted[i].name << ","
             << sorted[i].score << ","
             << sorted[i].correctCount << ","
             << sorted[i].timestamp << "\n";
    }
    file.close();
}

int insertAndRank(vector<Player>& board, const Player& newPlayer) {
    board.push_back(newPlayer);
    sort(board.begin(), board.end(), compareByScore);

    // Cap at 100
    if ((int)board.size() > 100) {
        board.resize(100);
    }

    // Find the player's rank (1-based)
    for (int i = 0; i < (int)board.size(); i++) {
        if (board[i].name == newPlayer.name &&
            board[i].score == newPlayer.score &&
            board[i].timestamp == newPlayer.timestamp) {
            return i + 1;
        }
    }

    return (int)board.size();  // Fallback
}
