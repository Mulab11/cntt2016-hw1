#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
const int P=1000000007;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int a[N][N],n;
int num[N<<1];
int q[N<<1];
void dfs(int x){
    //dfs求出x的联通块
    if(num[x]>=0)return;
    num[x]=0;
    q[++q[0]]=x;
    if(x<=n){
        rep(i,1,n)if(a[x][i]>=0)dfs(i+n);
    }
    else{
        rep(i,1,n)if(a[i][x-n]>=0)dfs(i);
    }
}
int kuo(int x,int xia){
    //xia表示下界
    //用类似dfs的方法，判断扩展是否合法
    if(num[x]<0)return 0;
    if(x<=n&&num[x]<xia)return 0;
    if(x<=n){
        rep(i,1,n)if(a[x][i]>=0){
            if(num[i+n]==-1){
                num[i+n]=a[x][i]-num[x];
                if(!kuo(i+n,xia))return 0;
            }
            else if(num[i+n]+num[x]!=a[x][i])return 0;
        }
    }
    else{
        rep(i,1,n)if(a[i][x-n]>=0){
            if(num[i]==-1){
                num[i]=a[i][x-n]-num[x];
                if(!kuo(i,xia))return 0;
            }
            else if(num[i]!=a[i][x-n]-num[x])return 0;
        }
    }
    return 1;
}
int calc1(){
    //下界是0的情况
    memset(num,-1,sizeof num);

    int ans=1;
    rep(i,1,n*2)if(num[i]==-1){
        q[0]=0;
        dfs(i);
        int cnt=0;
        rep(v1,0,9){
            rep(j,1,q[0])num[q[j]]=-1;
            num[q[1]]=v1;
            if(kuo(q[1],0))++cnt;
        }
        ans=ans*1ll*cnt%P;
        rep(j,1,q[0])num[q[j]]=0;
    }
    return ans;
}
int calc2(){
    //下界是1的情况
    memset(num,-1,sizeof num);

    int ans=1;
    rep(i,1,n*2)if(num[i]==-1){
        q[0]=0;
        //dfs求出联通块
        dfs(i);
        int cnt=0;
        rep(v1,0,9){
            //算出每个联通块的答案，然后乘起来
            rep(j,1,q[0])num[q[j]]=-1;
            num[q[1]]=v1;
            if(kuo(q[1],1))++cnt;
        }
        ans=ans*1ll*cnt%P;
        rep(j,1,q[0])num[q[j]]=0;
    }
    return ans;
}
int Main(){
    //考虑容斥，答案是calc1()-calc2()
    int ans=calc1();
    dec(ans,calc2());
    return ans;
}
class EqualSums{
public:
    int count(vector <string> board){
        //预处理
        n=board.size();
        rep(i,1,n)rep(j,1,n){
            if(board[i-1][j-1]=='-')a[i][j]=-1;
            else a[i][j]=board[i-1][j-1]-'0';
        }
        return Main();
    }
}gt;



