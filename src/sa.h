#ifndef __SA_H__
#define __SA_H__

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>

#define nptr -1

using namespace std;

class Module;
class NODE
{
public:
    int parent;
    int Lchild;
    int Rchild;
};

class COST
{
public:
    int width;
    int height;
    double area;
    double HPWL;
    double aspectR;
    double cost;

    COST()
    {
        this->width = 0;
        this->height = 0;
        this->area = 0;
        this->HPWL = 0;
        this->aspectR = 0;
        this->cost = 0;
    }

    COST &operator=(const COST &cost)
    {
        this->width = cost.width;
        this->height = cost.height;
        this->area = cost.area;
        this->HPWL = cost.HPWL;
        this->aspectR = cost.aspectR;
        this->cost = cost.cost;
        return *this;
    }

    ~COST()
    {
        delete this;
    }
};

void build_iniTree(vector<NODE> &tree, int num_module, int &root_idx, vector<Module *> vec_mod);
void build_iniTree_2(vector<NODE> &tree, int num_module, int &root_idx, vector<Module *> vec_mod);

void SA();

#endif