#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <string>
#include <vector>

using namespace std;

// A single quiz question
struct Question {
    string snippet;       // The C++ code to display
    string answer;        // The expected output
    string explanation;   // Why this is the answer
    int difficulty;       // 1 = easy, 2 = medium, 3 = hard
};

// Returns the full bank of hardcoded questions
vector<Question> loadQuestionBank();

// Shuffle and pick 'count' questions, filtered by difficulty
// difficulty: 1=easy only, 2=mixed, 3=hard only
vector<int> pickQuestionIndices(int bankSize, int count);

#endif
