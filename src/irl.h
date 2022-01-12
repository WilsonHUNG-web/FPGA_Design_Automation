#ifndef __IRL_H__
#define __IRL_H__
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "io.h"

using namespace std;

// class Module;
// class Archi;

class INDEX_IRL
{
public:
    int x_irl, y_irl;
    INDEX_IRL(int horizontal_i, int vertical_j) : x_irl(horizontal_i), y_irl(vertical_j) {}
};

class REALI
{
public:
    int w, h;
    float aspect;
    REALI(int w_, int h_) : w(w_), h(h_) { this->aspect = (float)min(w_, h_) / (float)max(w_, h_); }
};

INDEX_IRL *get_irl_idx(int x, int y, Archi *archi);
void init_module_irls(vector<Module *> vec_mod, Archi *archi, float min_aspect);
void gen_realization(Module *mod, Archi *archi, float min_aspect);
void gen_realization_format(Module *mod, Archi *archi, float min_aspect);
pair<int, int> get_num_clb_n_mux(int x, int y, int w, int h, Archi *archi);
void init_irl_idx(vector<Module *> vec_mod);
int get_x_irl(int x, Archi *archi);
int get_y_irl(int y, Archi *archi);
void init_module_irls_format(vector<Module *> vec_mod, Archi *archi, float min_aspect);
void gen_realization_format_height3(Module *mod, Archi *archi, float min_aspect);

#endif