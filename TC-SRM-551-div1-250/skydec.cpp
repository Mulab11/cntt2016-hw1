#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<string>
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
class ColorfulChocolates{
    public:
    int maximumSpread(string a, int m){
        n=a.size();
        int ans=0;
        rep(i,0,n-1){
            //枚举哪个巧克力的位置没变
            int lsz=0;
            int cost=0;
            per(l,i,0)if(a[l]==a[i]){
                //枚举与他同色的最左边的巧克力的位置
                lsz++;
                //累加需要交换的次数
                //由于每次交换的是相邻两个，所以当前l需要交换的次数只跟[l+1,i]的同色巧克力的个数有关
                //lsz记录个数，直接计算即可
                cost+=i-lsz+1-l;
                int rsz=0;
                int ret=cost;
                rep(r,i,n-1)if(a[r]==a[i]){
                    //枚举与他同色的最右边的巧克力的位置
                    rsz++;
                    ret+=r-(i+rsz-1);
                    //累加并更新答案
                    if(ret<=m)ans=max(ans,lsz+rsz-1);
                }
            }
        }
        return ans;
    }
};