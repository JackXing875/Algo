#include <iostream>
#include <vector>

using namespace std;

int m,n,solution = 0;
vector<vector<int>> grid;
vector<vector<bool>> flag;
int direction[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };

void DFS(int x,int y)
{
    if(x == m-1 && y == n-1)
    {
        solution++;
        return ;
    }
    int tx,ty;
    for(int i = 0;i < 4;i++)
    {
        tx = x + direction[i][0];
        ty = y + direction[i][1];
        if(tx < 0 || ty > m-1 || ty < 0 || ty > n-1) continue;
        if(grid[tx][ty] == 0) continue;
        if(flag[tx][ty] == true) continue;
        flag[tx][ty] = true;
        DFS(tx,ty);
        flag[tx][ty] = false;
    }
}

int main()
{
    cin >> m >> n;
    grid.assign(m,vector<int> (n,0));
    flag.assign(m,vector<bool> (n,false));
    for(int i = 0;i < m;i++)
        for(int j = 0;j < n;j++)
            cin >> grid[i][j];

    DFS(0,0);
    cout << solution << endl;
    return 0;
}