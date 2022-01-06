#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include "io.h"
#include "timer.h"

using namespace std;

int R, C, S, D;
vector<Module *> vec_mod;
vector<Net *> vec_net;

int main(int argc, char *argv[])
{

    auto time_parse_start = time_record();

    string filename_arch(argv[1]);
    string filename_module(argv[2]);
    string filename_net(argv[3]);
    string filename_floorplan(argv[4]);
    cout << "file inputs: ";
    cout << filename_arch << " ";
    cout << filename_module << " ";
    cout << filename_net << " ";
    cout << filename_floorplan << endl;

    parse_arch(filename_arch, R, C, S, D);
    cout << "R, C, S, D: ";
    cout << R << " " << C << " " << S << " " << D << endl;
    parse_module(filename_module, vec_mod);
    parse_net(filename_net, vec_mod, vec_net);

    auto time_parse_end = time_record();

    cout << "parser time: " << time_output(time_parse_start, time_parse_end) << endl;
    // cout << "Ini_time: " << Ini_time << endl;
    // cout << "Compute time: " << Compu_time << endl;
    // cout << "Total time: " << O_time + I_time + Compu_time + Ini_time << endl;

    return 0;
}
