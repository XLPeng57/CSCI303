


#include <iostream>
#include "Sudoku.h"

using namespace std;

int main(int argc, char *argv[]) {

    try {

        Sudoku sudoku("../sudoku.txt");
        cout<<"Sudoku read from file:"<<endl;
        sudoku.print();

        //----------------------------------

        int seed = 12312232;
        vector<Sudoku> *sudosSameSeed = Sudoku::generate(seed, 16, 0.3);
        //vector<Sudoku> *sudos = Sudoku::generate(9);

        if (sudosSameSeed != nullptr) {
            Sudoku complete = sudosSameSeed->at(0);
            Sudoku toSolve = sudosSameSeed->at(1);
            cout << "Complete sudoku:" << endl;
            complete.print();
            cout << "Sudoku to solve:" << endl;
            toSolve.print();
        }else{
            cout<<"Nothing to print, the randomly-generated Sudoku is null!"<<endl;
        }

    } catch (char const *msg) {
        cout << "Error: " << msg << endl;
    }


    return 0;
}
