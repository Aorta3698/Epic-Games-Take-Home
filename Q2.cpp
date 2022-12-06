#include <string>
#include <array>
#include <iostream>


/*

I wrote a detailed explanation of my thought process with markdown and LaTex
and put them in the submission.md file.

I am not allowed to submit PDF or share GitHub repo,
so if you would like to see the rendered version of it, I'd suggest Typora or Obsidian.
If you don't have either of those,
you can go to https://stackedit.io/app# and paste the codes in .md in there, and it will render it for you.

*/


// My g++ Version: 11.2.0. Compiled with -std=c++20


/**
 * Given a row-major matrix of integers, builds and returns
 * a string with the entries of that matrix appended in clockwise order
 * separated by ", " for each element.
 *
 * This runs in O(1) Space.
 *
 * Input:
 * value      (int*) - the 1D row of integers
 * numRows    (int)  - the number of rows in the matrix
 * numColumns (int)  - the number of columns in the matrix
 * outBuffer  (char*)- the output string. Guaranteed to be large enough to hold the answer.
 *
 * Output: void
 */
void BuildStringFromMatrix(int* matrix, int numRows, int numColumns, char* outBuffer){
    // edge case
    if (matrix == nullptr){
        throw std::invalid_argument("matrix can't be nullptr.\n");
    }
    if (numRows <= 0 || numColumns <= 0){
        throw std::invalid_argument("numRows and numColumns both must be positive.\n");
    }

    // initial data that we need
    int clockwiseDir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    std::array<int, 4> validRange {0, numColumns, numRows, 0}; // this is the boundary I elaborated on in the .md doc
    std::array<int, 4> lost {1, -1, -1, 1}; // this is the adjustment for boundary in each direction.
    int curDir = 0, row = 0, col = 0, total = numColumns * numRows;

    // helper function to check if (row, col) is within bound.
    auto withinBound = [&validRange](int row, int col) -> bool{
        return row >= validRange[0] && row < validRange[2]
            && col >= validRange[3] && col < validRange[1];
    };

    // compute the answer
    while(total--){
        int value = matrix[row * numColumns + col];
        int size = snprintf(nullptr, 0, "%d, ", value);
        int nextRow = row + clockwiseDir[curDir][0];
        int nextCol = col + clockwiseDir[curDir][1];
        sprintf(outBuffer, "%d%s", value, total? ", " : "");
        if (!withinBound(nextRow, nextCol)){
            validRange[curDir] += lost[curDir];
            curDir = (curDir + 1) % 4;
        }
        row += clockwiseDir[curDir][0];
        col += clockwiseDir[curDir][1];
        outBuffer += size;
    }
}
