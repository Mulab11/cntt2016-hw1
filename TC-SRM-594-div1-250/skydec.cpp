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
LL a[N],b[N];
int n,m;
int f[N][N];
int Get(int A,int B){
    memset(f,0,sizeof f);
    rep(i,0,n)rep(j,0,m){
        f[i+1][j]=max(f[i][j],f[i+1][j]);
        f[i][j+1]=max(f[i][j],f[i][j+1]);

        if(a[i+1]*A==b[j+1]*B)f[i+1][j+1]=max(f[i+1][j+1],f[i][j]+1);
    }
    return f[n][m];
}
int Main(){
    int ans=n+m;
    rep(i,1,n)rep(j,1,m)ans=min(ans,n+m-Get(b[j],a[i]));
    return ans;
}
class AstronomicalRecords{
public:
    int minimalPlanets(vector <int> A, vector <int> B){
        n=A.size();m=B.size();
        rep(i,1,n)a[i]=A[i-1];
        rep(i,1,m)b[i]=B[i-1];
        return Main();
    }
};