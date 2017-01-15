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
bool f[N*2*10000];
class MayTheBestPetWin{
public:
    int calc(vector <int> A, vector <int> B){
        f[0]=1;
        int L,R;L=R=0;
        rep(i,0,A.size()-1){
            int x=A[i]+B[i];
            L+=A[i];
            R+=B[i];

            per(j,L+R,x)f[j]|=f[j-x];
        }

        int ans=(int)1e9;
        rep(i,0,L+R)if(f[i]){
            if(max(i-L,R-i)<ans)ans=max(i-L,R-i);
        }
        return ans;
    }
};