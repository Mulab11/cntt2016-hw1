#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
char dj[305];int c[3];
class LittleElephantAndBalls{
public:
    int getNumber(string S){
        dj['R']=0;dj['G']=1;dj['B']=2;

        int ans=0;
        rep(i,0,S.size()-1){
            rep(j,0,2)ans+=min(c[j],2);
            c[dj[S[i]]]++;
        }
        return ans;
    }
};