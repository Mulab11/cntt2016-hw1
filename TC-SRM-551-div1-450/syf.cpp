//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cassert>
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int N=55;
int dis[N][N];
class ColorfulWolves
{
    public:
    int getmin(vector <string> colormap){

        const int inf = 1000000;
        int n=colormap.size();
        for(int i=0;i<n;i++){
            int cur=0;
            for(int j=0;j<n;j++){
                if(colormap[i][j]=='Y')dis[i][j]=cur++;
                else dis[i][j]=inf;
            }
        }	//构图
        for(int k=0;k<n;k++)
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);	//floyed 求解最短路
        return dis[0][n-1]>=inf ?-1:dis[0][n-1];

    }
};