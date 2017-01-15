#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
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
int fa[N];
int head[N],np[N],p[N],tot;
string a[N];
int n;
int gx[N],gy[N],m;
int tmp[N];
int M=0;
int id[1<<16];
int val[1<<16];
vector<int>sub[1<<16];
int t=0;
bool prefix(string s,string t){
    if(s.size()>t.size())return 0;
    rep(i,0,s.size()-1)if(s[i]!=t[i])return 0;
    return 1;
}
bool ok(int S){
    rep(i,1,m){
        if(S&(1<<(gy[i]-1)))if(!(S&(1<<(gx[i]-1))))return 0;
    }
    return 1;
}
int f[N][1<<16];
void dp(int x){
    f[x][0]=1;

    for(int u=head[x];u;u=np[u]){
        int y=p[u];
        dp(y);
        per(i,t,1){
            int ans=0;
            rep(j,0,sub[val[i]].size()-1){
                add(ans,f[x][sub[val[i]][j]]*1ll*f[y][sub[val[i]][j]^val[i]]%P);
            }
            f[x][val[i]]=ans;
        }
    }

    if(x){
        per(i,t,1){
            int ans=f[x][val[i]];
            rep(j,1,M)if(val[i]&(1<<(j-1)))if(id[val[i]^(1<<(j-1))]){
                add(ans,f[x][val[i]^(1<<(j-1))]);
            }
            f[x][val[i]]=ans;
        }
    }
}
int Main(){
    rep(i,1,m){
        tmp[++M]=gx[i];
        tmp[++M]=gy[i];
    }
    sort(tmp+1,tmp+1+M);
    M=unique(tmp+1,tmp+1+M)-tmp-1;

    rep(i,1,m){
        gx[i]=lower_bound(tmp+1,tmp+1+M,gx[i])-tmp;
        gy[i]=lower_bound(tmp+1,tmp+1+M,gy[i])-tmp;
        swap(gx[i],gy[i]);
    }

    rep(i,0,(1<<M)-1)if(ok(i)){
        val[++t]=i;
        id[i]=t;
    }

    rep(S,0,(1<<M)-1)if(id[S]){
        for(int T=S;;T=(T-1)&S)if(id[T])if(id[S^T]){
            sub[S].push_back(T);

            if(!T)break;
        }
    }

    rep(i,1,n){
        rep(j,1,n)if(prefix(a[j],a[i]))if(i^j){
            if((!fa[i])||(a[j].size()>a[fa[i]].size()))fa[i]=j;
        }
    }
    rep(i,1,n){
        ++tot;p[tot]=i;np[tot]=head[fa[i]];head[fa[i]]=tot;
    }

    dp(0);

    int ans=f[0][(1<<M)-1];
    rep(i,1,n-M)ans=ans*1ll*i%P;
    return ans;
}
class SimilarNames{
public:
    int count(vector <string> names, vector <int> info1, vector <int> info2){
        n=names.size();
        rep(i,1,n){
            a[i]=names[i-1];
        }
        m=info1.size();
        rep(i,1,m){
            gx[i]=info1[i-1]+1;
            gy[i]=info2[i-1]+1;
        }
        return Main();
    }
}gt;