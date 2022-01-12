#include "io.h"
#include "irl.h"

using namespace std;

void parse_arch(string filename_arch, Archi *archi)
{
    ifstream input(filename_arch);
    if (!(input.is_open()))
    {
        cout << "parse_arch() failed to open " << filename_arch << "!!" << endl;
        return;
    }
    else
    {
        input >> archi->R >> archi->C >> archi->S >> archi->D;
        archi->set_w_irl();
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
            Module *new_m = new Module(--mod_name, num_clb, num_mux);
            vec_mod.push_back(new_m);
        }
        // print all modules
        //  for (size_t i = 0; i < vec_mod.size(); i++)
        //      cout << vec_mod[i]->name << " " << vec_mod[i]->num_clb << " " << vec_mod[i]->num_mux << endl;
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
    // int idx_mod = name_mod - 1;
    // temp_mod = vec_mod[idx_mod];
    temp_mod = vec_mod[name_mod];
    return temp_mod;
}

void parse_net(string filename_net, vector<Module *> vec_mod, vector<Net *> &vec_net)
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
                    int int_name_mod = stoi(name_mod);
                    int_name_mod = int_name_mod - 1;
                    Module *temp_mod = find_module(vec_mod, int_name_mod);
                    // cout << temp_mod->name << " ";
                    new_net->vec_module.push_back(temp_mod);
                }
            }
            // cout << endl;

            vec_net.push_back(new_net);
        }
    }
    // print netlist
    // for (size_t i = 0; i < vec_net.size(); i++)
    // {
    //     cout << vec_net[i]->name << " { ";
    //     for (size_t j = 0; j < vec_net[i]->vec_module.size(); j++)
    //     {
    //         cout << vec_net[i]->vec_module[j]->name << " ";
    //     }
    //     cout << "}" << endl;
    // }
}

void output_floorplan(string filename_floorplan, vector<Module *> vec_mod, vector<Net *> vec_net, Archi *archi, double HPWL)
{
    ofstream output(filename_floorplan);
    if (!(output.is_open()))
    {
        cout << "output_floorplan() failed to open " << filename_floorplan << "!!" << endl;
        return;
    }
    Module *temp_mod;
    for (size_t i = 0; i < vec_mod.size(); i++)
    {
        temp_mod = vec_mod[i];
        output << temp_mod->name + 1 << " " << temp_mod->x << " " << temp_mod->y << " " << temp_mod->get_width(archi) << " " << temp_mod->get_height(archi);
    }
    cout << endl;
    cout << HPWL;
    // double HPWL = 0;
    //  for (size_t i = 0; i < vec_net.size(); i++)
    //  {
    //      Net *temp_net = vec_net[i];
    //  }
}

void output_floorplan_format(string filename_floorplan, vector<Module *> vec_mod, vector<Net *> vec_net, Archi *archi, double HPWL)
{
    ofstream output(filename_floorplan);
    if (!(output.is_open()))
    {
        cout << "output_floorplan() failed to open " << filename_floorplan << "!!" << endl;
        return;
    }
    Module *temp_mod;
    for (size_t i = 0; i < vec_mod.size(); i++)
    {
        temp_mod = vec_mod[i];
        output << temp_mod->name + 1 << " " << temp_mod->x << " " << temp_mod->y << " " << temp_mod->w << " " << temp_mod->h << endl;
    }
    // cout << endl;
    output << HPWL;
    // double HPWL = 0;
    //  for (size_t i = 0; i < vec_net.size(); i++)
    //  {
    //      Net *temp_net = vec_net[i];
    //  }
}
Dimention *Module::get_dimension(Archi *archi)
{
    // cout << "get_dimension" << endl;
    INDEX_IRL *idx_ril = get_irl_idx(this->x, this->y, archi);
    int x_irl = idx_ril->x_irl;
    int y_irl = idx_ril->y_irl;
    // cout << x_irl << ", " << y_irl << endl;
    int idx_irl = this->idx_REALI_selected[y_irl][x_irl];

    int w = this->irl_set[y_irl][x_irl][idx_irl]->w;
    int h = this->irl_set[y_irl][x_irl][idx_irl]->h;
    Dimention *dimention = new Dimention(w, h);

    return dimention;
}

int Module::get_width(Archi *archi)
{
    return this->irl_set[get_y_irl(this->y, archi)][get_x_irl(this->x, archi)][this->idx_REALI_selected[get_y_irl(this->y, archi)][get_x_irl(this->x, archi)]]->w;
}
int Module::get_height(Archi *archi)
{
    return this->irl_set[get_y_irl(this->y, archi)][get_x_irl(this->x, archi)][this->idx_REALI_selected[get_y_irl(this->y, archi)][get_x_irl(this->x, archi)]]->h;
}

int Module::get_width_format(int x_, Archi *archi)
{
    return this->irl_set_format[get_x_irl(x_, archi)][0]->w;
}
int Module::get_height_format(Archi *archi)
{
    return this->irl_set_format[get_x_irl(this->x, archi)][0]->h;
}

void Module::random_realization(Archi *archi)
{
    // INDEX_IRL *idx_ril = get_irl_idx(this->x, this->y, archi);
    // int x_irl = idx_ril->x_irl;
    int x_irl = get_x_irl(this->x, archi);
    // int y_irl = idx_ril->y_irl;

    for (int i = 0; i < 3; i++)
    {
        int irl_size = this->irl_set[i][x_irl].size();
        if (irl_size == 1)
            return;
        int cur_reali_idx = this->idx_REALI_selected[i][x_irl];
        int new_reali_idx;
        do
        {
            new_reali_idx = rand() % irl_size;
        } while (new_reali_idx == cur_reali_idx);

        this->idx_REALI_selected[i][x_irl] = new_reali_idx;
    }

    // int irl_size = this->irl_set[y_irl][x_irl].size();
    // if (irl_size == 1)
    //     return;
    // int cur_reali_idx = this->idx_REALI_selected[y_irl][x_irl];
    // int new_reali_idx;
    // do
    // {
    //     new_reali_idx = rand() % irl_size;
    // } while (new_reali_idx == cur_reali_idx);

    // this->idx_REALI_selected[y_irl][x_irl] = new_reali_idx;
}

void Module::get_3_dimens(int x_, Archi *archi, vector<Dimention *> &dimen_3)
{
    // cout << "[get_3_dimens]" << endl;
    // vector<Dimention *> vec_3dimen;
    int x_irl = get_x_irl(x_, archi);
    // cout << "x_ = " << x_ << " x_irl=" << x_irl << endl;
    for (int y_irl = 0; y_irl < 3; y_irl++)
    {

        int idx_irl = this->idx_REALI_selected[y_irl][x_irl];
        int w = this->irl_set[y_irl][x_irl][idx_irl]->w;
        int h = this->irl_set[y_irl][x_irl][idx_irl]->h;
        Dimention *d = new Dimention(w, h);

        dimen_3.push_back(d);
    }
    // return vec_3dimen;
}