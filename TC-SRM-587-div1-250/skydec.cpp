#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
class JumpFurther{
public:
    int furthest(int N, int badStep){
        int ans=0;
        rep(i,1,N){
            ans+=i;
            if(ans==badStep)ans--;
        }
        return ans;
    }
};