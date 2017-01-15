#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=305;
const int P=1000000007;
inline void add(int &a,int b){a+=b;if(a>=P)a-=P;}
inline void dec(int &a,int b){a-=b;if(a<0)a+=P;}
int n,m;
int l[N],r[N];
int f[N][N];
int Main(){
    rep(i,1,m){
        l[i]++;r[i]++;
    }
    f[1][0]=1;
    rep(i,1,n)rep(j,0,n)if(f[i][j]){
        //f[i][j]表示dp了[1..i-1]，要求[i..j]<=1的方案数
        
        //第i格上没有狼
        //更新下j
        if(j>=i+1)add(f[i+1][j],f[i][j]);
        else add(f[i+1][0],f[i][j]);

        //第i格上有狼
        //d表示新的i
        //因为i上放了狼，又因为[i,j]<=1，所以新的i=j+1
        int d=j+1;
        if(j==0)d=i+1;
        int ma=0;
        //统计最大的j使得[d,j]<=1
        rep(k,1,m)if(l[k]<=i)ma=max(ma,r[k]);
        if(ma<d)ma=0;
        add(f[d][ma],f[i][j]);
    }
    return f[n+1][0];
}
class WolfInZooDivOne{
public:
    int count(int N, vector <string> L, vector <string> R){
        //预处理
        //将vector<string>变成vector<int>
        ::n=N;
        int now=0;m=0;
        rep(i,0,L.size()-1)rep(j,0,L[i].size()-1){
            if(L[i][j]==' '){
                l[++m]=now;
                now=0;
            }
            else{
                now=now*10+(L[i][j]-'0');
            }
        }
        l[++m]=now;
        now=0;m=0;
        rep(i,0,R.size()-1)rep(j,0,R[i].size()-1){
            if(R[i][j]==' '){
                r[++m]=now;
                now=0;
            }
            else{
                now=now*10+(R[i][j]-'0');
            }
        }
        r[++m]=now;
        return Main();
    }
};


