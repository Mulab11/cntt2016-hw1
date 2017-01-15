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
int s[N],t[N],n;
int num1[N];
int num2[N];
bool Main(){
    int m=0;
    rep(i,1,n)if(s[i]){
        num1[i]=++m;
    }
    int m2=0;
    rep(i,1,n)if(t[i]){
        num2[i]=++m2;
    }
    if(m!=m2)return 0;

    rep(i,1,m){
        rep(j,1,n)if(num1[j]==i)
        rep(k,1,n)if(num2[k]==i){
            if(s[j]!=t[k])return 0;
            if(s[j]==1)if(j<k)return 0;
            if(s[j]==2)if(j>k)return 0;
        }
    }
    return 1;
}
class FoxAndChess{
public:
    string ableToMove(string S, string T){
        n=S.size();
        rep(i,1,n){
            if(S[i-1]=='.')s[i]=0;
            else if(S[i-1]=='L')s[i]=1;
            else s[i]=2;

            if(T[i-1]=='.')t[i]=0;
            else if(T[i-1]=='L')t[i]=1;
            else t[i]=2;
        }
        if(Main())return "Possible";
        else return "Impossible";
    }
};