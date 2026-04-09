#ifndef PAGES_H
#define PAGES_H

#include <string>
#include <vector>
#include "questions.h"
#include "leaderboard.h"

using namespace std;

// Returns the shared CSS styles used by all pages
string getStyles();

// Dashboard page with start quiz form + live leaderboard
string dashboardPage();

// Leaderboard widget for embedding in iframe (auto-refreshes)
string leaderboardWidget(const vector<Player>& board, int totalQuestions);

// Question page showing a code snippet and answer form
// hiddenState is passed through forms to track game progress
string questionPage(const string& playerName, int questionNum, int totalQuestions,
                    const Question& q, const string& hiddenIndices,
                    int currentIndex, int score, int correctCount);

// Feedback page after answering (correct or wrong)
string feedbackPage(bool isCorrect, const string& playerAnswer,
                    const Question& q, int pointsEarned, int totalScore,
                    int correctCount, int questionNum, int totalQuestions,
                    const string& playerName, const string& hiddenIndices,
                    int nextIndex);

// Results page after all questions
string resultsPage(const string& playerName, int score, int correctCount,
                   int totalQuestions);

// Leaderboard page showing top 10
string leaderboardPage(const vector<Player>& board, const string& currentPlayer,
                       int playerRank, int totalQuestions);

#endif
