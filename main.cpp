// ============================================================
// Guess the Output - C++ Code Quiz Arcade
// A web-based quiz game for convention booths
//
// Uses cpp-httplib for the HTTP server.
// All game logic is plain C++. The frontend is pure HTML + CSS.
// ============================================================

#include "httplib.h"
#include "questions.h"
#include "leaderboard.h"
#include "pages.h"
#include "utils.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <mutex>

using namespace std;

// File where scores are saved
const string LEADERBOARD_FILE = "leaderboard.txt";

// Total questions per round
const int QUESTIONS_PER_ROUND = 5;

// Base points for a correct answer
const int BASE_POINTS = 20;

// Mutex to protect leaderboard file from simultaneous writes
mutex leaderboardMutex;

// Global question bank (loaded once at startup)
vector<Question> questionBank;

int main() {
    // Seed random number generator
    srand(time(0));

    // Load question bank
    questionBank = loadQuestionBank();
    cout << "Loaded " << questionBank.size() << " questions." << endl;

    // Create the web server
    httplib::Server server;

    // ----------------------------------------------------------
    // GET / - Welcome page
    // ----------------------------------------------------------
    server.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content(welcomePage(), "text/html");
    });

    // ----------------------------------------------------------
    // POST /start - Begin a new game round
    // ----------------------------------------------------------
    server.Post("/start", [](const httplib::Request& req, httplib::Response& res) {
        string name = trim(sanitizeName(getFormValue(req.body, "name")));

        if (name.empty()) {
            // Redirect back to welcome if name is empty
            res.set_redirect("/");
            return;
        }

        // Pick random question indices for this round
        vector<int> indices = pickQuestionIndices(questionBank.size(), QUESTIONS_PER_ROUND);

        // Encode indices as comma-separated string
        string indicesStr = "";
        for (int i = 0; i < (int)indices.size(); i++) {
            if (i > 0) indicesStr += ",";
            indicesStr += to_string(indices[i]);
        }

        // Show the first question
        int currentIndex = 0;
        int qIdx = indices[currentIndex];
        Question q = questionBank[qIdx];

        string html = questionPage(name, 1, QUESTIONS_PER_ROUND, q,
                                   indicesStr, currentIndex, 0, 0);
        res.set_content(html, "text/html");
    });

    // ----------------------------------------------------------
    // POST /answer - Check the player's answer
    // ----------------------------------------------------------
    server.Post("/answer", [](const httplib::Request& req, httplib::Response& res) {
        string name = getFormValue(req.body, "name");
        string answer = getFormValue(req.body, "answer");
        string indicesStr = getFormValue(req.body, "indices");
        int currentIndex = atoi(getFormValue(req.body, "current").c_str());
        int score = atoi(getFormValue(req.body, "score").c_str());
        int correctCount = atoi(getFormValue(req.body, "correct").c_str());

        // Parse the indices
        vector<int> indices;
        stringstream ss(indicesStr);
        string token;
        while (getline(ss, token, ',')) {
            indices.push_back(atoi(token.c_str()));
        }

        // Get the current question
        int qIdx = indices[currentIndex];
        Question q = questionBank[qIdx];

        // Check the answer
        bool isCorrect = answersMatch(answer, q.answer);
        int pointsEarned = 0;
        if (isCorrect) {
            pointsEarned = BASE_POINTS;
            correctCount++;
        }
        score += pointsEarned;

        int questionNum = currentIndex + 1;
        int nextIndex = currentIndex + 1;

        string html = feedbackPage(isCorrect, answer, q, pointsEarned, score,
                                   correctCount, questionNum, QUESTIONS_PER_ROUND,
                                   name, indicesStr, nextIndex);
        res.set_content(html, "text/html");
    });

    // ----------------------------------------------------------
    // POST /next - Show the next question
    // ----------------------------------------------------------
    server.Post("/next", [](const httplib::Request& req, httplib::Response& res) {
        string name = getFormValue(req.body, "name");
        string indicesStr = getFormValue(req.body, "indices");
        int currentIndex = atoi(getFormValue(req.body, "current").c_str());
        int score = atoi(getFormValue(req.body, "score").c_str());
        int correctCount = atoi(getFormValue(req.body, "correct").c_str());

        // Parse indices
        vector<int> indices;
        stringstream ss(indicesStr);
        string token;
        while (getline(ss, token, ',')) {
            indices.push_back(atoi(token.c_str()));
        }

        // Show the next question
        int qIdx = indices[currentIndex];
        Question q = questionBank[qIdx];
        int questionNum = currentIndex + 1;

        string html = questionPage(name, questionNum, QUESTIONS_PER_ROUND, q,
                                   indicesStr, currentIndex, score, correctCount);
        res.set_content(html, "text/html");
    });

    // ----------------------------------------------------------
    // POST /results - Show final score
    // ----------------------------------------------------------
    server.Post("/results", [](const httplib::Request& req, httplib::Response& res) {
        string name = getFormValue(req.body, "name");
        int score = atoi(getFormValue(req.body, "score").c_str());
        int correctCount = atoi(getFormValue(req.body, "correct").c_str());

        string html = resultsPage(name, score, correctCount, QUESTIONS_PER_ROUND);
        res.set_content(html, "text/html");
    });

    // ----------------------------------------------------------
    // POST /save - Save score and show leaderboard
    // ----------------------------------------------------------
    server.Post("/save", [](const httplib::Request& req, httplib::Response& res) {
        string name = getFormValue(req.body, "name");
        int score = atoi(getFormValue(req.body, "score").c_str());
        int correctCount = atoi(getFormValue(req.body, "correct").c_str());

        // Create the player entry
        Player p;
        p.name = name;
        p.score = score;
        p.correctCount = correctCount;
        p.timestamp = getCurrentTimestamp();

        // Thread-safe leaderboard update
        leaderboardMutex.lock();
        vector<Player> board = readLeaderboard(LEADERBOARD_FILE);
        int rank = insertAndRank(board, p);
        writeLeaderboard(LEADERBOARD_FILE, board);
        leaderboardMutex.unlock();

        string html = leaderboardPage(board, name, rank);
        res.set_content(html, "text/html");
    });

    // ----------------------------------------------------------
    // GET /leaderboard - View leaderboard without playing
    // ----------------------------------------------------------
    server.Get("/leaderboard", [](const httplib::Request& req, httplib::Response& res) {
        leaderboardMutex.lock();
        vector<Player> board = readLeaderboard(LEADERBOARD_FILE);
        leaderboardMutex.unlock();

        string html = leaderboardPage(board, "", 0);
        res.set_content(html, "text/html");
    });

    // ----------------------------------------------------------
    // Start the server
    // ----------------------------------------------------------
    int port = 8080;
    cout << "============================================" << endl;
    cout << "  Guess the Output - Server Running!" << endl;
    cout << "  Open your browser to: http://localhost:" << port << endl;
    cout << "============================================" << endl;

    server.listen("0.0.0.0", port);

    return 0;
}
