#include<bits/stdc++.h>
using namespace std;
int n,i,j,k,l,a[55][26],b[55][26],s[26];
string ans;
class FoxAndHandle
{
    public:
        string lexSmallestName(string S)
        {
            n=S.size();
            fill(a[n],a[n]+26,n);
            for(i=n-1;~i;i--)for(j=0;j<26;j++)if(S[i]==j+'a')
            {
                a[i][j]=i+1;//计算下一个j出现的位置 
                b[i][j]=b[i+1][j]+1;//计算后面j出现的次数 
            }
            else
            {
                a[i][j]=a[i+1][j];
                b[i][j]=b[i+1][j];
            }
            for(i=0;i<26;i++)s[i]=b[0][i]>>1;//统计每个字母出现次数 
            for(i=l=0;l<n>>1;l++)for(j=0;j<26;j++)if(s[j])
            {
                s[j]--;
                for(k=0;k<26;k++)if(b[a[i][j]][k]<s[k])break;//判断能否填j 
                if(k<26)s[j]++;//不能填j 
                else//可以填j 
                {
                    i=a[i][j];//转移到下一个位置 
                    ans+=j+'a';
                    break;
                }
            }
            return ans;
        }
};