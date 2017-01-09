#include<bits/stdc++.h>
using namespace std;
int x,y,n,i,j,f[26],g[26],ans=1000000000;
bool b[26];
void work()//求最小代价 
{
    int i,j,k,l;
    for(i=j=l=0,k=-1000000000;i<26;i++)if(g[i])
    {
        if(g[i]<j)return;//无合法解 
        if(g[i]>j)l+=max(g[i]-'a'-i,0)*x+max(k+'a'-j,0)*y;//前一段已结束，加上前一段的末尾和当前段的开头 
        j=g[k=i];
    }
    ans=min(ans,l+=max(k+'a'-j,0)*y);//加上最后一段的末尾 
}
class NextAndPrev
{
    public:
        int getMinimum(int nextCost, int prevCost, string start, string goal)
        {
            if(start==goal)return 0;
            x=nextCost;
            y=prevCost;
            n=start.size();
            for(i=0;i<n;i++)//求每种字母最终变成哪种字母 
            {
                if(f[start[i]-'a']&&f[start[i]-'a']!=goal[i])return -1;
                f[start[i]-'a']=goal[i];
                b[goal[i]-'a']=1;
            }
            for(i=0;i<26;i++)if(!b[i])break;//判断goal是否包含所有字母 
            if(i==26)return -1;//无解 
            for(i=0;i<26;i++)//枚举间隔 
            {
                for(j=0;j<26;j++)if(f[j])g[(i+j)%26]=f[j]+i;
                else g[(i+j)%26]=0;
                work();//不移动 
                for(j=0;j<26;j++)if(g[j])g[j]+=26;
                work();//目标整体右移26 
                for(j=0;j<26;j++)if(g[j])g[j]-=52;
                work();//目标整体左移26 
            }
            if(ans==1000000000)ans=-1;
            return ans;
        }
};