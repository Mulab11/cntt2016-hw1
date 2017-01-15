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
const int N=55;
int a[N],n,ans[N];
bool use[N];
int c[N];
int calc(){
    //按照题意计算贡献
    int ret=0;
    rep(i,1,n-1)ret+=max(a[c[i]],a[c[i+1]]);
    return ret;
}
//按值的大小排序
inline bool cmp(const int &x,const int &y){return a[x]<a[y];}
vector<int> Main(){
    rep(i,1,n){
        //因为要求字典序最小，考虑逐位确定的算法
        int micost=1e9;
        int gt=0;
        rep(j,1,n)if(!use[j]){
            rep(k,1,i-1)c[k]=ans[k];
            c[i]=j;
            int dd=i;
            rep(k,1,n)if(!use[k])if(k!=j)c[++dd]=k;
            //显然后面的数有序是最优的
            //直观的证明方法：显然贡献有n-1段，排序后第i小的都贡献1次(i>1)
            //显然第2小的不可能贡献2次以上，第3小的不可能贡献3次以上，以此类推
            sort(c+i+1,c+n+1,cmp);
            
            int rc=calc();
            //注意是小于，不是小于等于
            if(rc<micost){
                micost=rc;
                gt=j;
            }
        }
        
        ans[i]=gt;
        use[gt]=1;
    }
    //输出答案
    vector<int> res;res.clear();
    rep(i,1,n){
        res.pb(ans[i]-1);
    }
    rep(i,0,res.size()-1)printf("%d ",res[i]);printf("\n");
    return res;
}
class TheBrickTowerMediumDivOne{
    public:
    vector<int> find(vector<int> a){
        //初始化
        n=a.size();
        rep(i,1,n)::a[i]=a[i-1];
        return Main();
    }
};