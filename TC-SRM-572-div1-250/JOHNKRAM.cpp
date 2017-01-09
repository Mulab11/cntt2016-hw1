#include<bits/stdc++.h>
using namespace std;
int n,i,j,a[26],s,m,ans;
class NewArenaPassword
{
    public:
        int minChange(string oldPassword, int K)
        {
            n=oldPassword.size();
            for(i=0;i+K<n;i++)//枚举每一位 
            {
                memset(a,0,sizeof(a));
                s=m=0;
                for(j=i;j<n;j+=n-K)//求字母总数及出现最多的字母出现次数 
                {
                    s++;
                    m=max(m,++a[oldPassword[j]-'a']);
                }
                ans+=s-m;//计算答案 
            }
            return ans;
        }
};