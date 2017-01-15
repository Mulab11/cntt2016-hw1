#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<string>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=305;
int a[N];int n,m;
int f[N][2];
int bit(int x,int y){return (x&(1<<y))>0;}
int w(int l,int r,int st,int vv){
    int ans=0;
    rep(i,l,r)ans+=(bit(st,i-l)^vv^a[i]);
    return ans;
}
int Main(){
    if(m<=17){
        int ret=1e9;
        rep(st,0,(1<<m)-1){
            f[1][0]=w(1,m,st,0);
            f[1][1]=w(1,m,st,1)+1;
            rep(i,2,n/m){
                int v0=w((i-1)*m+1,i*m,st,0);
                int v1=w((i-1)*m+1,i*m,st,1);
                f[i][1]=min(f[i-1][0]+2,f[i-1][1])+v1;
                f[i][0]=min(f[i-1][0],f[i-1][1])+v0;
            }
            int ans=min(f[n/m][0],f[n/m][1]);
            if(n%m){
                ans+=w(n-(n%m)+1,n,st,0);
            }
            if(ans<ret)ret=ans;
        }
        return ret;
    }
    else{
        int rev[22];
        int S=n/m;int ret=1e9;
        rep(i,0,(1<<S)-1){
            int ans=0;
            rep(j,1,S)if((1<<(j-1))&i){
                if(j==1)ans++;
                else if(!((1<<(j-2))&i))ans+=2;
                rev[j]=1;
            }
            else rev[j]=0;
            rep(j,1,m){
                int rp=0;
                rep(k,1,S)rp+=(a[m*(k-1)+j]^rev[k]);
                if((n%m)>=j)rp+=(a[m*S+j]);
                ans+=min(rp,S+((n%m)>=j)-rp);
            }
            if(ans<ret)ret=ans;
        }
        return ret;
    }
}
class FlippingBitsDiv1{
    public:
    int getmin(vector<string> S, int M){
        m=M;
        rep(i,0,S.size()-1)rep(j,0,S[i].size()-1)a[++n]=S[i][j]-'0';
        return Main();
    }
}gt;