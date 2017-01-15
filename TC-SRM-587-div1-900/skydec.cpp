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
int a[N][N];
int n,m;
int gx[N][N];
bool check(){
    rep(i,1,n)rep(j,1,n)gx[i][j]=2;
    rep(i,1,n)gx[i][i]=0;
    rep(i,1,n)rep(j,1,n)if(i^j)rep(k,1,m)if(a[i][k]<2&&a[j][k]<2){
        if(gx[i][j]<2){
            if(gx[i][j]!=(a[i][k]^a[j][k]))return 0;
        }
        else
        gx[i][j]=(a[i][k]^a[j][k]);
    }

    rep(k,1,n)rep(i,1,n)rep(j,1,n){
        if(gx[i][k]<2&&gx[k][j]<2){
            if(gx[i][j]==2)gx[i][j]=(gx[i][k]^gx[k][j]);
            else if(gx[i][j]!=(gx[i][k]^gx[k][j]))return 0;
        }
    }
    return 1;
}
vector<string> Main(){
    if(!check()){
        vector<string> res;res.clear();
        return res;
    }
    rep(i,1,n)rep(j,1,m)if(a[i][j]==2){
        a[i][j]=0;
        if(!check())a[i][j]=1;
    }

    vector<string> res;res.clear();
    rep(i,1,n){
        string gt="";
        rep(j,1,m)gt=gt+(a[i][j]?'Z':'N');
        res.push_back(gt);
    }
    return res;
}
class ThreeColorability{
public:
    vector<string> lexSmallest(vector <string> cells){
        n=cells.size();
        m=cells[0].size();
        rep(i,1,n)rep(j,1,m)if(cells[i-1][j-1]=='?')a[i][j]=2;
        else a[i][j]=(cells[i-1][j-1]=='Z');

        return Main();
    }
};