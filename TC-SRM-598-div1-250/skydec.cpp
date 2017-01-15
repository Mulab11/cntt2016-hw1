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
int n,a[N];
int Main(){
    int ans=n+5;
    a[0]=100;
    rep(i,0,n/3)if(a[i*3]==100){
        int ret=i;

        int l=i*3+1;
        per(j,n,i*3+1)if(j>=l){
            ret++;
            if(a[j]+a[l]<=300)l++;
        }
        ans=min(ans,ret);
    }
    return ans;
}
class BinPacking{
public:
    int minBins(vector <int> item){
        n=item.size();
        rep(i,1,n)a[i]=item[i-1];
        sort(a+1,a+1+n);
        return Main();
    }
};