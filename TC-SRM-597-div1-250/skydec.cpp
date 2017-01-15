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
int a[N],b[N];
int n;
int cnt[35];
int Main(){
    rep(i,1,n){
        cnt[a[i]]++;cnt[b[i]]--;
    }
    rep(i,0,25)if(cnt[i]!=0)return -1;

    rep(i,1,n){
        int p=1;
        bool flag=1;
        rep(j,i,n){
            while(p<=n&&a[p]!=b[j])p++;

            if(p==n+1){flag=0;break;}
            p++;
        }
        if(flag)return i-1;
    }
    return n;
}
class LittleElephantAndString{
public:
    int getNumber(string A, string B){
        n=A.size();
        rep(i,1,n){
            a[i]=A[i-1]-'A';
            b[i]=B[i-1]-'A';
        }
        return Main();
    }
};

