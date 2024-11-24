#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void drawHangman(int wrongGuesses) { // Рисует виселицу в зависимости от количества неверных ответов
    string hangman[8] = {
        "  _______    ",
        " |       |   ",
        " |           ",
        " |           ",
        " |           ",
        " |           ",
        " |           ",
        " |__________ "
    };

    if (wrongGuesses >= 1) hangman[2] = " |       O   ";        // Голова
    if (wrongGuesses >= 2) hangman[3] = " |       |  ";       // Шея
    if (wrongGuesses >= 3) hangman[4] = " |      /|\\  ";       // Туловище и руки
    if (wrongGuesses >= 4) hangman[5] = " |       |  ";       // Живот
    if (wrongGuesses >= 5) hangman[6] = " |      / \\  ";       // Ноги

    for (int i = 0; i < 8; i++) { // Отображаем виселицу
        cout << hangman[i] << endl;
    }
}

void chooseWordFromFile(vector<string>& words) {
    ifstream file("words.txt");
    string word;
    while (getline(file, word, ',')) {
        words.push_back(word);
    }
    file.close();
}

int main() {

    setlocale(LC_ALL, "Russian"); // вкл русского языка

    srand(time(0));

    vector<string> words;
    chooseWordFromFile(words);

    string word = words[rand() % words.size()]; // Выбираем случайное слово
    string guessedWord(word.length(), '_');
    int lives = 6;
    vector<char> wrongGuesses;
    bool wordGuessed = false;

    cout << "Добро пожаловать в игру 'Виселица'!" << endl;
    cout << "У вас " << lives << " жизней." << endl;

    while (lives > 0 && !wordGuessed) {
        cout << "\nТекущее слово: " << guessedWord << endl;
        cout << "Неверные буквы: ";
        for (char c : wrongGuesses) {
            cout << c << " ";
        }
        cout << endl;

        drawHangman(6 - lives); // Рисуем виселицу

        char guess;
        cout << "Введите букву: ";
        cin >> guess;

        if (find(wrongGuesses.begin(), wrongGuesses.end(), guess) != wrongGuesses.end() || // Проверка на уже угаданную букву
            find(guessedWord.begin(), guessedWord.end(), guess) != guessedWord.end()) {
            cout << "Вы уже вводили эту букву!" << endl;
            continue;
        }

        bool correctGuess = false; // Проверка, есть ли буква в слове
        for (int i = 0; i < word.length(); i++) {
            if (word[i] == guess) {
                guessedWord[i] = guess;
                correctGuess = true;
            }
        }

        if (correctGuess) {
            cout << "Правильная буква!" << endl;
        }
        else {
            lives--;
            wrongGuesses.push_back(guess);
            cout << "Неверная буква!" << endl;
        }

        if (guessedWord == word) { // Проверка, угадано ли слово
            wordGuessed = true;
        }
    }

    if (wordGuessed) {
        cout << "\nПоздравляем! Вы угадали слово: " << word << endl;
    }
    else {
        cout << "\nВы проиграли! Загаданное слово было: " << word << endl;
    }

    return 0;
}
