#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=1505;
const int P=1000000009;
inline int Pow(int a,int b){
    int c=1;
    for(;b;b>>=1,a=a*1ll*a%P)if(b&1)c=c*1ll*a%P;
    return c;
}
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int kd(char c){
    if(c<='z'&&c>='a')return c-'a';
    return c-'A'+26;
}
int a[N],n,L;
int tmp[N],M;
int last[N];
int fac[N],inv[N];
int f[N][N];
void selfloop(int L){
    memset(last,0,sizeof last);
    per(i,n,1){
        if(n-i-1>=0)add(f[i][L],last[a[i]]*1ll*fac[n-i-1]%P);
        add(last[a[i]],f[i][L]*1ll*inv[n-i]%P);
    }
}
int Main(){
    fac[0]=1;rep(i,1,n)fac[i]=fac[i-1]*1ll*i%P;
    inv[n]=Pow(fac[n],P-2);per(i,n-1,0)inv[i]=inv[i+1]*1ll*(i+1)%P;

    rep(i,1,n)tmp[i]=a[i];
    sort(tmp+1,tmp+1+n);
    M=unique(tmp+1,tmp+1+n)-tmp-1;
    rep(i,1,n)a[i]=lower_bound(tmp+1,tmp+1+M,a[i])-tmp;

    f[n][1]=1;
    selfloop(1);

    rep(j,2,L){
        memset(last,0,sizeof last);
        int sum=0;
        per(i,n,1){
            add(last[a[i]],f[i][j-1]*1ll*inv[n-i]%P);
            add(sum,f[i][j-1]*1ll*inv[n-i]%P);

            f[i][j]=sum;
            dec(f[i][j],last[a[i]]);
            //printf("_%d %d %d\n",f[i][j],sum,last[a[i]]);
            if(n-i-1>=0)f[i][j]=f[i][j]*1ll*fac[n-i-1]%P;
        }

        selfloop(j);
        //rep(i,1,n)printf("%d ",f[i][j]);printf("\n");
    }
    int ans=0;
    rep(i,1,n){
        add(ans,(f[i][L]*1ll*fac[n-1]%P)*1ll*inv[n-i]%P);
    }
    return ans;
}
class ColorfulBuilding{
public:
    int count(vector<string>color1,vector<string>color2,int L){
        string c1="";string c2="";
        rep(i,0,color1.size()-1)c1=c1+color1[i];
        rep(i,0,color2.size()-1)c2=c2+color2[i];
        ::L=L;
        n=c1.size();
        rep(i,1,n)a[i]=kd(c1[i-1])*60+kd(c2[i-1]);
        return Main();
    }
}gt;