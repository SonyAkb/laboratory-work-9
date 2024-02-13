#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int add_words_in_mas(string* ptr, string row) {
    int space_1 = 0, space_2; //индекс послелнего пробела
    int count = 0; //счетчик слов в строке
    for (int i = 0; i < row.size(); i++) {
        if (row[i] == 32) { //если к-л символ является пробелом
            ptr[count] = row.substr(space_1, i - space_1); //записываю в массив новое слово
            space_1 = i + 1; //меняю индекс последнего пробела
            ++count; //меняю колличество слов в строке
        }
    }
    ptr[count] = row.substr(space_1, row.size() - space_1); //последнее слово в строке
    return count + 1; //колличество слов с строке

    //ptr - массив где хранятся все слова текущей строки
    //row - текущая строка
}

bool the_same_words(string* ptr, int length) {
    bool flag = false; //сейчас нет одинаковых слов в строке
    for (int i = 0; i < length && !flag; ++i) {
        for (int j = i + 1; j < length && !flag; ++j) {
            if (ptr[i] == ptr[j]) { //если два элемента массива равны, то flag=true
                flag = true; //в строке есть одинаковые слова
            }
        }
    }
    return flag; //наличие одинаковых слов в строке

    //ptr - массив где хранятся все слова текущей строки
    //length - колличество слов в текущей строке
}

void print_mas(string* ptr, int n) { //вывод одномерного запутанного массива
    for (int i = 0; i < n; ++i) {
        cout << ptr[i] << "-";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");

    int world_count, c;
    int the_ordinal_number_of_the_ord = 0; //порядковый номер слов
    int maximum_of_digits[] = { 0,0 };
    //первый индекс - индекс слова
    //второй индекс - последнее максимальной количество цифр

    ifstream input("F1.txt");
    ofstream output("F2.txt");

    string line;

    while (getline(input, line)) {
        string all_words_in_line[256]; //массив всех слов в строке
        
        int number_of_words = add_words_in_mas(all_words_in_line, line); //колличество слов в строке


        //print_mas(all_words_in_line, number_of_words);

        bool equal_words = the_same_words(all_words_in_line, number_of_words); //есть ли в строке одинаковые слова?

        if (equal_words) { //если есть одинаковые слова, то добавляю строку в F2
            output << line << endl;
        }
        the_ordinal_number_of_the_ord += number_of_words;
    }


    input.close(); //закрываю файл
    output.close();//закрываю файл
    
    return 0;
}

