//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<iostream>
#include<vector>
using namespace std;
int G[55][55];
int n,m,yM[55],chk[55];
int dfs(int u){	//匈牙利算法进行二分图匹配
    for(int v=0; v<m;v++) if(G[u][v] && !chk[v]){
        chk[v] = 1;
        if(yM[v]==-1 || dfs(yM[v])){
            yM[v] = u; return 1;
        }
    }
    return 0;
}
bool judge(int th,int tr, int bh, int br){	//排序
    return br > tr && br*th >tr*bh;
}
class PointyWizardHats{
    public : int getNumHats(vector <int> th, vector <int> tr, vector <int> bh, vector <int> br){
        n = th.size(), m = bh.size();
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(judge(th[i],tr[i],bh[j],br[j]))
                    G[i][j] =1;	//构图
        int ans=0;
        for(int i=0;i<m;i++) yM[i] = -1;
        for(int i=0;i<n;i++){	//匹配
            for(int j=0;j<m;j++) chk[j] = 0;
            ans += dfs(i);
        }
        return ans;
    }
};