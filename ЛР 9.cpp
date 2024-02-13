#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int add_words_in_mas(string* ptr_mas_words, string row) {
    int space_1 = 0, space_2; //������ ���������� �������
    int count = 0; //������� ���� � ������
    for (int i = 0; i < row.size(); i++) {
        if (row[i] == 32) { //���� �-� ������ �������� ��������
            ptr_mas_words[count] = row.substr(space_1, i - space_1); //��������� � ������ ����� �����
            space_1 = i + 1; //����� ������ ���������� �������
            ++count; //����� ����������� ���� � ������
        }
    }
    ptr_mas_words[count] = row.substr(space_1, row.size() - space_1); //��������� ����� � ������
    return count + 1; //����������� ���� � ������

    //ptr_mas_words - ������ ��� �������� ��� ����� ������� ������
    //row - ������� ������
}

bool the_same_words(string* ptr, int length) { //�������� ���������� ���� � ������
    bool flag = false; //������ ��� ���������� ���� � ������
    for (int i = 0; i < length && !flag; ++i) {
        for (int j = i + 1; j < length && !flag; ++j) {
            if (ptr[i] == ptr[j]) { //���� ��� �������� ������� �����, �� flag=true
                flag = true; //� ������ ���� ���������� �����
            }
        }
    }
    return flag; //������� ���������� ���� � ������

    //ptr - ������ ��� �������� ��� ����� ������� ������
    //length - ����������� ���� � ������� ������
}

bool is_that_a_digit(char symbol) { //��������: ������ ��� ����� ��� ���
    bool flag = false; //������ ����� �� �������
    char list_of_numbers[] = { '0','1','2','3','4','5', '6','7','8', '9' };
    for (int i = 0; i < 10 && !flag; ++i){ //������� �� ������ �� ����� �������
        //cout << symbol << ' ';
        if (symbol == list_of_numbers[i]) flag = true; //����� �������
    }
    //cout << endl;
    return flag; //������ ��� ����� ��� ���
    //symbol - ����� ���� ������
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
            cout << "��������� � searching_for_numbers!" << endl;
            max_count = count; //���������� ���� � �����
            index_max_count = i + 1; //������ ����� � ������������ ����������� ����
        }

    }
    //cout << endl;
    return index_max_count;

    //ptr_line - ������ �� ������� � ������
    //len - ���������� ��������� � �������
    //max_count - ������� ������������ ���������� ����
}

void print_mas(string* ptr, int n) { //����� ����������� ����������� �������
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
    int the_ordinal_number_of_the_ord = 0; //���������� ����� ����

    int maximum_of_digits[] = { 0,0 };
    int new_maximum_of_digits[] = { 0,0 };
    //������ ������ - ������ �����
    //������ ������ - ��������� ������������ ���������� ����
    

    ifstream input("F1.txt");
    ofstream output("F2.txt");

    string line;

    while (getline(input, line)) {
        string all_words_in_line[256]; //������ ���� ���� � ������
        int number_of_words = add_words_in_mas(all_words_in_line, line); //����������� ���� � ������




        searching_for_numbers(all_words_in_line, number_of_words, new_maximum_of_digits[1], new_maximum_of_digits[0]);

        if (new_maximum_of_digits[1] > maximum_of_digits[1]) {
            cout << "��������� � ������!" << endl;
            maximum_of_digits[0] = the_ordinal_number_of_the_ord + new_maximum_of_digits[0];
            maximum_of_digits[1] = new_maximum_of_digits[1];
        }



        bool equal_words = the_same_words(all_words_in_line, number_of_words); //���� �� � ������ ���������� �����?
        if (equal_words) { //���� ���� ���������� �����, �� �������� ������ � F2
            output << line << endl;
        }
        the_ordinal_number_of_the_ord += number_of_words;

        

    }

    //cout << is_that_a_digit('1') << endl;

    cout << "�� ����� F1 � ���� F2 ������������ ��� ������, � ������� ���������� �� ����� ���� ���������� ����" << endl;
    cout << "����� ����� � ������� ������ ����� ���� " << maximum_of_digits[0] << ' ' << maximum_of_digits[1] << endl;

    input.close(); //�������� ����
    output.close();//�������� ����
    
    return 0;
}

