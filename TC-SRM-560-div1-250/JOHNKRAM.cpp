#include<bits/stdc++.h>
using namespace std;
int a[100];
class TomekPhone
{
    public:
        int minKeystrokes(vector <int> frequencies, vector <int> keySizes)
        {
            int n=frequencies.size(),m=keySizes.size(),N,i,j,ans=0;
            for(i=N=0;i<m;i++)
            {
                a[keySizes[i]+1]--;//差分优化区间加 
                N+=keySizes[i];
            }
            if(N<n)return -1;//判断是否够数 
            for(a[1]=m,i=2;i<51;i++)a[i]+=a[i-1];//计算每种编号出现次数 
            sort(frequencies.begin(),frequencies.end(),greater<int>());//排序 
            for(i=0,j=1;i<n;i++)for(;;j++)if(a[j]--)//求出最小编号 
            {
                ans+=j*frequencies[i];//计算答案 
                break;
            }
            return ans;
        }
};