#include "irl.h"

int get_x_irl(int x, Archi *archi)
{
    int S = archi->S;
    int D = archi->D;

    int x_irl;

    if (x <= S)
        x_irl = x;
    else if (S >= D)
        x_irl = x % D > 0 ? S - (D - x % D) : S;
    else
        x_irl = x % D;

    if (x_irl < 0)
    {
        cout << "error! x_irl < 0" << endl;
    }

    return x_irl;
}

int get_y_irl(int y, Archi *archi)
{
    return y % 3;
}

INDEX_IRL *get_irl_idx(int x, int y, Archi *archi)
{
    int x_irl = get_x_irl(x, archi);
    int y_irl = get_y_irl(y, archi);

    // cout << "get_irl_idx: " << x_irl << ", " << y_irl << endl;
    return new INDEX_IRL(x_irl, y_irl);
}

pair<int, int> get_num_clb_n_mux(int x, int y, int w, int h, Archi *archi)
{
    int num_clb_per_col = 0, num_mux_per_col = 0;
    int num_clb_per_row = 0, num_mux_per_row = 0;
    float D = (float)(archi->D), S = (float)(archi->S);
    float W = (float)w; // H = (float)h;
    float X = (float)x;

    // num_clb_per_col, num_mux_per_col
    num_clb_per_col = h;

    if (h < 3)
        num_mux_per_col = 0;
    else if (y == 0)
        num_mux_per_col = h / 3;
    else if (y == 1)
    {
        if (h < 5)
            num_mux_per_col = 0;
        else
            num_mux_per_col = (h - 2) / 3;
    }
    else if (y == 2)
    {
        if (h < 4)
            num_mux_per_col = 0;
        else
            num_mux_per_col = (h - 1) / 3;
    }

    // num_mux_per_row
    if (x <= S)
        num_mux_per_row = ceil((W - (S - X)) / D); // FLOAT
    else
        num_mux_per_row = ceil((W - (S + D - X)) / D); // FLOAT
    // num_clb_per_row
    num_clb_per_row = w - num_mux_per_row;

    // cout << "(x, y, w, h)" << x << ", " << y << ", " << w << ", " << h << endl;
    // cout << "get_num_clb_n_mux = " << num_clb_per_col * num_clb_per_row << ", " << num_mux_per_col * num_mux_per_row << endl;
    // cout << num_mux_per_col << ", " << num_mux_per_row << "=" << ceil((W - (S - X)) / D) << " = " << (W - (S - X)) / D << endl;
    return make_pair(num_clb_per_col * num_clb_per_row, num_mux_per_col * num_mux_per_row);
}

void gen_realization(Module *mod, Archi *archi, float min_aspect)
{
    int num_clb = mod->num_clb;
    int num_mux = mod->num_mux;
    // int S = archi->S;
    // int D = archi->D;

    int max_width = 0;
    // if (num_clb <= S)
    //     max_width = min(max(num_clb, num_mux == 0 ? 0 : S + 1 + num_mux * D), archi->C);
    // else
    // {
    //     float clb_dominant_solution = (float)(num_clb - S) / (float)(D - 1);
    //     max_width = min(max(num_clb + (int)ceil(clb_dominant_solution), num_mux == 0 ? 0 : S + 1 + num_mux * D), archi->C);
    // }
    max_width = archi->C;

    int max_height = min(max(num_clb, 3 * num_mux + 2), archi->R);
    int min_height = num_mux == 0 ? 1 : 3; // todo

    // cout << mod->name << " " << mod->num_clb << " " << mod->num_mux << " "
    //      << " max_width, max_height: " << max_width << " " << max_height << endl;
    for (size_t i = 0; i < 3; i++)
    {
        for (int j = 0; j < archi->w_irl; j++)
        {
            // cout << mod->name << " " << i << " " << j;
            int temp_width = 1;
            for (int k = max_height; k >= min_height; k--)
            {
                // cout << " k=" << k << " width=" << temp_width << " (max_width=" << max_width << endl;
                pair<int, int> num_clb_n_mux = get_num_clb_n_mux(j, i, temp_width, k, archi);
                while (num_clb_n_mux.first < num_clb || num_clb_n_mux.second < num_mux)
                {
                    // cout << "temp_width: " << temp_width << "(#clb, #mux): " << num_clb_n_mux.first << "," << num_clb_n_mux.second << endl;
                    num_clb_n_mux = get_num_clb_n_mux(j, i, ++temp_width, k, archi);
                    if (temp_width == max_width)
                        break;
                }
                if (temp_width == max_width)
                    break;
                // cout << "(#clb, #mux): " << num_clb_n_mux.first << ", " << num_clb_n_mux.second << endl;
                REALI *new_realization = new REALI(temp_width, k);
                if (new_realization->aspect < min_aspect)
                    continue;
                //  cout << "hello"
                //<< " " << mod->irl_set[i][j].size() << endl;
                if (mod->irl_set[i][j].size() > 0)
                {
                    // cout << "hello a" << endl;
                    REALI *temp_reali_last = mod->irl_set[i][j].back();
                    // cout << "hello b" << endl;
                    // cout << "temp_reali_last: " << temp_reali_last->w << endl;
                    if (temp_reali_last->w == temp_width)
                        mod->irl_set[i][j].back() = new_realization;
                    else
                        mod->irl_set[i][j].push_back(new_realization);
                }
                else
                    mod->irl_set[i][j].push_back(new_realization);
            }

            /* code */
        }
    }
}

void gen_realization_format(Module *mod, Archi *archi, float min_aspect)
{
    int num_clb = mod->num_clb;
    int num_mux = mod->num_mux;
    // int S = archi->S;
    // int D = archi->D;

    // int max_width = 0;
    // if (num_clb <= S)
    //     max_width = min(max(num_clb, num_mux == 0 ? 0 : S + 1 + num_mux * D), archi->C);
    // else
    // {
    //     float clb_dominant_solution = (float)(num_clb - S) / (float)(D - 1);
    //     max_width = min(max(num_clb + (int)ceil(clb_dominant_solution), num_mux == 0 ? 0 : S + 1 + num_mux * D), archi->C);
    // }
    int max_width = archi->C;
    if (max_width % 5 != 0)
        max_width = max_width - max_width % 5;

    int max_height = min(max(num_clb, 3 * num_mux), archi->R);
    if (max_height % 3 != 0)
        max_height += (3 - max_height % 3);
    int min_height = 3;

    cout << "max_height: " << max_height << ", min_height" << min_height << ", max_width: " << max_width << endl;

    for (int j = 0; j < archi->w_irl; j++)
    {
        // cout << mod->name << " " << i << " " << j;
        int temp_width = 5;
        for (int k = max_height; k >= min_height; k -= 3)
        {
            // cout << " k=" << k << " width=" << temp_width << " (max_width=" << max_width << endl;
            pair<int, int> num_clb_n_mux = get_num_clb_n_mux(j, 0, temp_width, k, archi);
            while (num_clb_n_mux.first < num_clb || num_clb_n_mux.second < num_mux)
            {
                // cout << "temp_width: " << temp_width << "(#clb, #mux): " << num_clb_n_mux.first << "," << num_clb_n_mux.second << endl;
                temp_width += 5;
                num_clb_n_mux = get_num_clb_n_mux(j, 0, temp_width, k, archi);
                if (temp_width == max_width)
                    break;
            }
            if (temp_width == max_width)
                break;
            // cout << "(#clb, #mux): " << num_clb_n_mux.first << ", " << num_clb_n_mux.second << endl;
            REALI *new_realization = new REALI(temp_width, k);
            // if (new_realization->aspect < min_aspect)
            //     continue;

            if (mod->irl_set_format[j].size() > 0)
            {
                // cout << "hello a" << endl;
                REALI *temp_reali_last = mod->irl_set_format[j].back();
                // cout << "hello b" << endl;
                // cout << "temp_reali_last: " << temp_reali_last->w << endl;
                if (temp_reali_last->w == temp_width)
                    mod->irl_set_format[j].back() = new_realization;
                else
                    mod->irl_set_format[j].push_back(new_realization);
            }
            else
                mod->irl_set_format[j].push_back(new_realization);
        }

        /* code */
    }
}

void gen_realization_format_height3(Module *mod, Archi *archi, float min_aspect)
{
    int num_clb = mod->num_clb;
    int num_mux = mod->num_mux;
    // int S = archi->S;
    // int D = archi->D;

    // int max_width = 0;
    // if (num_clb <= S)
    //     max_width = min(max(num_clb, num_mux == 0 ? 0 : S + 1 + num_mux * D), archi->C);
    // else
    // {
    //     float clb_dominant_solution = (float)(num_clb - S) / (float)(D - 1);
    //     max_width = min(max(num_clb + (int)ceil(clb_dominant_solution), num_mux == 0 ? 0 : S + 1 + num_mux * D), archi->C);
    // }
    int max_width = archi->C;
    if (max_width % 5 != 0)
        max_width = max_width - max_width % 5;

    for (int j = 0; j < archi->w_irl; j++)
    {
        // cout << mod->name << " " << i << " " << j;
        int temp_width = 1;
        int k = 3;
        // cout << " k=" << k << " width=" << temp_width << " (max_width=" << max_width << endl;
        pair<int, int> num_clb_n_mux = get_num_clb_n_mux(j, 0, temp_width, k, archi);
        while (num_clb_n_mux.first < num_clb || num_clb_n_mux.second < num_mux)
        {
            // cout << "temp_width: " << temp_width << "(#clb, #mux): " << num_clb_n_mux.first << "," << num_clb_n_mux.second << endl;
            temp_width += 1;
            num_clb_n_mux = get_num_clb_n_mux(j, 0, temp_width, k, archi);
            if (temp_width == max_width)
            {
                cout << "error! not enough width for this module" << endl;
                break;
            }
        }
        if (temp_width == max_width)
            break;
        // cout << "(#clb, #mux): " << num_clb_n_mux.first << ", " << num_clb_n_mux.second << endl;
        REALI *new_realization = new REALI(temp_width + 2, k);
        mod->w = temp_width;
        mod->h = k;
        // if (new_realization->aspect < min_aspect)
        //     continue;

        mod->irl_set_format[j].push_back(new_realization);
    }

    /* code */
}

void init_module_irls_format(vector<Module *> vec_mod, Archi *archi, float min_aspect)
{
    // create empty irl_set in each Module
    for (size_t i = 0; i < vec_mod.size(); i++)
    {
        Module *temp_mod = vec_mod[i];
        vector<int> irl_idx(archi->w_irl, 0);

        for (int k = 0; k < archi->w_irl; k++)
        {
            vector<REALI *> irl_row;
            // vector<REALI *> empty_irl;
            temp_mod->irl_set_format.push_back(irl_row);
            temp_mod->idx_REALI_selected_format.push_back(0);
        }

        // temp_mod->irl_set.push_back(irl_row);
    }

    for (size_t i = 0; i < vec_mod.size(); i++)
    {
        Module *temp_mod = vec_mod[i];
        // gen_realization_format(temp_mod, archi, min_aspect);
        gen_realization_format_height3(temp_mod, archi, min_aspect);
    }

    int total_area_max = 0;
    int total_area_min = 0;
    int sub_max_area = 0;
    int sub_min_area = 99999999;
    int sub_area = 0;
    for (size_t i = 0; i < vec_mod.size(); i++)
    {
        sub_max_area = 0;
        // cout << "Mod: " << vec_mod[i]->name << "(#clb, # mux): " << vec_mod[i]->num_clb << ", " << vec_mod[i]->num_mux << endl;
        for (size_t j = 0; j < vec_mod[i]->irl_set_format.size(); j++)
        {

            // cout << "x_irl: " << j << ": ";
            for (size_t k = 0; k < vec_mod[i]->irl_set_format[j].size(); k++)
            {

                REALI *temp_reali = vec_mod[i]->irl_set_format[j][k];
                // cout << "(" << temp_reali->w << ", " << temp_reali->h << ") ";
                sub_area = temp_reali->w * temp_reali->h;
                if (sub_area > sub_max_area)
                    sub_max_area = sub_area;
                if (sub_area < sub_min_area)
                    sub_min_area = sub_area;
            }
            total_area_max += sub_max_area;
            total_area_min += sub_min_area;
            // cout << endl;
        }
    }
    // cout << "total_area_max_required= " << total_area_max << " ";
    // cout << "total_area_min_required= " << total_area_min << " ";
    // cout << "total available area: " << archi->R * archi->C << " ";
    // cout << "min white sapce ratio: " << ((double)(archi->R * archi->C - total_area_min) / (double)(archi->R * archi->C)) << endl;
}
