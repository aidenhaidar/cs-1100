#include "questions.h"
#include <cstdlib>
#include <algorithm>

vector<Question> loadQuestionBank() {
    vector<Question> bank;
    Question q;

    // ===== EASY (difficulty 1) =====

    q.snippet = "int a = 5;\nint b = 2;\ncout << a + b;";
    q.answer = "7";
    q.explanation = "5 + 2 = 7, simple addition.";
    q.difficulty = 1;
    bank.push_back(q);

    q.snippet = "int x = 10;\ncout << x;";
    q.answer = "10";
    q.explanation = "Just prints the value of x.";
    q.difficulty = 1;
    bank.push_back(q);

    q.snippet = "string name = \"Alice\";\ncout << \"Hi \" << name;";
    q.answer = "Hi Alice";
    q.explanation = "String concatenation with cout.";
    q.difficulty = 1;
    bank.push_back(q);

    q.snippet = "int a = 8;\nint b = 3;\ncout << a - b;";
    q.answer = "5";
    q.explanation = "8 - 3 = 5, simple subtraction.";
    q.difficulty = 1;
    bank.push_back(q);

    q.snippet = "cout << \"Hello\" << \" \" << \"World\";";
    q.answer = "Hello World";
    q.explanation = "Three strings printed back to back.";
    q.difficulty = 1;
    bank.push_back(q);

    q.snippet = "int x = 4;\nx = x * 2;\ncout << x;";
    q.answer = "8";
    q.explanation = "x starts at 4, then gets multiplied by 2.";
    q.difficulty = 1;
    bank.push_back(q);

    q.snippet = "bool flag = true;\ncout << flag;";
    q.answer = "1";
    q.explanation = "true prints as 1 in C++.";
    q.difficulty = 1;
    bank.push_back(q);

    // ===== MEDIUM (difficulty 2) =====

    q.snippet = "int x = 10;\nint y = 3;\ncout << x / y;";
    q.answer = "3";
    q.explanation = "Integer division: 10 / 3 = 3 (truncated).";
    q.difficulty = 2;
    bank.push_back(q);

    q.snippet = "for (int i = 0; i < 3; i++) {\n    cout << i << \" \";\n}";
    q.answer = "0 1 2 ";
    q.explanation = "Loop runs for i = 0, 1, 2. Each prints with a trailing space.";
    q.difficulty = 2;
    bank.push_back(q);

    q.snippet = "int x = 7;\nif (x > 10) {\n    cout << \"big\";\n} else {\n    cout << \"small\";\n}";
    q.answer = "small";
    q.explanation = "7 is not greater than 10, so the else branch runs.";
    q.difficulty = 2;
    bank.push_back(q);

    q.snippet = "int x = 10;\nint y = 3;\ncout << x % y;";
    q.answer = "1";
    q.explanation = "Modulo: 10 % 3 = 1 (remainder).";
    q.difficulty = 2;
    bank.push_back(q);

    q.snippet = "int sum = 0;\nfor (int i = 1; i <= 4; i++) {\n    sum += i;\n}\ncout << sum;";
    q.answer = "10";
    q.explanation = "1 + 2 + 3 + 4 = 10.";
    q.difficulty = 2;
    bank.push_back(q);

    q.snippet = "int x = 5;\nif (x >= 5) {\n    cout << \"yes\";\n} else {\n    cout << \"no\";\n}";
    q.answer = "yes";
    q.explanation = "5 >= 5 is true, so 'yes' is printed.";
    q.difficulty = 2;
    bank.push_back(q);

    q.snippet = "int a = 2;\nint b = 3;\ncout << a * b + 1;";
    q.answer = "7";
    q.explanation = "Multiplication before addition: 2 * 3 = 6, then 6 + 1 = 7.";
    q.difficulty = 2;
    bank.push_back(q);

    q.snippet = "for (int i = 5; i > 0; i--) {\n    cout << i << \" \";\n}";
    q.answer = "5 4 3 2 1 ";
    q.explanation = "Counting down from 5 to 1 with a trailing space.";
    q.difficulty = 2;
    bank.push_back(q);

    q.snippet = "int x = 0;\nwhile (x < 3) {\n    x++;\n}\ncout << x;";
    q.answer = "3";
    q.explanation = "Loop increments x until it reaches 3, then prints 3.";
    q.difficulty = 2;
    bank.push_back(q);

    q.snippet = "string s = \"hello\";\ncout << s.size();";
    q.answer = "5";
    q.explanation = "The string 'hello' has 5 characters.";
    q.difficulty = 2;
    bank.push_back(q);

    // ===== HARD (difficulty 3) =====

    q.snippet = "int x = 5;\nif (x > 3 && ++x > 5) {\n    cout << x;\n} else {\n    cout << x;\n}";
    q.answer = "6";
    q.explanation = "++x increments x to 6 before comparing. 6 > 5 is true. Prints 6.";
    q.difficulty = 3;
    bank.push_back(q);

    q.snippet = "for (int i = 0; i < 3; i++) {\n    for (int j = 0; j < 2; j++) {\n        cout << \"*\";\n    }\n}";
    q.answer = "******";
    q.explanation = "Outer loop runs 3 times, inner 2 times each: 3 x 2 = 6 stars.";
    q.difficulty = 3;
    bank.push_back(q);

    q.snippet = "int arr[] = {10, 20, 30};\ncout << arr[0] + arr[2];";
    q.answer = "40";
    q.explanation = "arr[0] is 10 and arr[2] is 30. 10 + 30 = 40.";
    q.difficulty = 3;
    bank.push_back(q);

    q.snippet = "int x = 1;\nfor (int i = 0; i < 4; i++) {\n    x *= 2;\n}\ncout << x;";
    q.answer = "16";
    q.explanation = "x doubles 4 times: 1 -> 2 -> 4 -> 8 -> 16.";
    q.difficulty = 3;
    bank.push_back(q);

    q.snippet = "int a = 10;\nint b = a++;\ncout << a << \" \" << b;";
    q.answer = "11 10";
    q.explanation = "Post-increment: b gets old value (10), then a becomes 11.";
    q.difficulty = 3;
    bank.push_back(q);

    q.snippet = "int x = 15;\ncout << (x > 10 ? \"big\" : \"small\");";
    q.answer = "big";
    q.explanation = "Ternary operator: 15 > 10 is true, so 'big' is printed.";
    q.difficulty = 3;
    bank.push_back(q);

    q.snippet = "int count = 0;\nfor (int i = 0; i < 5; i++) {\n    if (i % 2 == 0) {\n        count++;\n    }\n}\ncout << count;";
    q.answer = "3";
    q.explanation = "Even values of i: 0, 2, 4. That's 3 numbers.";
    q.difficulty = 3;
    bank.push_back(q);

    return bank;
}

vector<int> pickQuestionIndices(int bankSize, int count) {
    // Create a list of all indices
    vector<int> indices;
    for (int i = 0; i < bankSize; i++) {
        indices.push_back(i);
    }

    // Shuffle using Fisher-Yates
    for (int i = bankSize - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Take the first 'count' indices
    vector<int> picked;
    for (int i = 0; i < count && i < bankSize; i++) {
        picked.push_back(indices[i]);
    }

    return picked;
}
