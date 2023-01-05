#include <iostream>
#include <vector>
#include "patterns.h"
#include "matching.h"
#include "print.h"
using namespace std;
#define TEST_SIZE 1

int main() {
//    vector<char> fifo(FIFO_SIZE, ' ');
    char fifo[FIFO_SIZE];

//    memset(fifo, ' ', sizeof(char) * FIFO_SIZE);
    for (int i = 0; i < FIFO_SIZE; ++i) {
        fifo[i] = ' ';
    }
//    for (int i = 0; i < PATTERNS_COUNT; ++i) {
     for (int i = 0; i < TEST_SIZE; ++i) {                     // loop input stream
        for (int j = 0; j < pattern_lengths[i]; ++j) {  // loop patterns
            shift(fifo, patterns[i][j]);         // shift input

            int tmp_res = match_all(fifo);
            if (tmp_res != NO_MATCH){
                cout << tmp_res << endl;
                print(fifo);
            }
        }
    }

}
