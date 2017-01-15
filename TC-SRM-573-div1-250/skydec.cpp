#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int a[N],n;
bool vis[N];
int Main(int S){
    //从小到大排序
    sort(a+1,a+1+n);
    for(int i=1;i<=n;i+=3){
        //枚举取光[i,n]
        memset(vis,0,sizeof vis);
        bool flag=1;
        rep(j,i,n)if(!vis[j]){
            //枚举最小的数为j
            int gt=0;
            rep(k,j+1,n)if(!vis[k])if(a[j]+a[k]>S){
                //枚举最大的数，用gt存下来
                gt=k;
                break;
            }
            if(!gt){flag=0;break;}
            vis[j]=1;
            vis[gt]=1;
            gt=0;
            //枚举中间的数，也就是[j+1,n]里第一个未使用的数
            rep(k,j+1,n)if(!vis[k]){
                gt=k;break;
            }
            if(!gt){flag=0;break;}
            vis[gt]=1;
        }
        //如果能找到的话，说明后面的都可以组成，返回(n-i+1)/3
        if(flag)return (n-i+1)/3;
    }
    return 0;
}
class TeamContest{
public:
    int worstRank(vector<int> s){
        //预处理
        rep(i,3,s.size()-1)a[++n]=s[i];
        return Main(max(max(s[0],s[1]),s[2])+min(min(s[0],s[1]),s[2]))+1;
    }
};




