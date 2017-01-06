#include<bits/stdc++.h>
using namespace std;
#define MAXN 105
int h[MAXN],ne[MAXN],p[MAXN],a[MAXN],d[MAXN],f[MAXN],s[MAXN],m1[MAXN],m2[MAXN];
bool dfs(int x)//判断是否合法 
{
    int i=h[x],j=0;
    m1[x]=MAXN;//子树内孩子数<2的结点深度最小值 
    m2[x]=-MAXN;//子树内孩子数<2的结点深度最大值 
    for(;i;i=ne[i])if(p[i]!=f[x])
    {
        j++;
        d[p[i]]=d[x]+1;
        f[p[i]]=x;
        if(!dfs(p[i]))return 0;
        m1[x]=min(m1[x],m1[p[i]]);
        m2[x]=max(m2[x],m2[p[i]]);
    }
    if(j<2)
    {
        m1[x]=min(m1[x],d[x]);
        m2[x]=max(m2[x],d[x]);
    }
    if(m2[x]>m1[x]+1)return 0;//判断是否平衡 
    if(m1[x]!=m2[x])s[d[x]]++;//统计不平衡点数 
    if(s[d[x]]>1)return 0;//判断一层是否有多个不平衡点 
    return 1;
}
class HatRack
{
    public:
        long long countWays(vector <int> knob1, vector <int> knob2)
        {
            int n=knob1.size()+1,i,j,m=0;
            if(n<=2)return n;
            long long ans=0,x;
            for(i=0;i+1<n;i++)
            {
                p[++m]=knob2[i];
                ne[m]=h[knob1[i]];
                h[knob1[i]]=m;
                p[++m]=knob1[i];
                ne[m]=h[knob2[i]];
                h[knob2[i]]=m;
                a[knob1[i]]++;
                a[knob2[i]]++;
            }
            for(i=1;i<=n;i++)if(a[i]>3)break;//判断是否是二叉树 
            if(i<=n)return 0;
            for(i=1,j=0;i<=n;i++)if(a[i]==2)j++;
            if(j>2)return 0;//判断是否是二叉树 
            for(i=1;i<=n;i++)if(a[i]==2)//根的度为2 
            {
                memset(s,0,sizeof(s));
                f[i]=d[i]=0;
                if(dfs(i))//判断是否是完全二叉树 
                {
                    for(j=x=1;j<=n;j++)if(m1[j]==m2[j]&&a[j]-(j!=i))x<<=1;//计算有多少个点可以交换左右子树 
                    ans+=x;//计算答案 
                }
            }
            return ans;
        }
};