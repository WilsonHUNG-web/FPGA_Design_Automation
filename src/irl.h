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

INDEX_IRL get_irl_idx(int x, int y, int s, int d);

#endif