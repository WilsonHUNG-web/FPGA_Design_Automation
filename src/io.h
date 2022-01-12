#ifndef __PARCER_H__
#define __PARCER_H__
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class REALI;

class Dimention
{
public:
    int w, h;
    Dimention(int w_, int h_) : w(w_), h(h_) {}
};

class Archi
{
public:
    int R, C, S, D;
    int w_irl;
    int idx_archi_condition;

    void set_w_irl()
    {
        if (this->S < this->D)
        {
            w_irl = this->D;
            idx_archi_condition = 0;
        }
        else // S>=D
        {
            w_irl = this->S + 1;
            idx_archi_condition = 1;
        }
    }
    // Archi(int R_, int C_, int S_, int D_) : R(R_), C(C_), S(S_), D(D_) {}
};

class Module
{
public:
    int name;
    int num_clb;
    int num_mux;
    int x, y;
    int w, h;
    int avg_width;
    bool placed;
    double x_cen, y_cen;
    vector<vector<vector<REALI *>>> irl_set; // 3 * w_irl * len_irl
    vector<vector<REALI *>> irl_set_format;  // 3 * w_irl * len_irl
    vector<vector<int>> idx_REALI_selected;
    vector<int> idx_REALI_selected_format;
    // int idx_irl;
    Module(int name_, int num_clb_, int num_mux_) : name(name_), num_clb(num_clb_), num_mux(num_mux_), x(0), y(0), w(0), h(0), placed(false) {}
    Dimention *get_dimension(Archi *archi);
    void random_realization(Archi *archi);
    int get_width_by_x_n_y_irl(int x_, int y_irl, Archi *archi);

    int get_width(Archi *archi);
    int get_height(Archi *archi);

    int get_width_format(int x_, Archi *archi);
    int get_height_format(Archi *archi);

    void get_3_dimens(int x_, Archi *archi, vector<Dimention *> &dimen_3);
    void cal_center()
    {
        this->x_cen = (double)this->x + (double)this->w;
        this->y_cen = (double)this->y + (double)this->h;
    }
};

class Net
{
public:
    int name;
    vector<Module *> vec_module;
    Net(int name_) : name(name_) {}
};

void parse_arch(string filename_arch, Archi *archi);
void parse_module(string filename_module, vector<Module *> &vec_mod);

Module *find_module(vector<Module *> vec_mod, int name_mod);
void parse_net(string filename_net, vector<Module *> vec_mod, vector<Net *> &vec_net);

void output_floorplan(string filename_floorplan, vector<Module *> vec_mod, vector<Net *> vec_net, Archi *archi, double HPWL);
void output_floorplan_format(string filename_floorplan, vector<Module *> vec_mod, vector<Net *> vec_net, Archi *archi, double HPWL);

#endif