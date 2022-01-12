#include "sa.h"

// row by row
void build_iniTree_2(vector<NODE> &tree, int num_module, int &root_idx, vector<Module *> vec_mod)
{
    cout << "build tree 2 start" << endl;
    int num_mod_per_row = sqrt(num_module);
    tree = vector<NODE>(num_module);
    vector<int> OCCUPIED(num_module, 0);
    queue<int> BF;

    root_idx = rand() % num_module;
    tree[root_idx].parent = nptr;
    BF.push(root_idx);
    OCCUPIED[root_idx] = 1;

    int left = num_module - 1; // root is taken

    while (!BF.empty())
    {
        int parent = BF.front();
        int head = parent;
        BF.pop();

        int Lchild = nptr, Rchild = nptr;
        cout << " [num_mod_per_row] = " << num_mod_per_row << endl;
        for (int i = 0; i < num_mod_per_row; i++)
        {
            if (left == 0)
                break;
            if (left > 0)
                do
                {
                    Lchild = rand() % num_module;
                } while (OCCUPIED[Lchild]);
            tree[parent].Lchild = Lchild;
            BF.push(Lchild);
            OCCUPIED[Lchild] = 1;
            left--;
            cout << "left: " << left << endl;
            tree[parent].Lchild = Lchild;
            tree[Lchild].Rchild = nptr;
            // tree[parent].Lchild = Lchild;
            // if (Lchild != nptr)
            tree[Lchild].parent = parent;
            if (!((int)i == num_mod_per_row - 1))
            {
                parent = BF.front();
                BF.pop();
            }
            else // last left child
            {
                tree[Lchild].Lchild = nptr;
                BF.pop();
            }
            if (left == 0)
                break;
        }
        // if (left > 0)
        //  BF.push(head);
        // if (left > 0)
        //   BF.pop();
        parent = head;
        // BF.push(head);
        if (left > 0)
        {
            do
            {
                Rchild = rand() % num_module;
            } while (OCCUPIED[Rchild]);
            tree[parent].Rchild = Rchild;
            BF.push(Rchild);
            OCCUPIED[Rchild] = 1;
            left--;
            cout << "left: " << left << endl;
            // tree[parent].Rchild = Rchild;
            // if (Rchild != nptr)
            tree[Rchild].parent = parent;
        }
        // if (left == 0)
        //

        tree[parent].Rchild = Rchild;
        tree[parent].Lchild = Lchild;
    }
    // tree[parent].Rchild = Rchild;
    // if (Rchild != nptr)
    //   tree[Rchild].parent = parent;
    cout << "build tree 2 end" << endl;
}

void build_iniTree(vector<NODE> &tree, int num_module, int &root_idx, vector<Module *> vec_mod)
{

    tree = vector<NODE>(num_module);
    vector<int> OCCUPIED(num_module, 0);
    queue<int> BF;

    root_idx = rand() % num_module;
    tree[root_idx].parent = nptr;
    BF.push(root_idx);
    OCCUPIED[root_idx] = 1;

    int left = num_module - 1;

    while (!BF.empty())
    {
        int parent = BF.front();
        BF.pop();

        int Lchild = nptr, Rchild = nptr;
        if (left > 0)
        {
            do
            {
                Lchild = rand() % num_module;
            } while (OCCUPIED[Lchild]);
            tree[parent].Lchild = Lchild;
            BF.push(Lchild);
            OCCUPIED[Lchild] = 1;
            left--;

            if (left > 0)
            {
                do
                {
                    Rchild = rand() % num_module;
                } while (OCCUPIED[Rchild]);
                tree[parent].Rchild = Rchild;
                BF.push(Rchild);
                OCCUPIED[Rchild] = 1;
                left--;
            }
        }
        tree[parent].Lchild = Lchild;
        tree[parent].Rchild = Rchild;
        if (Lchild != nptr)
            tree[Lchild].parent = parent;
        if (Rchild != nptr)
            tree[Rchild].parent = parent;
    }
}