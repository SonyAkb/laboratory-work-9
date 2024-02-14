#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int add_words_in_mas(string* ptr_mas_words, string row); //преобразую строку в массив слов этой строки
bool the_same_words(string* ptr, int length); //проверка одинаковых слов в строке
bool is_that_a_digit(char symbol); //проверяю: символ - это цифра или нет
void searching_for_numbers(string* ptr_line, int len, int& max_count, int& index_max_count, int numbering);
                        //считаю колличество цифр в слове

int main() {
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");

    bool equal_words;
    int number_of_words;

    int the_ordinal_number_of_the_ord = 0; //порядковый номер слов
    int maximum_of_digits[] = { 0,0 };
    //первый индекс - индекс слова с максимальным кол-ом цифр
    //второй индекс - последнее максимальной количество цифр

    ifstream input("F1.txt"); //входной файловый поток
    ofstream output("F2.txt"); //выходной файловый поток

    string line;

    while (getline(input, line)) {
        string all_words_in_line[256]; //массив всех слов в строке
        number_of_words = add_words_in_mas(all_words_in_line, line); //количество слов в строке

        searching_for_numbers(all_words_in_line, number_of_words, maximum_of_digits[1], maximum_of_digits[0], the_ordinal_number_of_the_ord);

        equal_words = the_same_words(all_words_in_line, number_of_words); //есть ли в строке одинаковые слова?
        if (equal_words) { //если есть одинаковые слова, то добавляю строку в F2
            output << line << endl; //добавляю строку в F2
        }
        the_ordinal_number_of_the_ord += number_of_words; //прибавляю количество слов в текущей строке
    }

    cout << "Из файла F1 в файл F2 скопированны все строки, в которых содержится не менее двух одинаковых слов" << endl;

    if (maximum_of_digits[1] != 0) {
        cout << "Номер слова в котором больше всего цифр: " << maximum_of_digits[0] << endl << "В этом слове цифр: " << maximum_of_digits[1] << endl;
    }
    else cout << "Файл F1 не содержит слов, в которых были бы цифры" << endl;
    
    input.close(); //закрываю файл
    output.close();//закрываю файл
    
    return 0;
}

int add_words_in_mas(string* ptr_mas_words, string row) { //преобразую строку в массив слов этой строки
    int space = 0; //индекс послелнего пробела
    int count = 0; //счетчик слов в строке
    for (int i = 0; i < row.size(); i++) {
        if (row[i] == 32) { //если к-л символ является пробелом
            ptr_mas_words[count] = row.substr(space, i - space); //записываю в массив новое слово
            space = i + 1; //меняю индекс последнего пробела
            ++count; //меняю колличество слов в строке
        }
    }
    ptr_mas_words[count] = row.substr(space, row.size() - space); //последнее слово в строке
    return count + 1; //колличество слов с строке
    //ptr_mas_words - массив где хранятся все слова текущей строки
    //row - текущая строка
}

bool the_same_words(string* ptr, int length) { //проверка одинаковых слов в строке
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

bool is_that_a_digit(char symbol) { //проверяю: символ - это цифра или нет
    bool flag = false; //сейчас цифра не найдена
    char list_of_numbers[] = { '0','1','2','3','4','5', '6','7','8', '9' };
    for (int i = 0; i < 10 && !flag; ++i) { //прохожу по списку со всеми цифрами
        if (symbol == list_of_numbers[i]) flag = true; //цифра найдена
    }
    return flag; //символ это цифра или нет
    //symbol - какой либо символ
}

void searching_for_numbers(string* ptr_line, int len, int& max_count, int& index_max_count, int numbering) {
    //считаю колличество цифр в слове
    int count; //колличество цифр в слове
    for (int i = 0; i < len; ++i) { //переход по словам в массиве слов строки
        count = 0; //колличество цифр в новом слове
        for (int j = 0; j < ptr_line[i].size(); ++j) { //переход по буквам в конкретном слове
            count += is_that_a_digit(ptr_line[i][j]); //если цифра найдена, то прибавится 1
        }
        if (count > max_count) { //если новое кол-о цифр больше предыдущего наибольшего
            max_count = count; //количество цифр в числе
            index_max_count = numbering + i + 1; //НОМЕР слова с максимальным колличесвом цифр
        }
    }
    //ptr_line - массив со словами в строке
    //len - количество элементов в массиве
    //max_count - текущее максимальное количество цифр
    //max_count текущее максимальной кол-о цифр в слове
    //index_max_count - номер необходимого слова  
    //numbering - текущее кол-о слов
}