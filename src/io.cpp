#include "io.h"

using namespace std;

void parse_arch(string filename_arch, int &R, int &C, int &S, int &D)
{
    ifstream input(filename_arch);
    if (!(input.is_open()))
    {
        cout << "parse_arch() failed to open " << filename_arch << "!!" << endl;
        return;
    }
    else
    {
        input >> R >> C >> S >> D;
        return;
    }
}

void parse_module(string filename_module, vector<Module *> &vec_mod)
{

    ifstream input(filename_module);
    if (!(input.is_open()))
    {
        cout << "parse_module() failed to open " << filename_module << "!!" << endl;
        return;
    }
    else
    {
        int mod_name, num_clb, num_mux;
        while (input >> mod_name >> num_clb >> num_mux)
        {
            Module *new_m = new Module(mod_name, num_clb, num_mux);
            vec_mod.push_back(new_m);
        }
        // print all modules
        // for (size_t i = 0; i < vec_mod.size(); i++)
        //     cout << vec_mod[i]->name << " " << vec_mod[i]->num_clb << " " << vec_mod[i]->num_mux << endl;
        return;
    }
}

Module *find_module(vector<Module *> vec_mod, int name_mod)
{
    Module *temp_mod = nullptr;
    if ((unsigned int)name_mod > vec_mod.size())
    {
        cout << "error: Module name exceeds number of modules in the module list." << endl;
        return temp_mod;
    }
    int idx_mod = name_mod - 1;
    temp_mod = vec_mod[idx_mod];
    return temp_mod;
}

void parse_net(string filename_net, vector<Module *> vec_mod, vector<Net *> vec_net)
{

    ifstream input(filename_net);
    if (!(input.is_open()))
    {
        cout << "parse_net() failed to open " << filename_net << "!!" << endl;
        return;
    }
    else
    {
        string name_str, dummy;
        while (input >> name_str >> dummy)
        {
            int name_net = stoi(name_str);
            // vector<Module *> vec_mod_in_net;

            string name_mod;
            Net *new_net = new Net(name_net);

            while (input >> name_mod)
            {
                if (name_mod == "}")
                    break;
                else
                {
                    Module *temp_mod = find_module(vec_mod, stoi(name_mod));
                    // cout << temp_mod->name << " ";
                    new_net->vec_module.push_back(temp_mod);
                }
            }
            // cout << endl;

            vec_net.push_back(new_net);
        }
    }
    // print netlist
    //  for (size_t i = 0; i < vec_net.size(); i++)
    //  {
    //      cout << vec_net[i]->name << " { ";
    //      for (size_t j = 0; j < vec_net[i]->vec_module.size(); j++)
    //      {
    //          cout << vec_net[i]->vec_module[j]->name << " ";
    //      }
    //      cout << "}" << endl;
    //  }
}

void output_floorplan(string filename_floorplan, vector<Module *> vec_mod, vector<Net *> vec_net)
{
    ofstream output(filename_floorplan);
    if (!(output.is_open()))
    {
        cout << "output_floorplan() failed to open " << filename_floorplan << "!!" << endl;
        return;
    }

    for (size_t i = 0; i < vec_mod.size(); i++)
    {
        Module *temp_mod = vec_mod[i];
        output << temp_mod->name << " " << temp_mod->x << " " << temp_mod->y;
    }

    double HPWL = 0;
    for (size_t i = 0; i < vec_net.size(); i++)
    {
        Net *temp_net;
    }
}