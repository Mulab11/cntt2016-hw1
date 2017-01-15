#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int P=1000000007;
class TrafficCongestion{
public:
    int theMinCars(int n){
        ++n;
        int sum=0;
        int pre=0;
        sum=1;
        pre=1;
        rep(i,2,n){
            int now=(sum+P-pre)%P;
            now=(now*2+1)%P;
            sum=(sum+now)%P;
            pre=now;
        }
        return pre;
    }
};