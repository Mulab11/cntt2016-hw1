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
const int N=16;
int n,m;
int w[N];
int k;
int numc;
int row,col;
int dx[N],dy[N];
int hh;
bool ok[1600000];
int f[1600000];
int cnt[1<<13];
int po[16];
int Main(){
    //考虑状压dp,每个帽子有三种状态:没掀开,掀开有硬币,掀开没硬币

    //预处理三进制的信息，用来加速三进制运算
    po[0]=1;
    rep(i,1,15)po[i]=po[i-1]*3;
    rep(i,0,(1<<13)-1)cnt[i]=cnt[i>>1]+(i&1);
    int up=1;
    rep(i,1,hh)up*=3;
    
    rep(i,0,(1<<hh)-1){
        //预处理下哪些状态是合法的，这里是一个二进制信息表示每个帽子下面是否有硬币
        if(cnt[i]!=numc)continue;
        int rr,cc;
        rr=cc=0;
        int val=0;
        rep(j,1,hh)if(i&(1<<(j-1))){
            //验证每行每列帽子奇偶和硬币奇偶的异或是否为0
            rr^=(1<<dx[j]);
            cc^=(1<<dy[j]);
            val+=po[j-1]*2;
        }
        else val+=po[j-1];
        if(rr==row&&cc==col)ok[val]=1;
    }
    per(i,up-1,0)if(ok[i]){
        //类似一个超集覆盖的东西，因为上面的合法性只考虑了所有帽子掀开的情况
        //对于一种所有帽子都掀开的情况，显然我们把他一些帽子盖上也是合法的
        //于是枚举哪个帽子盖上，覆盖一下，得到所有可达状态，可以大大优化运行时间
        int val=i;
        rep(j,0,hh-1){
            if(val%3){
                ok[i-(val%3)*po[j]]=1;
            }
            val/=3;
        }
    }
    //开始dp
    rep(i,0,up-1)f[i]=-(1e9);
    if(!ok[0])return -1;
    
    per(i,up-1,0){
        //实际上我们并不关心哪些硬币被掀开
        //因为玩家B要最小化硬币的面值，所以每次A即将掀开时肯定是掀开最小的
        //所以我们只关心硬币的数量,f[S]表示状态S能翻开的最多的硬币的数量
        int can=0;
        int now=i;
        int dj=0;
        rep(j,0,hh-1){
            //dj是一个二进制数，表示已知硬币的分布情况
            dj|=((now%3)==2)*(1<<j);
            //can是一个二进制数，表示还没掀开的帽子的分布情况
            can|=((now%3)==0)*(1<<j);
            now/=3;
        }
        if(!ok[i])continue;
        //如果已经掀开的帽子个数大于k，则不合法
        if(hh-cnt[can]>k)continue;
        f[i]=cnt[dj];
        rep(j,0,hh-1)if(can&(1<<j)){
            //假设我们要掀开第j个
            int ret=1e9;
            //考虑B的决策，注意这里是取min
            if(ok[i+po[j]*2])ret=min(ret,f[i+po[j]*2]);
            if(ok[i+po[j]])ret=min(ret,f[i+po[j]]);
            //注意由于初始值设成了10^9，所以要特判全都不合法的情况，这里做的时候被坑了一次
            if(ret==(1e9))continue;
            f[i]=max(f[i],ret);
        }
    }
    int res=0;
    sort(w+1,w+1+numc);
    //将w排序后取前f[0]个的和输出
    rep(i,1,f[0])res+=w[i];
    return res;
}
class MagicalHats{
    public:
    int findMaximumReward(vector<string> board,vector<int> coins,int numGuesses){
        //初始化
        numc=coins.size();
        rep(i,1,numc)w[i]=coins[i-1];
        n=board.size();
        m=board[0].size();
        rep(i,0,n-1)rep(j,0,m-1)if(board[i][j]=='H'){
            row^=(1<<i);
            col^=(1<<j);
            ++hh;
            dx[hh]=i;
            dy[hh]=j;
        }
        k=numGuesses;
        return Main();
    }
};


