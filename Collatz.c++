// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

using namespace std;

int cache[10000005] = { };

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j)
{

    int max = 0;

    int count= 0;
    int temp = i;
    int copyOfTemp = temp;

    int larger;
    int smaller;

    if(i < j)
    {
        larger = j;
        smaller = i;
    }
    else{
        larger = i;
        smaller = j;
    }

    assert(smaller <= larger);

    for(int current = smaller; current < larger+1; current++)
    {
        temp = current;
        count = 1;
        while(temp != 1)
        {
            if(temp % 2 == 0)
            {
                copyOfTemp = temp;
                temp = temp/2;
                
		        if(temp > 0 && temp < 900000 && copyOfTemp > 0 && copyOfTemp < 900000)
                {
                    assert(temp > 0);
                    assert(copyOfTemp > 0);

                    if(cache[temp] != 0)
                    {
                        count += cache[temp];
                        break;
                    }
                     else
                        cache[copyOfTemp] = collatz_eval(temp, temp) +1 ;
                }

                count++;
            }
            else
            {
                copyOfTemp = temp;
                temp = 3*temp +1;
                
		        if(temp > 0 && temp < 900000 && copyOfTemp > 0 && copyOfTemp < 900000)
                {
                    assert(temp > 0);
                    assert(copyOfTemp > 0);

                    if(cache[temp] != 0)
                    {
                        count += cache[temp];
                        break;
                    }
                    else
                        cache[copyOfTemp]= collatz_eval(temp, temp) + 1;
		        }

                count++;
            }
        }

        if(count > max)
        {
            max = count;
        }
        assert(max >= count);
    }

    return max;
}


// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
