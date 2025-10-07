#include <iostream>
#include <vector>

class UnionFind
{
public:
    std::vector<int> id;
    std::vector<int> size;

    UnionFind(int N)
    {
        id.resize(N);
        size.assign(N,1);

        for(int i = 0;i < N;i++)
            id[i] = i;
    }

    int root(int i)
    {
        while(id[i] != i)
        {
            id[i] = id[id[i]];
            i = id[i];
        }

        return i;
    }

    void unionSets(int p, int q)
    {
        int proot = root(p);
        int qroot = root(q);

        if(size[proot] <= size[qroot])
        {
            id[proot] = qroot;
            size[qroot] += size[proot];
        }
        else
        {
            id[qroot] = proot;
            size[proot] += size[qroot];
        }
    }

    bool connected(int p, int q)
    {
        return root(p) == root(q);
    }
};