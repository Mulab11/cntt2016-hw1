#include<bits/stdc++.h>
using namespace std;
int n,i,j,t[55][26],s[26];
class LittleElephantAndString
{
    public:
        int getNumber(string A, string B)
        {
            n=A.size();
            reverse(A.begin(),A.end());
            reverse(B.begin(),B.end());
            fill(t[n],t[n]+26,n);
            for(i=n-1;~i;i--)
            {
                copy(t[i+1],t[i+1]+26,t[i]);
                s[A[i]-'A']++;
                s[B[i]-'A']--;
                t[i][A[i]-'A']=i;
            }
            for(i=0;i<26;i++)if(s[i])return -1;
            for(i=0,j=-1;i<n;i++)if(t[j+1][B[i]-'A']<n)j=t[j+1][B[i]-'A'];
            else break;
            return n-i;
        }
};
