#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MyClass {
private:
    string str;
    int size;

public:
    MyClass(const string& input, int n) {
        this->str = input;
        this->size = n;
    }

    void print(const string& str, int size) {
        cout << str;
        cout << endl;
    }

    string encryption(const string& text, const string& esh, const string& desh, int size) {
        string encr;
        for (int i = 0; i < size; i++) {
            char current = text[i];
            bool b = false;
            for (int j = 0; j < 256; j++) {
                if (current == esh[j]) {
                    encr += desh[j];
                    b = true;
                    break;
                }
            }
            if (b == false) {
                encr += current;
            }
        }
        return encr;
    }

    string decryption(const string& text, const string& esh, const string& desh, int size) {
        string decr;
        for (int i = 0; i < size; i++) {
            char current = text[i];
            bool b = false;
            for (int j = 0; j < 256; j++) {
                if (current == desh[j]) {
                    decr += esh[j];
                    b = true;
                    break;
                }
            }
            if (b == false) {
                decr += current;
            }
        }
        return decr;
    }
};


class Encryption {
private:
    int rows;
    int columns;

public:
    Encryption(int Rows, int Columns) {
        this->rows = Rows;
        this->columns = Columns;
    }

    void print(const vector<vector<char>>& Str) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << Str[i][j] << " ";
            }
            cout << endl;
        }
    }

    vector<vector<char>> encr(const vector<vector<char>>& Str) {
        vector<vector<char>> newStr(columns, vector<char>(rows, ' '));
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                newStr[j][i] = Str[i][j];
            }
        }

        cout << "Encrypted string using Row-Column Cipher:" << endl;
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                cout << newStr[j][i];
            }
        }
        cout << endl;
        return newStr;
    }

    vector<vector<char>> decr(const vector<vector<char>>& Str) {
        vector<vector<char>> original(rows, vector<char>(columns, ' '));
        for (int j = 0; j < columns; ++j) {
            for (int i = 0; i < rows; ++i) {
                original[i][j] = Str[j][i];
            }
        }

        cout << "Decrypted string using Row-Column Cipher:" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << original[i][j];
            }
        }
        cout << endl;
        return original;
    }
};

int main() {
    string text, esh, desh;
    int shift, SIZE, rows, cols;
    cout << "Enter text: ";
    getline(cin, text);
    
    MyClass myclass(text, text.length());
    for (int i = 0; i < 256; ++i) {
        esh += char(i%256); 
    }
    for (int i = 0; i < 256; ++i) {
        desh += char((i + 3) % 256);  
    }

    string caesarEncrypted = myclass.encryption(text, esh, desh, text.length());
    cout << "Caesar Encrypted Text: " << caesarEncrypted << endl;

    cout << "Enter the number of columns for Row-Column Cipher: ";
    cin >> cols;
    SIZE = cols;
    rows = (caesarEncrypted.length() + SIZE - 1) / SIZE; 

    vector<vector<char>> str(rows, vector<char>(SIZE, ' '));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < SIZE; j++) {
            int index = i * SIZE + j;
            if (index < caesarEncrypted.length()) {
                str[i][j] = caesarEncrypted[index];
            }
        }
    }

    Encryption encrypt(rows, SIZE);
    encrypt.print(str);
    vector<vector<char>> rowColEncrypted = encrypt.encr(str);
    vector<vector<char>> rowColDecrypted = encrypt.decr(rowColEncrypted);


    string rowColDecryptedText = "";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (rowColDecrypted[i][j] != ' ') {
                rowColDecryptedText += rowColDecrypted[i][j];
            }
        }
    }

    string caesarDecrypted = myclass.decryption(rowColDecryptedText, esh, desh, rowColDecryptedText.length());
    cout << "Caesar Decrypted Text: " << caesarDecrypted << endl;

    cout << "Final Decrypted Text (Original): " << caesarDecrypted << endl;

    return 0;
}
