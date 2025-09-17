#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int,int> PII;

const int INF = INT_MAX;

void dijkstra(int n,int start,vector<vector<PII>>& graph,vector<int>& dist) 
{
    dist.assign(n,INF);     
    vector<bool> visited(n,false);
    priority_queue<PII,vector<PII>,greater<>> pq;

    dist[start] = 0;
    pq.push({0,start}); 

    while(!pq.empty()) 
    {
        auto [d,u] = pq.top(); pq.pop();
        if(visited[u]) continue;
        visited[u] = true;

        for(auto [v,w]: graph[u])
        {
            if(dist[u]+w < dist[v]) 
            {
                dist[v] = dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
}
