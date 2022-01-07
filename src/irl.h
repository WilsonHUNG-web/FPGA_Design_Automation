#ifndef __IRL_H__
#define __IRL_H__
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class INDEX_IRL
{
public:
    int i, j;
    INDEX_IRL(int horizontal_i, int vertical_j) : i(horizontal_i), j(vertical_j) {}
};

class REALI
{
public:
    int x, y;
    int w, h;
    REALI(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {}
};

INDEX_IRL get_irl_idx(int x, int y, int s, int d);

#endif