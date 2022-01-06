#ifndef __PARCER_H__
#define __PARCER_H__
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Module
{
public:
    int name;
    int num_clb;
    int num_mux;
    int x, y;
    // int idx_irl;
    Module(int name_, int num_clb_, int num_mux_) : name(name_), num_clb(num_clb_), num_mux(num_mux_), x(0), y(0) {}
};

class Net
{
public:
    int name;
    vector<Module *> vec_module;
    Net(int name_) : name(name_) {}
};

void parse_arch(string filename_arch, int &R, int &C, int &S, int &D);
void parse_module(string filename_module, vector<Module *> &vec_mod);

Module *find_module(vector<Module *> vec_mod, int name_mod);
void parse_net(string filename_net, vector<Module *> vec_mod, vector<Net *> vec_net);

void output_floorplan(string filename_floorplan, vector<Module *> vec_mod, vector<Net *> vec_net);

#endif