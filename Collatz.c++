// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair

#include "Collatz.h"

// ------------
// collatz_read
// ------------

std::pair<int, int> collatz_read (std::istream& r) {
    int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
    int j;
    r >> j;
    return std::make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int cache[1000001];
bool use_cache = false;

int collatz_eval (int i, int j) {
    using namespace std;
    assert(i > 0 && i < 1000001 && j > 0 && j < 1000001);
    int max = -1;
    if(j < i) //swap if j is smaller
    {
        int swap = i;
        i = j;
        j = swap;
    }
    
    if(i < j >> 1) //optimization from quiz (max_cycle_length(10, 100) = max_cycle_length(50, 100))
        i = j >> 1;
    
    for(int k = i; k <= j; k++) {
        
        int count = 1;
        long temp_k = k;
        
        if(use_cache && cache[k] != -1) {
            count = cache[k];
        }
        else {
            while(temp_k > 0) {
                if(temp_k == 1) {
                    temp_k = -1;
                }
                else if(temp_k % 2 == 0) {
                    temp_k = temp_k >> 1;
                    ++count;
                }
                else {
                    //temp_k = 3 * temp_k + 1;
                    temp_k = temp_k + (temp_k >> 1) + 1; //optimization from quiz
                    ++count;
                    ++count;
                }
            }
            cache[k] = count;
        }
        
        
        if(count > max)
            max = count;
    }
    assert(max > 0);
    return max;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;
}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    use_cache = true;
    for(int i = 0; i < 1000001; i++)
        cache[i] = -1;
    
    while (true) {
        const std::pair<int, int> p = collatz_read(r);
        if (p == std::make_pair(0, 0))
            return;
        const int i = p.first;
        const int j = p.second;
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);
    }
}
