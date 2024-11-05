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
            if (!b) {
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
            if (!b) {
                decr += current;
            }
        }
        return decr;
    }
};


void program1(string& text) {
    string esh, desh;
    MyClass myclass(text, text.length());

    esh.resize(256);
    for (int i = 0; i < 256; i++) {
        esh[i] = static_cast<char>(i);
    }

    desh.resize(256);
    for (int i = 0; i < 256; i++) {
        desh[i] = static_cast<char>((i + 3) % 256); 
    }

    string en = myclass.encryption(text, esh, desh, text.length());
    cout << "Encrypted with Caesar cipher: " << en << endl;
    text = en;  
}

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

        cout << "Encrypted with transposition cipher:" << endl;
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

        cout << "Decrypted with transposition cipher:" << endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                cout << original[i][j];
            }
        }
        cout << endl;
        return original;
    }
};

void program2(string& text, int SIZE) {
    int rows = (text.length() + SIZE - 1) / SIZE;
    vector<vector<char>> str(rows, vector<char>(SIZE, ' '));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < SIZE; j++) {
            int index = i * SIZE + j;
            if (index < text.length()) {
                str[i][j] = text[index];
            }
        }
    }

    Encryption encrypt(rows, SIZE);
    encrypt.print(str);
    vector<vector<char>> encrypted = encrypt.encr(str);

    text.clear();
    for (int j = 0; j < SIZE; ++j) {
        for (int i = 0; i < rows; ++i) {
            if (encrypted[j][i] != ' ')  
                text += encrypted[j][i];
        }
    }

    cout << "Text after Row-Column transposition: " << text << endl;
}


int main() {
    string text;
    cout << "Enter the text: ";
    getline(cin, text);

    program1(text);

    int SIZE;
    cout << "Enter column size for transposition cipher: ";
    cin >> SIZE;
    cin.ignore(); 
    program2(text, SIZE);

    int rows = (text.length() + SIZE - 1) / SIZE;
    vector<vector<char>> str(rows, vector<char>(SIZE, ' '));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < SIZE; j++) {
            int index = i * SIZE + j;
            if (index < text.length()) {
                str[i][j] = text[index];
            }
        }
    }

    Encryption encrypt(rows, SIZE);
    vector<vector<char>> decrypted = encrypt.decr(str);

    text.clear();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (decrypted[i][j] != ' ')  
                text += decrypted[i][j];
        }
    }

    cout << "Text after Row-Column transposition decryption: " << text << endl;

 
    string esh, desh;
    MyClass myclass(text, text.length());
    esh.resize(256);
    for (int i = 0; i < 256; i++) {
        esh[i] = static_cast<char>(i);
    }

    desh.resize(256);
    for (int i = 0; i < 256; i++) {
        desh[i] = static_cast<char>((i - 3 + 256) % 256);  
    }

    string finalDecryptedText = myclass.decryption(text, esh, desh, text.length());
    cout << "Final decrypted text: " << finalDecryptedText << endl;
    a b c d 
    d e f g
    return 0;
}
