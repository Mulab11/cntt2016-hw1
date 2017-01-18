#include<bits/stdc++.h>
using namespace std;
int n,i,f[100],s[100],m[100],ans;
int get(int x)
{
    return f[x]==x?x:f[x]=get(f[x]);
}
class GooseTattarrattatDiv1
{
    public:
        int getmin(string S)
        {
            n=S.size();
            for(i=0;i<26;i++)f[i]=i;
            for(i=0;i<n;i++)s[S[i]-'a']++;
            for(i=0;i<26;i++)m[i]=s[i];
            for(i=0;i<<1<n;i++)f[get(S[i]-'a')]=get(S[n-i-1]-'a');
            for(i=0;i<26;i++)if(get(i)!=i)
            {
                s[f[i]]+=s[i];
                m[f[i]]=max(m[f[i]],s[i]);
            }
            for(i=0;i<26;i++)if(f[i]==i)ans+=s[i]-m[i];
            return ans;
        }
};
