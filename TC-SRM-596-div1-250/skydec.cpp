#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
class IncrementAndDoubling{
public:
    int getMin(vector <int> a){
        int ans=0;
        int h=0;
        rep(i,0,a.size()-1)if(a[i]){
            int x=a[i];
            int d=-1;
            while(x){
                if(x&1)ans++;
                d++;x/=2;
            }
            if(d>h)h=d;
        }
        return ans+h;
    }
};