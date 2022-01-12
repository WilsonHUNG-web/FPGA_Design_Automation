#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <random>
#include "io.h"
#include "timer.h"
#include "irl.h"
#include "sa.h"
#define kmove 20
#define Prob 0.95

using namespace std;

bool deactivate_op1 = false;
// int count_traverse = 0;

// global vars
Archi *archi = new Archi;
vector<Module *> vec_mod;
vector<Net *> vec_net;
float min_aspect = 0.1;
double HPWL = 0;
unsigned int seed;

vector<int> contourH;

int num_mod, num_net, C, R;
int cur_height = 0;
// ouble HPWL = 0;
//  funcs
void init_global_vars();
// COST cal_cost();
void cal_cost(COST &output_cost);
//

void init_global_vars()
{
    num_mod = vec_mod.size();
    num_net = vec_net.size();
    C = archi->C;
    R = archi->R;
    contourH = vector<int>(C, 0);
}

void cal_avg_width()
{
    int avg_width, sum_width;
    for (size_t i = 0; i < vec_mod.size(); i++)
    {
        avg_width = sum_width = 0;
        for (size_t j = 0; j < vec_mod[i]->irl_set_format.size(); j++)
        {
            sum_width += vec_mod[i]->irl_set_format[j][0]->w;
            /* code */
        }
        avg_width = sum_width / archi->w_irl;
        vec_mod[i]->avg_width = avg_width;
    }
}

void sort_mod_by_avg_width()
{
    sort(vec_mod.begin(), vec_mod.end(), [](const Module *a, const Module *b)
         { return a->avg_width > b->avg_width; });
}

void sort_mod_by_name()
{
    sort(vec_mod.begin(), vec_mod.end(), [](const Module *a, const Module *b)
         { return a->name < b->name; });
}

void place()
{
    int num_module_left = num_mod;

    int x_start = 0, x_end = 0;
    Module *temp_mod;
    do
    {
        x_start = 0;
        for (size_t i = 0; i < vec_mod.size(); i++)
        {
            temp_mod = vec_mod[i];
            if (num_module_left == 0)
                break;
            if (temp_mod->placed)
                continue;

            x_end = x_start + temp_mod->get_width_format(x_start, archi);

            if (x_end > C)
                continue;
            else // commit placement
            {
                temp_mod->x = x_start;
                temp_mod->y = cur_height;
                temp_mod->w = temp_mod->get_width_format(x_start, archi);
                x_start = x_end;

                temp_mod->placed = true;
                num_module_left--;
                if (x_end == C)
                    break;
            }
        }
        cur_height += 3;
    } while (num_module_left > 0);
}

double sub_HPWL = 0;
double minx = 99999, miny = 99999, maxx = 0, maxy = 0;
void cal_HPWL()
{

    for (size_t i = 0; i < vec_mod.size(); i++)
    {
        vec_mod[i]->cal_center();
    }

    for (size_t i = 0; i < vec_net.size(); i++)
    {
        minx = 99999, miny = 99999, maxx = 0, maxy = 0;
        for (size_t j = 0; j < vec_net[i]->vec_module.size(); j++)
        {
            Module *mod = vec_net[i]->vec_module[j];
            if (mod->x_cen < minx)
                minx = mod->x_cen;
            if (mod->x_cen > maxx)
                maxx = mod->x_cen;

            if (mod->y_cen < miny)
                miny = mod->y_cen;
            if (mod->y_cen > maxy)
                maxy = mod->y_cen;
        }
        HPWL += (maxx - minx) + (maxy - miny);
    }
}

int main(int argc, char *argv[])
{
    string filename_arch(argv[1]);
    string filename_module(argv[2]);
    string filename_net(argv[3]);
    string filename_floorplan(argv[4]);
    // cout << "file inputs: ";
    // cout << filename_arch << " ";
    // cout << filename_module << " ";
    // cout << filename_net << " ";
    // cout << filename_floorplan << endl;

    string case_name = filename_arch;
    case_name.erase(0, 14);
    case_name.erase(5, 5);
    seed = seed_selector(case_name);
    srand(seed);

    // cout << "[Run " << case_name << "]" << endl;

    parse_arch(filename_arch, archi);
    // cout << "R, C, S, D and w_irl: ";
    // cout << archi->R << " " << archi->C << " " << archi->S << " " << archi->D << " and " << archi->w_irl << endl;
    parse_module(filename_module, vec_mod);
    parse_net(filename_net, vec_mod, vec_net);

    init_global_vars();
    init_module_irls_format(vec_mod, archi, min_aspect);

    cal_avg_width();
    // sort_mod_by_avg_width();
    random_shuffle(vec_mod.begin(), vec_mod.end());
    place();
    sort_mod_by_name();
    cal_HPWL();
    // cout << "Flooplan Height:" << cur_height << endl;
    // cout << "This solution is ";
    // cout << "HPWL, seed" << endl;
    if (cur_height <= R)
        cout << HPWL << "," << seed << endl;
    else
        cout << "NOT valid." << endl;

    output_floorplan_format(filename_floorplan, vec_mod, vec_net, archi, HPWL);

    return 0;
}
