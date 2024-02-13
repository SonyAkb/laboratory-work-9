#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int add_words_in_mas(string* ptr, string row) {
    int space_1 = 0, space_2; //������ ���������� �������
    int count = 0; //������� ���� � ������
    for (int i = 0; i < row.size(); i++) {
        if (row[i] == 32) { //���� �-� ������ �������� ��������
            ptr[count] = row.substr(space_1, i - space_1); //��������� � ������ ����� �����
            space_1 = i + 1; //����� ������ ���������� �������
            ++count; //����� ����������� ���� � ������
        }
    }
    ptr[count] = row.substr(space_1, row.size() - space_1); //��������� ����� � ������
    return count + 1; //����������� ���� � ������

    //ptr - ������ ��� �������� ��� ����� ������� ������
    //row - ������� ������
}

bool the_same_words(string* ptr, int length) {
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
    //������ ������ - ������ �����
    //������ ������ - ��������� ������������ ���������� ����

    ifstream input("F1.txt");
    ofstream output("F2.txt");

    string line;

    while (getline(input, line)) {
        string all_words_in_line[256]; //������ ���� ���� � ������
        
        int number_of_words = add_words_in_mas(all_words_in_line, line); //����������� ���� � ������


        //print_mas(all_words_in_line, number_of_words);

        bool equal_words = the_same_words(all_words_in_line, number_of_words); //���� �� � ������ ���������� �����?

        if (equal_words) { //���� ���� ���������� �����, �� �������� ������ � F2
            output << line << endl;
        }
        the_ordinal_number_of_the_ord += number_of_words;
    }


    input.close(); //�������� ����
    output.close();//�������� ����
    
    return 0;
}

