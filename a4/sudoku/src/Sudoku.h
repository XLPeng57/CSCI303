#ifndef SUDOKU_H
#define SUDOKU_H
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include "StringUtils.h"
#include <random>
#include <tuple>


using namespace std;

/**
 * Class that stores, generates, and solves a Sudoku board.
 * The current implementation supports 9x9 and 16x16 Sudokus.
 */

class Sudoku {
private:
    //the size of the sudoku (9 or 16)
    int sudokuSize;
    //matrix that stores the numbers. The size of the matrix is sudokuSize x sudokuSize.
    int **sudo;

    //returns a vector with the integers found in textLine, which are separated by a space.
    vector<int> splitIntoNumbers(const string &textLine) {
        vector<int> numbers;
        stringstream ss(textLine);
        string item;
        while (getline(ss, item, ' ')) {
            int number = stoi(StringUtils::trim(item));
            numbers.push_back(number);
        }
        return numbers;
    }

public:

    /*
     * Constructor that creates a 9 x 9 Sudoku
     */
    Sudoku() {
        Sudoku(9);
    }

    /*
     * Constructor that creates a Sudoku from the input matrix (sudo) and size (sudokuSize).
     */
    Sudoku(int sudokuSize, int **sudo) {
        this->sudokuSize = sudokuSize;
        this->sudo = sudo;

    }

    /*
     * Constructor that creates a Sudoku of a given size (sudokuSize) and fills it with zeros.
     */
    Sudoku(int sudoSize) {

        if (sudoSize != 9 && sudoSize != 16) {
            throw "Sudoku size not supported: " + sudoSize;
        }

        sudokuSize = sudoSize;
        sudo = new int *[sudoSize];
        for (int i = 0; i < sudoSize; ++i) {
            sudo[i] = new int[sudoSize];
            for (int j = 0; j < sudoSize; ++j) {
                sudo[i][j] = 0;
            }
        }
    }

    /*
     * Constructor that creates a Sudoku from a text file. The path of the file must be provided
     */
    Sudoku(string filePath) {

        //open the file
        fstream newfile;
        newfile.open(filePath, ios::in);
        if (!newfile.is_open())
            throw "Could not find input file";

        string line;
        int sudoSize = -1;
        int i = 0;

        //iterate over each line that ends with backslash
        while (getline(newfile, line, '\\')) {

            //get the numbers of the line
            vector<int> numbers = splitIntoNumbers(line);

            //determine the size of the Sudoku
            if (sudoSize == -1) {
                sudoSize = numbers.size();
                if (sudoSize != 9 && sudoSize != 16) {
                    throw "Sudoku size not supported: " + sudoSize;
                }
                sudokuSize = sudoSize;
                sudo = new int *[sudoSize];
            }

            sudo[i] = new int[sudoSize];

            //build the Sudoku by adding the numbers
            int j = 0;
            for (int tok: numbers) {
                sudo[i][j] = 0;
                if (tok < 0 || tok > sudoSize)
                    throw "Invalid digit: " + tok;
                else
                    sudo[i][j] = tok;
                j++;
            }

            i++;
        }
        newfile.close();

    }

    /*
     * Prints in the terminal the matrix that corresponds to a Sudoku. It currently supports 9 x 9 and 16 x 16 Sudokus.
     */
    void static printMatrix(int sudoSize, int **matrix) {

        //this is the number of columns in an Sudoku's internal grid
        //for example, in a 9 x 9 sudoku, gridSize = 3
        int gridSize = (int) sqrt(sudoSize);

        for (int i = 0; i < sudoSize; ++i) {

            //print horizontal separator
            if (i % gridSize == 0) {
                printSeparator(sudoSize, gridSize);
            }

            for (int j = 0; j < sudoSize; ++j) {

                //print vertical separator
                if (j % gridSize == 0)
                    cout << "| ";

                //print each number with the appropriate spacing and format
                {
                    string suffix;
                    if (sudoSize == 16) {
                        if (matrix[i][j] < 10)
                            suffix = " ";
                    }

                    if (matrix[i][j] == 0)
                        cout << ". " << suffix;
                    else
                        cout << matrix[i][j] << " " << suffix;
                }
            }
            cout << "|" << endl;
        }

        //-------------------------------
        //print the last horizontal separator
        printSeparator(sudoSize, gridSize);
    }

    /*
     * Prints the horizontal separator of a Sudoku in the terminal.
     */
    void static printSeparator(int sudoSize, int gridSize) {
        string separator;
        for (int j = 0; j < sudoSize; ++j) {
            if (j % gridSize == 0)
                separator.append("+-");
            else {
                separator.append("---");
                if (sudoSize == 16) separator.append("-");
            }
        }
        separator.append("+");
        cout << separator << endl;
    }

    /*
     * Prints this Sudoku in the terminal.
     */
    void print() {
        printMatrix(sudokuSize, sudo);
    }


    /*
     * Returns true if the number provided is not found in row i and column j of the given Sudoku (sudokuMatrix).
     * Otherwise, it returns false.
     *
     * This method basically checks if a number can be inserted in position (i,j)
     */



    static bool isValid(int **sudokuMatrix, int number, int i, int j, int sudoSize) {
        int s = int(sqrt(sudoSize));
        return numberNotInRow(sudokuMatrix, number, i, sudoSize) &&
               numberNotInColumn(sudokuMatrix, number, j, sudoSize)&& noRepeat(sudokuMatrix,sudoSize,i-i%s,j-j%s,number);
    }

    //check if the number has appeared in the grid and add this to isVaild method

    /*
     * Returns true if the number provided is not found in column j of the given Sudoku (sudokuMatrix).
     * Otherwise, it returns false.
     */
    static bool numberNotInColumn(int *const *sudokuMatrix, int number, int j, int sudoSize) {
        for (int k = 0; k < sudoSize; ++k) {
            if (number == sudokuMatrix[k][j]) return false;
        }
        return true;
    }

    /*
     * Returns true if the number provided is not found in row i of the given Sudoku (sudokuMatrix).
     * Otherwise, it returns false.
     */
    static bool numberNotInRow(int *const *sudokuMatrix, int number, int i, int sudoSize) {
        for (int k = 0; k < sudoSize; ++k) {
            if (number == sudokuMatrix[i][k]) return false;
        }
        return true;
    }

    static bool noRepeat(int **sudokuMatrix,int sudoSize,int row, int col, int number)
    {
        int s = int(sqrt(sudoSize));

        for (int i = 0; i<s; i++) {
            for (int j = 0; j < s; j++) {
                if (sudokuMatrix[row + i][col + j] == number)
                    return false;
            }
        }
        return true;
    }


    static bool RecurFill(int **sudokuMatrix,int i, int j,int sudoSize)
    {
        int s = int(sqrt(sudoSize));
        if (i<sudoSize-1&&j>=sudoSize){
            i = i + 1;
            j = 0;
        }
        if (i < s){
            if (j < s) {
                j = s;
            }
        }
        if (i>=sudoSize && j>=sudoSize) {
            return true;
        }else if (i < sudoSize-s){
            if (j == (int)(i/s)*s) {
                j = j + s;
            }
        }else{
            if (j == sudoSize-s){
                i = i + 1;
                j = 0;
                if (i>=sudoSize)
                    return true;
            }
        }
        for (int n = 1; n<=sudoSize; n++){
            if (isValid(sudokuMatrix, n, i, j,sudoSize)){
                sudokuMatrix[i][j] = n;
                if (RecurFill(sudokuMatrix,i, j+1,sudoSize))
                    return true;
                sudokuMatrix[i][j] = 0;
            }
        }
        return false;
    }


    /*
     * Generates a random Sudoku of size sudoSize x sudoSize.
     * It returns a vector (a pointer) with two elements:
     *      1. the first element is the complete Sudoku (i.e., randomly generated)
     *      2. the second element is the same Sudoku but with 30% of the numbers deleted.
     */
    static vector<Sudoku>* generate(int sudoSize) {
        return generate(time(nullptr), sudoSize, 0.3);
    }

    /*
     * Generates a random Sudoku of size 9 x 9.
     * It receives missingRate, which is the % of numbers to be deleted from the Sudoku (0 <= missingRate <= 1).
     *
     * It returns a vector (a pointer) with two elements:
     *      1. the first element is the complete Sudoku (i.e., randomly generated)
     *      2. the second element is the same Sudoku but with missingRate% of the numbers deleted.
     */
    static vector<Sudoku>* generate(float missingRate) {
        return generate(time(nullptr), 9, missingRate);
    }

    /*
     * Generates a random Sudoku of size sudoSize x sudoSize.
     * It receives missingRate, which is the % of numbers to be deleted from the Sudoku (0 <= missingRate <= 1).
     * It also receives a random seed (i.e., a number) for the C++ random number generator.
     *
     * Calling this method multiple times with the same seed and parameters will generate exactly the same Sudoku.
     *
     * It returns a vector (a pointer) with two elements:
     *      1. the first element is the complete Sudoku (i.e., randomly generated)
     *      2. the second element is the same Sudoku but with missingRate% of the numbers deleted.
     */


    static vector<Sudoku>* generate(time_t seed, int sudoSize, float missingRate) {

        //IMPLEMENT YOUR CODE HERE!
        //GENERAL STRATEGY:
        //1. Initialize a matrix (called sudokuMatrix) of size sudoSize x sudoSize  with zeros
        //2. Randomly fill in the (3x3 or 4x4) internal grids of the Sudoku from the diagonal (see the file Sudoku-grids.pdf):
        // For each one of these grids:
        // (1) create a vector with the possible numbers of the Sudoku (e.g., 1-9 or 1-16).
        // (2) shuffle the vector
        // (3) insert the first element from the vector into one empty position of the grid.
        // (4) After the number is inserted, remove it from the vector.
        // (5) Repeat steps 3-4 until the vector is empty (i.e., until the internal grid has been filled in).
        // There is no need to check for Sudoku violations in this part because we are focusing on the diagonal grids.
        //3. Randomly fill in the remaining (3x3 or 4x4) internal grids of the Sudoku (see the file Sudoku-grids.pdf):
        // For each one of these grids:
        // (1) create a vector with the possible numbers of the Sudoku (e.g., 1-9 or 1-16).
        // (2) shuffle the vector.
        // (3) find one element from the vector that can be inserted (according to the Sudoku rules) in the next empty position of the grid
        //     (you can find the element by iterating the vector and using the method isValid).
        // (4) after the number is inserted, remove it from the vector.
        // (5) Repeat steps 3-4 for each empty position of the grid.
        // (6) Since it is possible to not able to insert all numbers in the grid (due to the Sudoku rules),
        //     you need to start over: set the grid with zeros (remove the numbers already inserted), and start from step (1).
        // Eventually, there will be a random sequence that will work, i.e., you will get the grid filled in.
        srand(seed);
        int **sudokuMatrix;
        sudokuMatrix = new int *[sudoSize];
        for(int i = 0; i<sudoSize;i++)
            sudokuMatrix[i] = new int[sudoSize];

        //initailze everything to 0
        for (int i=0; i<sudoSize;i++) {
            for (int j = 0; j < sudoSize; j++) {
                sudokuMatrix[i][j] = 0;
            }
        }
        int s= (int) sqrt(sudoSize);
        for (int i = 0; i<s;i++ ){
            vector<int> numbers;
            for (int j =1; j<sudoSize+1;j++){
                numbers.push_back(j);
            }

            random_shuffle(numbers.begin(), numbers.end());
            vector<int> numbersTemp(numbers);
            for (int k=i*s; k<(i+1)*s;k++){
                for(int l=i*s; l<(i+1)*s; l++){
                    sudokuMatrix[l][k] = numbersTemp.at(0);
                    numbersTemp.erase(numbersTemp.begin());
                }
            }
        }

        RecurFill(sudokuMatrix,0,s,sudoSize);

        //4. Initialize another matrix (called sudokuToSolve), and copy sudokuMatrix into sudokuToSolve
        int **sudokuToSolve;
        sudokuToSolve = new int *[sudoSize];
        for(int i = 0; i<sudoSize;i++)
            sudokuToSolve[i] = new int[sudoSize];
        for (int i=0; i<sudoSize;i++){
            for(int j=0; j<sudoSize; j++) {
                sudokuToSolve[i][j] = sudokuMatrix[i][j];
            }
        }

        //5. Randomly remove from sudokuToSolve X numbers, according to missingRate (X = missingRate *  sudoSize * sudoSize)
        //6. Build and return the corresponding Sudokus (uncomment the code below).
        int remove = missingRate * sudoSize * sudoSize;
        for (int i =0; i<remove;i++){
            int random_row = rand() % sudoSize ;
            int randon_col = rand() % sudoSize ;
            sudokuToSolve[random_row][randon_col] =0;
        }
        Sudoku completeSudoku = Sudoku(sudoSize, sudokuMatrix);
        Sudoku toSolveSudoku = Sudoku(sudoSize, sudokuToSolve);
        return new vector<Sudoku>{completeSudoku, toSolveSudoku};

    }
};


#endif //SUDOKU_H