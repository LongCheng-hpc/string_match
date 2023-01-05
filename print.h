//
// Created by 程龙 on 2022-12-09.
//

#ifndef STRING_MATCH_PRINT_H
#define STRING_MATCH_PRINT_H

#endif //STRING_MATCH_PRINT_H

void print(char * fifo){
    cout << "start printing" << endl;
    for (int i = 0; i < FIFO_SIZE; ++i)
        cout << fifo[i] << endl;

}
