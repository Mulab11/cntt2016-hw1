#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int ct[N][N];
int n,m;
int q[N];
bool vis[N];
bool check(int d){
    memset(vis,0,sizeof vis);
    //采用无限更新的方法
    //类似bfs
    rep(Round,1,50){
        rep(i,0,25){
            bool ok=1;
            rep(j,1,n)if(j^d){
                ok&=(vis[j]||(ct[j][i]<=ct[d][i]));
            }
            if(ok){
                //每次更新vis的值，然后用新的vis=1的值去更新别人
                rep(j,1,n)if(ct[j][i]<ct[d][i])if(!vis[j]){
                    vis[j]=1;
                }
            }
        }
    }
    //有没被更新的点的话答案就是false
    rep(i,1,n)if(i^d)if(!vis[i])return 0;
    return 1;
}
class StringGame{
public:
    vector<int> getWinningStrings(vector<string> S){
        //预处理
        n=S.size();
        m=S[0].size();
        //显然答案只跟该字母有几个有关
        rep(i,1,n)rep(j,1,m)ct[i][S[i-1][j-1]-'a']++;
        vector<int> ans;ans.clear();
        rep(i,1,n)if(check(i))ans.push_back(i-1);
        return ans;
    }
};
