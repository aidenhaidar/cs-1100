#include "pages.h"
#include <sstream>

// ============================================================
// Shared CSS styles for all pages
// ============================================================

string getStyles() {
    return R"(
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: #0f0f23;
            color: #e0e0e0;
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
            padding: 20px;
        }
        .container {
            background: #1a1a2e;
            border-radius: 16px;
            padding: 40px;
            max-width: 700px;
            width: 90%;
            box-shadow: 0 8px 32px rgba(0, 0, 0, 0.4);
        }
        .dashboard-container {
            background: none;
            max-width: 1100px;
            width: 95%;
            padding: 0;
            box-shadow: none;
        }
        .dashboard-header {
            text-align: center;
            margin-bottom: 32px;
        }
        .dashboard-grid {
            display: flex;
            gap: 24px;
            align-items: flex-start;
        }
        .dashboard-left {
            flex: 1;
            background: #1a1a2e;
            border-radius: 16px;
            padding: 36px;
            box-shadow: 0 8px 32px rgba(0, 0, 0, 0.4);
        }
        .dashboard-right {
            flex: 1;
            background: #1a1a2e;
            border-radius: 16px;
            overflow: hidden;
            box-shadow: 0 8px 32px rgba(0, 0, 0, 0.4);
            min-height: 480px;
        }
        .dashboard-right iframe {
            width: 100%;
            height: 480px;
            border: none;
        }
        .live-badge {
            display: inline-block;
            background: #1a4731;
            color: #4ade80;
            padding: 4px 12px;
            border-radius: 12px;
            font-size: 0.8em;
            font-weight: bold;
            margin-left: 8px;
            animation: pulse 2s infinite;
        }
        @keyframes pulse {
            0%, 100% { opacity: 1; }
            50% { opacity: 0.5; }
        }
        h1 {
            color: #00d4ff;
            font-size: 2.2em;
            text-align: center;
            margin-bottom: 8px;
        }
        h2 {
            color: #00d4ff;
            font-size: 1.5em;
            margin-bottom: 16px;
        }
        .subtitle {
            color: #888;
            text-align: center;
            font-size: 1.1em;
            margin-bottom: 32px;
        }
        .instructions {
            background: #16213e;
            border-left: 4px solid #00d4ff;
            padding: 16px 20px;
            border-radius: 8px;
            margin-bottom: 28px;
            line-height: 1.6;
        }
        input[type="text"] {
            width: 100%;
            padding: 14px 18px;
            font-size: 1.1em;
            border: 2px solid #333;
            border-radius: 8px;
            background: #0f0f23;
            color: #fff;
            margin-bottom: 16px;
            outline: none;
        }
        input[type="text"]:focus {
            border-color: #00d4ff;
        }
        .btn {
            display: inline-block;
            padding: 14px 32px;
            font-size: 1.1em;
            font-weight: bold;
            color: #fff;
            background: #00d4ff;
            border: none;
            border-radius: 8px;
            cursor: pointer;
            text-decoration: none;
            transition: background 0.2s;
        }
        .btn:hover { background: #00b8d9; }
        .btn-center { display: block; width: 100%; text-align: center; }
        .btn-large {
            padding: 18px 40px;
            font-size: 1.3em;
            margin-top: 8px;
        }
        .code-box {
            background: #0d1117;
            border: 1px solid #333;
            border-radius: 8px;
            padding: 20px;
            font-family: 'Courier New', monospace;
            font-size: 1.05em;
            line-height: 1.6;
            white-space: pre;
            overflow-x: auto;
            margin-bottom: 24px;
            color: #c9d1d9;
        }
        .badge {
            display: inline-block;
            padding: 4px 12px;
            border-radius: 12px;
            font-size: 0.85em;
            font-weight: bold;
            margin-bottom: 16px;
        }
        .badge-easy { background: #1a4731; color: #4ade80; }
        .badge-medium { background: #4a3728; color: #fbbf24; }
        .badge-hard { background: #4a2028; color: #f87171; }
        .progress {
            color: #888;
            text-align: right;
            font-size: 0.9em;
            margin-bottom: 8px;
        }
        .score-display {
            color: #00d4ff;
            text-align: right;
            font-size: 0.9em;
            margin-bottom: 16px;
        }
        .correct-box {
            background: #1a4731;
            border-left: 4px solid #4ade80;
            padding: 16px 20px;
            border-radius: 8px;
            margin-bottom: 24px;
        }
        .correct-box h3 { color: #4ade80; margin-bottom: 8px; }
        .wrong-box {
            background: #4a2028;
            border-left: 4px solid #f87171;
            padding: 16px 20px;
            border-radius: 8px;
            margin-bottom: 24px;
        }
        .wrong-box h3 { color: #f87171; margin-bottom: 8px; }
        .explanation { color: #aaa; font-size: 0.95em; margin-top: 8px; }
        .result-card {
            text-align: center;
            padding: 20px;
        }
        .big-score {
            font-size: 4em;
            font-weight: bold;
            color: #00d4ff;
            margin: 16px 0;
        }
        .stat-row {
            display: flex;
            justify-content: center;
            gap: 40px;
            margin: 20px 0;
        }
        .stat { text-align: center; }
        .stat-value { font-size: 1.8em; font-weight: bold; color: #fff; }
        .stat-label { color: #888; font-size: 0.9em; }
        table {
            width: 100%;
            border-collapse: collapse;
            margin-bottom: 24px;
        }
        th {
            text-align: left;
            padding: 10px 12px;
            border-bottom: 2px solid #333;
            color: #00d4ff;
            font-size: 0.9em;
        }
        td {
            padding: 10px 12px;
            border-bottom: 1px solid #222;
        }
        .highlight-row {
            background: #16213e;
            font-weight: bold;
        }
        .highlight-row td { color: #00d4ff; }
        .rank-1 td:first-child { color: #ffd700; }
        .rank-2 td:first-child { color: #c0c0c0; }
        .rank-3 td:first-child { color: #cd7f32; }
        a { color: #00d4ff; text-decoration: none; }
        a:hover { text-decoration: underline; }
        .nav-links {
            text-align: center;
            margin-top: 20px;
        }
        .nav-links a {
            margin: 0 12px;
        }
        @media (max-width: 768px) {
            .dashboard-grid {
                flex-direction: column;
            }
            .dashboard-right {
                min-height: 400px;
            }
            .dashboard-right iframe {
                height: 400px;
            }
        }
    )";
}

// ============================================================
// Helper to wrap content in an HTML page shell
// ============================================================

string htmlShell(const string& title, const string& body) {
    string html = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
    html += "  <meta charset=\"UTF-8\">\n";
    html += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    html += "  <title>" + title + "</title>\n";
    html += "  <style>" + getStyles() + "</style>\n";
    html += "</head>\n<body>\n";
    html += "  <div class=\"container\">\n" + body + "\n  </div>\n";
    html += "</body>\n</html>";
    return html;
}

// ============================================================
// Dashboard Page (two-column: start quiz + live leaderboard)
// ============================================================

string dashboardPage() {
    string html = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
    html += "  <meta charset=\"UTF-8\">\n";
    html += "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    html += "  <title>Guess the Output - Dashboard</title>\n";
    html += "  <style>" + getStyles() + "</style>\n";
    html += "</head>\n<body>\n";
    html += "  <div class=\"container dashboard-container\">\n";

    // Header
    html += "    <div class=\"dashboard-header\">\n";
    html += "      <h1>GUESS THE OUTPUT</h1>\n";
    html += "      <p class=\"subtitle\">C++ Code Quiz Arcade</p>\n";
    html += "    </div>\n";

    // Two-column grid
    html += "    <div class=\"dashboard-grid\">\n";

    // Left column: start quiz
    html += "      <div class=\"dashboard-left\">\n";
    html += "        <h2>Ready to play?</h2>\n";
    html += "        <div class=\"instructions\">\n";
    html += "          Read short C++ code snippets and type what you think they output.<br><br>\n";
    html += "          <strong>23 questions</strong> &mdash; all randomized, no repeats.<br>\n";
    html += "          Each correct answer earns <strong>20 points</strong>.<br>\n";
    html += "          Can you top the leaderboard?\n";
    html += "        </div>\n";
    html += "        <form method=\"POST\" action=\"/start\">\n";
    html += "          <label style=\"color:#aaa; font-size:0.9em;\">Enter your name:</label>\n";
    html += "          <input type=\"text\" name=\"name\" placeholder=\"Your name\" required autofocus>\n";
    html += "          <button type=\"submit\" class=\"btn btn-center btn-large\">Start Quiz</button>\n";
    html += "        </form>\n";
    html += "      </div>\n";

    // Right column: live leaderboard iframe
    html += "      <div class=\"dashboard-right\">\n";
    html += "        <iframe src=\"/leaderboard-widget\"></iframe>\n";
    html += "      </div>\n";

    html += "    </div>\n";  // end grid
    html += "  </div>\n";    // end container
    html += "</body>\n</html>";

    return html;
}

// ============================================================
// Leaderboard Widget (for iframe, auto-refreshes every 5 sec)
// ============================================================

string leaderboardWidget(const vector<Player>& board, int totalQuestions) {
    string html = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
    html += "  <meta charset=\"UTF-8\">\n";
    html += "  <meta http-equiv=\"refresh\" content=\"5\">\n";
    html += "  <style>\n";
    html += "    * { margin: 0; padding: 0; box-sizing: border-box; }\n";
    html += "    body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: #1a1a2e; color: #e0e0e0; padding: 24px; }\n";
    html += "    .widget-header { display: flex; align-items: center; margin-bottom: 20px; }\n";
    html += "    .widget-header h2 { color: #00d4ff; font-size: 1.3em; }\n";
    html += "    .live-dot { width: 8px; height: 8px; background: #4ade80; border-radius: 50%; margin-left: 10px; animation: pulse 2s infinite; }\n";
    html += "    .live-label { color: #4ade80; font-size: 0.8em; font-weight: bold; margin-left: 6px; }\n";
    html += "    @keyframes pulse { 0%,100%{opacity:1;} 50%{opacity:0.4;} }\n";
    html += "    table { width: 100%; border-collapse: collapse; }\n";
    html += "    th { text-align: left; padding: 8px 10px; border-bottom: 2px solid #333; color: #00d4ff; font-size: 0.85em; }\n";
    html += "    td { padding: 8px 10px; border-bottom: 1px solid #222; }\n";
    html += "    .rank-1 td:first-child { color: #ffd700; font-weight: bold; }\n";
    html += "    .rank-2 td:first-child { color: #c0c0c0; font-weight: bold; }\n";
    html += "    .rank-3 td:first-child { color: #cd7f32; font-weight: bold; }\n";
    html += "    .empty-msg { color: #888; text-align: center; padding: 60px 0; }\n";
    html += "  </style>\n";
    html += "</head>\n<body>\n";

    // Header with live indicator
    html += "  <div class=\"widget-header\">\n";
    html += "    <h2>Leaderboard</h2>\n";
    html += "    <div class=\"live-dot\"></div>\n";
    html += "    <span class=\"live-label\">LIVE</span>\n";
    html += "  </div>\n";

    if (board.empty()) {
        html += "  <p class=\"empty-msg\">No scores yet.<br>Be the first to play!</p>\n";
    } else {
        html += "  <table>\n";
        html += "    <tr><th>Rank</th><th>Name</th><th>Score</th><th>Correct</th></tr>\n";

        int showCount = 10;
        if ((int)board.size() < showCount) {
            showCount = board.size();
        }

        for (int i = 0; i < showCount; i++) {
            string rowClass = "";
            if (i == 0) rowClass = " class=\"rank-1\"";
            if (i == 1) rowClass = " class=\"rank-2\"";
            if (i == 2) rowClass = " class=\"rank-3\"";

            html += "    <tr" + rowClass + ">";
            html += "<td>#" + to_string(i + 1) + "</td>";
            html += "<td>" + board[i].name + "</td>";
            html += "<td>" + to_string(board[i].score) + "</td>";
            html += "<td>" + to_string(board[i].correctCount) + "/" + to_string(totalQuestions) + "</td>";
            html += "</tr>\n";
        }

        html += "  </table>\n";
    }

    html += "</body>\n</html>";
    return html;
}

// ============================================================
// Question Page
// ============================================================

string questionPage(const string& playerName, int questionNum, int totalQuestions,
                    const Question& q, const string& hiddenIndices,
                    int currentIndex, int score, int correctCount) {

    string diffLabel, diffClass;
    if (q.difficulty == 1) {
        diffLabel = "Easy";
        diffClass = "badge-easy";
    } else if (q.difficulty == 2) {
        diffLabel = "Medium";
        diffClass = "badge-medium";
    } else {
        diffLabel = "Hard";
        diffClass = "badge-hard";
    }

    string body = "";
    body += "<div class=\"progress\">Question " + to_string(questionNum) + " of " + to_string(totalQuestions) + "</div>\n";
    body += "<div class=\"score-display\">Score: " + to_string(score) + " pts</div>\n";
    body += "<span class=\"badge " + diffClass + "\">" + diffLabel + "</span>\n";
    body += "<h2>What does this code output?</h2>\n";
    body += "<div class=\"code-box\">" + q.snippet + "</div>\n";
    body += "<form method=\"POST\" action=\"/answer\">\n";
    body += "  <input type=\"hidden\" name=\"name\" value=\"" + playerName + "\">\n";
    body += "  <input type=\"hidden\" name=\"indices\" value=\"" + hiddenIndices + "\">\n";
    body += "  <input type=\"hidden\" name=\"current\" value=\"" + to_string(currentIndex) + "\">\n";
    body += "  <input type=\"hidden\" name=\"score\" value=\"" + to_string(score) + "\">\n";
    body += "  <input type=\"hidden\" name=\"correct\" value=\"" + to_string(correctCount) + "\">\n";
    body += "  <input type=\"text\" name=\"answer\" placeholder=\"Type your answer...\" required autofocus autocomplete=\"off\">\n";
    body += "  <button type=\"submit\" class=\"btn btn-center\">Submit Answer</button>\n";
    body += "</form>\n";

    return htmlShell("Question " + to_string(questionNum) + " - Guess the Output", body);
}

// ============================================================
// Feedback Page
// ============================================================

string feedbackPage(bool isCorrect, const string& playerAnswer,
                    const Question& q, int pointsEarned, int totalScore,
                    int correctCount, int questionNum, int totalQuestions,
                    const string& playerName, const string& hiddenIndices,
                    int nextIndex) {

    string body = "";
    body += "<div class=\"progress\">Question " + to_string(questionNum) + " of " + to_string(totalQuestions) + "</div>\n";
    body += "<div class=\"score-display\">Score: " + to_string(totalScore) + " pts</div>\n";

    if (isCorrect) {
        body += "<div class=\"correct-box\">\n";
        body += "  <h3>Correct! +" + to_string(pointsEarned) + " pts</h3>\n";
        body += "  <p>Nice work! The answer is: <strong>" + q.answer + "</strong></p>\n";
        body += "</div>\n";
    } else {
        body += "<div class=\"wrong-box\">\n";
        body += "  <h3>Not quite!</h3>\n";
        body += "  <p>You answered: <strong>" + playerAnswer + "</strong></p>\n";
        body += "  <p>The correct answer is: <strong>" + q.answer + "</strong></p>\n";
        body += "  <p class=\"explanation\">" + q.explanation + "</p>\n";
        body += "</div>\n";
    }

    // Button to continue
    string nextAction = (questionNum >= totalQuestions) ? "/results" : "/next";
    string nextLabel = (questionNum >= totalQuestions) ? "See Results" : "Next Question";

    body += "<form method=\"POST\" action=\"" + nextAction + "\">\n";
    body += "  <input type=\"hidden\" name=\"name\" value=\"" + playerName + "\">\n";
    body += "  <input type=\"hidden\" name=\"indices\" value=\"" + hiddenIndices + "\">\n";
    body += "  <input type=\"hidden\" name=\"current\" value=\"" + to_string(nextIndex) + "\">\n";
    body += "  <input type=\"hidden\" name=\"score\" value=\"" + to_string(totalScore) + "\">\n";
    body += "  <input type=\"hidden\" name=\"correct\" value=\"" + to_string(correctCount) + "\">\n";
    body += "  <button type=\"submit\" class=\"btn btn-center\">" + nextLabel + "</button>\n";
    body += "</form>\n";

    return htmlShell("Answer - Guess the Output", body);
}

// ============================================================
// Results Page
// ============================================================

string resultsPage(const string& playerName, int score, int correctCount,
                   int totalQuestions) {

    string body = "";
    body += "<div class=\"result-card\">\n";
    body += "  <h1>Round Complete!</h1>\n";
    body += "  <p class=\"subtitle\">Great job, " + playerName + "!</p>\n";
    body += "  <div class=\"big-score\">" + to_string(score) + "</div>\n";
    body += "  <p style=\"color:#888; margin-bottom:20px;\">points</p>\n";
    body += "  <div class=\"stat-row\">\n";
    body += "    <div class=\"stat\">\n";
    body += "      <div class=\"stat-value\">" + to_string(correctCount) + "/" + to_string(totalQuestions) + "</div>\n";
    body += "      <div class=\"stat-label\">Correct</div>\n";
    body += "    </div>\n";
    body += "  </div>\n";
    body += "</div>\n";

    body += "<form method=\"POST\" action=\"/save\">\n";
    body += "  <input type=\"hidden\" name=\"name\" value=\"" + playerName + "\">\n";
    body += "  <input type=\"hidden\" name=\"score\" value=\"" + to_string(score) + "\">\n";
    body += "  <input type=\"hidden\" name=\"correct\" value=\"" + to_string(correctCount) + "\">\n";
    body += "  <button type=\"submit\" class=\"btn btn-center\">See Leaderboard</button>\n";
    body += "</form>\n";

    return htmlShell("Results - Guess the Output", body);
}

// ============================================================
// Leaderboard Page (standalone, after completing a round)
// ============================================================

string leaderboardPage(const vector<Player>& board, const string& currentPlayer,
                       int playerRank, int totalQuestions) {

    string body = "";
    body += "<h1>Leaderboard</h1>\n";
    body += "<p class=\"subtitle\">Top 10 Players</p>\n";

    if (board.empty()) {
        body += "<p style=\"text-align:center; color:#888; padding:40px 0;\">No scores yet. Be the first to play!</p>\n";
    } else {
        body += "<table>\n";
        body += "  <tr><th>Rank</th><th>Name</th><th>Score</th><th>Correct</th></tr>\n";

        int showCount = 10;
        if ((int)board.size() < showCount) {
            showCount = board.size();
        }

        for (int i = 0; i < showCount; i++) {
            string rowClass = "";

            // Highlight the current player's row
            if (!currentPlayer.empty() && (i + 1) == playerRank) {
                rowClass = " class=\"highlight-row\"";
            }

            // Gold/silver/bronze styling
            if (i == 0) rowClass = " class=\"rank-1" + string((i + 1 == playerRank && !currentPlayer.empty()) ? " highlight-row" : "") + "\"";
            if (i == 1) rowClass = " class=\"rank-2" + string((i + 1 == playerRank && !currentPlayer.empty()) ? " highlight-row" : "") + "\"";
            if (i == 2) rowClass = " class=\"rank-3" + string((i + 1 == playerRank && !currentPlayer.empty()) ? " highlight-row" : "") + "\"";

            string marker = "";
            if (!currentPlayer.empty() && (i + 1) == playerRank) {
                marker = " &#9668;";  // Left-pointing triangle
            }

            body += "  <tr" + rowClass + ">";
            body += "<td>#" + to_string(i + 1) + "</td>";
            body += "<td>" + board[i].name + marker + "</td>";
            body += "<td>" + to_string(board[i].score) + "</td>";
            body += "<td>" + to_string(board[i].correctCount) + "/" + to_string(totalQuestions) + "</td>";
            body += "</tr>\n";
        }

        body += "</table>\n";
    }

    body += "<div class=\"nav-links\">\n";
    body += "  <a href=\"/\" class=\"btn\">Back to Dashboard</a>\n";
    body += "</div>\n";

    return htmlShell("Leaderboard - Guess the Output", body);
}
