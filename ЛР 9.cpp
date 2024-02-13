#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int add_words_in_mas(string* ptr_mas_words, string row) {
    int space_1 = 0, space_2; //индекс послелнего пробела
    int count = 0; //счетчик слов в строке
    for (int i = 0; i < row.size(); i++) {
        if (row[i] == 32) { //если к-л символ €вл€етс€ пробелом
            ptr_mas_words[count] = row.substr(space_1, i - space_1); //записываю в массив новое слово
            space_1 = i + 1; //мен€ю индекс последнего пробела
            ++count; //мен€ю колличество слов в строке
        }
    }
    ptr_mas_words[count] = row.substr(space_1, row.size() - space_1); //последнее слово в строке
    return count + 1; //колличество слов с строке

    //ptr_mas_words - массив где хран€тс€ все слова текущей строки
    //row - текуща€ строка
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

    //ptr - массив где хран€тс€ все слова текущей строки
    //length - колличество слов в текущей строке
}

bool is_that_a_digit(char symbol) { //провер€ю: символ это цифра или нет
    bool flag = false; //сейчас цифра не найдена
    char list_of_numbers[] = { '0','1','2','3','4','5', '6','7','8', '9' };
    for (int i = 0; i < 10 && !flag; ++i){ //прохожу по списку со всеми цифрами
        //cout << symbol << ' ';
        if (symbol == list_of_numbers[i]) flag = true; //цифра найдена
    }
    //cout << endl;
    return flag; //символ это цифра или нет
    //symbol - какой либо символ
}

int searching_for_numbers(string* ptr_line, int len, int& max_count, int& index_max_count) {
    int count;
    for (int i = 0; i < len; ++i) {
        count = 0;
        for (int j = 0; j < ptr_line[i].size(); ++j) {
            //cout << ptr_line[i][j] << ' ';
            count += is_that_a_digit(ptr_line[i][j]);
        }
        //cout << count << ' ';
        if (count > max_count) {
            cout << "»зменений в searching_for_numbers!" << endl;
            max_count = count; //количество цифр в числе
            index_max_count = i + 1; //индекс слова с максимальным колличесвом цифр
        }

    }
    //cout << endl;
    return index_max_count;

    //ptr_line - массив со словами в строке
    //len - количество элементов в массиве
    //max_count - текущее максимальное количество цифр
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
    int the_ordinal_number_of_the_ord = 0; //пор€дковый номер слов

    int maximum_of_digits[] = { 0,0 };
    int new_maximum_of_digits[] = { 0,0 };
    //первый индекс - индекс слова
    //второй индекс - последнее максимальной количество цифр
    

    ifstream input("F1.txt");
    ofstream output("F2.txt");

    string line;

    while (getline(input, line)) {
        string all_words_in_line[256]; //массив всех слов в строке
        int number_of_words = add_words_in_mas(all_words_in_line, line); //колличество слов в строке




        searching_for_numbers(all_words_in_line, number_of_words, new_maximum_of_digits[1], new_maximum_of_digits[0]);

        if (new_maximum_of_digits[1] > maximum_of_digits[1]) {
            cout << "»зменений в цифрах!" << endl;
            maximum_of_digits[0] = the_ordinal_number_of_the_ord + new_maximum_of_digits[0];
            maximum_of_digits[1] = new_maximum_of_digits[1];
        }



        bool equal_words = the_same_words(all_words_in_line, number_of_words); //есть ли в строке одинаковые слова?
        if (equal_words) { //если есть одинаковые слова, то добавл€ю строку в F2
            output << line << endl;
        }
        the_ordinal_number_of_the_ord += number_of_words;

        

    }

    //cout << is_that_a_digit('1') << endl;

    cout << "»з файла F1 в файл F2 скопированны все строки, в которых содержитс€ не менее двух одинаковых слов" << endl;
    cout << "Ќомер слова в котором больше всего цифр " << maximum_of_digits[0] << ' ' << maximum_of_digits[1] << endl;

    input.close(); //закрываю файл
    output.close();//закрываю файл
    
    return 0;
}

