#include<bits/stdc++.h>
using namespace std;
int n,m,N,i,j,k,s[50][26],a[50];
vector<int> ans;
class StringGame
{
    public:
        vector <int> getWinningStrings(vector <string> S)
        {
            n=S.size();
            m=S[0].size();
            for(i=0;i<n;i++)for(j=0;j<m;j++)s[i][S[i][j]-'a']++;//求每个串每种字母个数 
            for(i=0;i<n;i++)//枚举选择的串 
            {
                fill(a,a+n,1);
                for(N=n;N>1;)
                {
                    for(j=0;j<26;j++)//枚举填的字母 
                    {
                        for(k=0;k<n;k++)if(a[k]&&s[k][j]>s[i][j])break;//判断填j后s[i]是不是最小的串 
                        if(k<n)continue;
                        for(k=0;k<n;k++)if(a[k]&&s[k][j]<s[i][j])break;//判断填j后能不能删掉其他的串
                        if(k<n)break;
                    }
                    if(j==26)break;//不能填字母 
                    for(k=0;k<n;k++)if(a[k]&&s[k][j]<s[i][j])N-=a[k]--;//删掉能删掉的串 
                }
                if(N==1)ans.push_back(i);
            }
            return ans;
        }
};