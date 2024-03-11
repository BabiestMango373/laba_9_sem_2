#include <iostream>
#include <fstream>
#include <string>
#include <locale> // Для работы с русскими символами

using namespace std;

// Функция для подсчета гласных букв в слове
int countgl(const string& word) {
    const string vowels = "аеёиоуыэюяАЕЁИОУЫЭЮЯ";
    int count = 0;
    for (char c : word) {
        if (vowels.find(c) != string::npos) {
            count++;
        }
    }
    return count;
}

// Функция для определения номера слова с наибольшим количеством гласных букв
int findgl(const string& line) {
    int maxgl = 0;
    int glIndex = 0;

    string word;
    int wordIndex = 1;
    for (char c : line) {
        if (c == ' ' || c == '\t') {
            if (!word.empty()) {
                int vCount = countgl(word);
                if (vCount > maxgl) {
                    maxgl = vCount;
                    glIndex = wordIndex;
                }
                word = "";
                wordIndex++;
            }
        } else {
            word += c;
        }
    }
    // Проверяем последнее слово в строке
    if (!word.empty()) {
        int vowelsCount = countgl(word);
        if (vowelsCount > maxgl) {
            maxgl = vowelsCount;
            glIndex = wordIndex;
        }
    }
    return glIndex;
}

// Функция для создания и заполнения файла F1.txt пользователем
void file(int numLines) {
    ofstream file("F1.txt"); // Открываем файл для записи

    if (!file.is_open()) {
        cerr << "Файл не открыт" << endl;
        return;
    }

    cout << "Введите содержимое строки"<<numLines << endl;

    string line;
    for (int i = 0; i < numLines; ++i) {
        getline(cin, line);
        file << line << endl;
    }

    file.close();
}

int main() {
    locale::global(locale("")); // Устанавливаем локаль для поддержки русских символов
    
    int numLines;
    cout << "Введите количество строк для файла F1.txt: ";
    cin >> numLines;
    cin.ignore(); // Очищаем буфер ввода
    
    file(numLines); // Создаем и заполняем файл F1.txt

    ifstream inFile("F1.txt"); // Открываем файл для чтения
    ofstream outFile("F2.txt"); // Открываем файл для записи

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Файл не открыт" << endl;
        return 1;
    }

    string line;
    while (getline(inFile, line)) { // Читаем файл построчно
        string word;
        int wordCount = 0;
        for (char c : line) {
            if (c == ' ' || c == '\t') {
                if (!word.empty()) {
                    wordCount++;
                    word = "";
                }
            } else {
                word += c;
            }
        }
        if (!word.empty()) {
            wordCount++;
        }

        // Проверяем, есть ли больше двух слов в строке
        if (wordCount > 2) {
            outFile << line << endl;
            int maxglIndex = findgl(line);
            cout << "Максимальное количество гласных букв в слове под индексом: " << maxglIndex << endl;
        }
    }

    inFile.close(); // Закрываем файлы
    outFile.close();

    return 0;
}
