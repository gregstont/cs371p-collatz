#include <iostream> // endl, istream, ostream
#include <stdlib.h>
#include <time.h>

#include "Collatz.h"


#define SLOT_SIZE 100

/**
 * generate the acceptance tests file
 */

#define MAX_NUM 200000

void generate_acceptance_tests() {
    using namespace std;
    
    srand(time(0));
    
    cout << "1 1" << endl;
    cout << "1 2" << endl;
    cout << "9 9" << endl;
    cout << "999999 999999" << endl;
    
    for(int i = 0; i < 1000; i++) {
        cout << rand() % MAX_NUM + 1 << " " << rand() % MAX_NUM + 1 << endl;
    }
}

/**
 * generate the meta cache to be used in the program
 */
void build_meta_cache() {
    using namespace std;
    //initialize_cache();
    int stop = 99;
    int start = 0;
    //int count = 0;
    cout << "int meta_cache[10000] = {";
    while(stop < 999999) {
        int result;
        if(start == 0)
            result = collatz_eval (1, stop);
        else
            result = collatz_eval (start, stop);
        cout << result << ",";
        start += SLOT_SIZE;
        stop += SLOT_SIZE;
        //cout << start << " " << stop << " " << result << endl;
        //count++;
    }
    cout << "0};" << endl;
    //cout << count << endl;
}



int main(int argc, char **argv) {
    //build_meta_cache();
    generate_acceptance_tests();
    return 0;
}