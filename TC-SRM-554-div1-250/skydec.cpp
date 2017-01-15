#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
#include<string>
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
class TheBrickTowerEasyDivOne{
    public:
    int find(int rc, int rh, int bc, int bh){
        if(rh==bh){
            //讨论高度相同的情况
            if(rc==bc)return rc+bc;
            //数量一样则所有方案都可以满足
            //否则考虑短板效应
            return min(rc,bc)*2+1;
        }
        //对于用的最少的颜色用了i个的情况，有三种方案，红的+1，蓝的+1，或者都不+1
        //最后还剩下一些情况，讨论下即可
        int d=min(rc-1,bc-1);
        return d*3+2+1+(rc!=bc);
    }
};