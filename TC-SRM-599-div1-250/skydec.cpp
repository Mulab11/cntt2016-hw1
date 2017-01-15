#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
class BigFatInteger{
public:
    int minOperations(int A, int B){
        int ans=0;
        int d=0;
        rep(i,2,A)if(A%i==0){
            ans++;
            int v=0;
            while(A%i==0){A/=i;v++;}
            v*=B;
            int g=0;
            int v2=v;
            while(v!=1){
                g++;v/=2;
            }
            if((1<<g)<v2)g++;
            d=max(d,g);
        }
        return ans+d;
    }
};