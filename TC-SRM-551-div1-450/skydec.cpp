#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<string>
#include<ctime>
#include<set>
#include<map>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int N=55;
int n;
int w[N][N];
class ColorfulWolves{
    public:
    int getmin(vector<string> colormap){
        n=colormap.size();
        //显然(i,j)的代价是i可以选择的最小的颜色是j
        //于是我们可以提前计算好代价
        rep(i,1,n)rep(j,1,n){
            //显然如果color[i][j]='N'的话，由于我们只能将'Y'变成'N'，所以一定会不合法，边权设为inf
            if(colormap[i-1][j-1]=='N')w[i][j]=1e9;
            //统计有几个数需要变'N'
            rep(k,1,j-1)if(colormap[i-1][k-1]=='Y')w[i][j]++;
        }
        //显然当前的状态只跟当前所在的颜色有关，而且如果走成环肯定是不优的
        //于是我们相当于对预处理好的代价跑最短路
        //直接floyd即可
        rep(k,1,n)rep(i,1,n)rep(j,1,n)
        w[i][j]=min(w[i][j],w[i][k]+w[k][j]);
        if(w[1][n]>10000000)return -1;
        return w[1][n];
    }
};

