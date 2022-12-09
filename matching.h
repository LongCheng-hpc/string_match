//
// Created by 程龙 on 2022-12-09.
//
#include <vector>

using namespace std;
#define FIFO_SIZE 50
#ifndef STRING_MATCH_MATCHING_H
#define STRING_MATCH_MATCHING_H

#endif //STRING_MATCH_MATCHING_H

bool match(vector<char> &pVector, int pid) {
    for (int i = 0; i < pattern_lengths[pid]; ++i) {
        if(patterns[pid][i] != pVector[pattern_lengths[pid] - 1 - i]){
            return false;
        }
    }
    return true;
}

int match_all(vector<char> &pVector){
    int pattern_id = NO_MATCH;
    for(int pid = 0; pid < PATTERNS_COUNT; pid++){
        if(match(pVector, pid)){
            pattern_id = pattern_id == NO_MATCH ? pid : MULTIPLE_MATCHES;
        }
    }
    return pattern_id;
}

void shift(vector<char> &fifo, char c){
    for (int i = FIFO_SIZE - 1; i > 0 ; i--) {
        fifo[i] = fifo[i - 1];
    }
    fifo[0] = c;
}