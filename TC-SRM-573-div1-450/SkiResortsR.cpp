#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <queue>
#include <typeinfo>
#include <fstream>
#include <cassert>

using namespace std;
const int maxn = 52*52;
const long long  INF = 1e17;

class SkiResorts {
    public:
    int n, nodes;
    
    priority_queue<pair<long long, int> > q;
    
    long long d[maxn];
    int x[maxn], y[maxn], book[maxn], id[52][52];
    long long Dijkstra(vector<string> road, vector<int> altitude)
    {
//        for(int i=0;i<n;i++) 
//            g[0].push_back(edge(id(0, i), abs(altitude[0] - altitude[i])));
//        
        for(int i=0;i<maxn;i++) d[i] = INF , book[i] = 0;
        for(int i=0;i<n;i++) d[id[0][i]] = abs(altitude[0] - altitude[i]);
        
        for(int i=0;i<nodes;i++)
        {
            long long res = INF; int who = -1;
            for(int j=0;j<nodes;j++) if(book[j] == 0 && d[j] < res) res = d[j], who = j;
            if(who < 0) break;
            book[who] = 1;
            
            for(int j=0;j<nodes;j++) 
                if(d[j] > d[who] && road[x[who]][x[j]] == 'Y' && altitude[y[who]] >= altitude[y[j]])
                    d[j] = min(d[j], d[who] + abs(altitude[y[j]] - altitude[x[j]]));
        }
        
        long long res = INF;
        for(int i=0;i<n;i++) res = min(res, d[id[n-1][i]]);
        return res == INF ? -1 : res;
    }
        
    long long minCost(vector<string> road, vector<int> altitude) {
        n = road.size();
        nodes = n*n+1;
        for(int i=0;i<n;i++) for(int j=0;j<n;j++)
        {
            int to = i*n+j+1;
            x[to] = i;
            y[to] = j;
            id[i][j] = to;
        }
        return Dijkstra(road, altitude);
    }
};