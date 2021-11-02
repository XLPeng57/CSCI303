#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Sudoku{
private:
    int sudo[9][9];
public:
    Sudoku();
    void readfile​(string str);
    void printSodoku();
};

Sudoku::Sudoku(){

    for (int j=0; j<9;j++){
        for(int i=0;i<9;i++) {
            sudo[j][i] = 0;
        }
    }

}
/*Sudoku::Sudoku(){
    readFromFile​(string str);
}*/



void Sudoku::readfile​(string path){
    string temp[9];
    short loop = 0;
    std::string line;
    auto myFile = path;
    std::ifstream in(myFile);
    if (in.is_open()) {

        while (getline(in, line)) {
            string word = "";
            for (auto x : line)
            {
                if (x != '\\' and x != ' ')
                {
                    word = word + x;
                    temp[loop] = word;

                }else if (x == '\\'){
                    loop++;
                    word = "";

                }
            }

            if (loop==9)break;

        }


        in.close();
    }else {
        cout << "Unable to open file";
    }

    for (int j=0; j<9;j++){
        for(int i=0;i<9;i++){
            if(isdigit(temp[j].at(i))) {
                char c;
                c = temp[j].at(i);
                int x = c - '0';
                sudo[j][i] = x;
            }

        }
    }
}

void Sudoku::printSodoku() {
    string print1 = "+-------+-------+-------+";
    string print2 = "|";
    string print3 = " ";

    cout << print1 << endl;
    for (int a=0;a<9;a++) {
        cout << print2;
        for (int b = 0; b < 9; b++) {
            if (sudo[a][b] == 0) {
                cout << print3 << ".";
            } else {
                cout << print3 << sudo[a][b];
            }


            if (b == 2 || b == 5)
                cout << print3 << print2;
        }
        cout << print3 << print2 << endl;
        if (a == 2 || a == 5 || a == 8)
            cout << print1 << endl;
    }
}





int main(int argc, char *argv[]) {
    auto file = argv[1];
    string s(file);
    Sudoku test;
    test.readfile​(file);
    test.printSodoku();

}