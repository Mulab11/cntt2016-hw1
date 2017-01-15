#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
typedef double DB;
class TriangleXor{
public:
    int theArea(int w){
        double ans=0;
        rep(i,0,w){
            double h=1-(i*1./(w+i));
            double res=(w-i+1)*1.*w*h/2;
            if(i)res*=2;
            if(i&1)ans-=res;
            else ans+=res;
        }
        return (int)ans;
    }
}gt;