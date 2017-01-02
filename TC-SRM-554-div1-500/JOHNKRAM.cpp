#include<bits/stdc++.h>
using namespace std;
int n,i,j;
int a[50],b[50];
vector<int> ans;
bool cmp(int x,int y)//height[x]为第一关键字，x为第二关键字 
{
    if(a[x]==a[y])return x<y;
    return a[x]<a[y];
}
class TheBrickTowerMediumDivOne
{
    public:
        vector <int> find(vector <int> heights)
        {
            n=heights.size();
            for(i=1;i<=n;i++)a[i]=heights[i-1];//转成全局数组 
            for(i=1,a[j=0]=1000000000;i<=n;i++)b[a[i]>a[b[j]]?n+1+j-i:++j]=i;//按顺序插入 
            sort(b+j+1,b+n+1,cmp);//排序 
            for(i=1;i<=n;i++)ans.push_back(b[i]-1);//转成vector 
            return ans;
        }
};