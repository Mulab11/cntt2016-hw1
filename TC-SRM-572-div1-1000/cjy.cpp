#include<bits/stdc++.h>
#define FA(i) for(int i=0;i<26;i++)
using namespace std;
int f[26],g[26],O=1e9,S=O,i,A,B;
int Calc()
{
	int l=-O,gl=0,s=0;
	FA(i)if(g[i]){if(s+=(g[i]>gl)*(max(0,g[i]-i-97)*A+max(0,l+97-gl)*B),l=i,g[i]<gl)return O;gl=g[i];}
	return s+max(0,l+97-gl)*B;
}
class NextAndPrev
{
	public:
		int getMinimum(int C,int D,string s,string t)
		{
			if(A=C,B=D,s==t)return 0;
			for(;i<s.size();f[s[i]-97]=t[i++])if(f[s[i]-97]&&f[s[i]-97]!=t[i])return -1;
			FA(i)if((f[i]-i)%26!=f[0]%26)goto GO;
			return -1;GO:;
			FA(i)
			{
				FA(j)g[(j+i)%26]=(f[j]>0)*(f[j]+i);
				S=min(S,Calc());
				FA(j)g[j]=(g[j]>0)*(g[j]+26);
				S=min(S,Calc());
				FA(j)g[j]=(g[j]>0)*(g[j]-52);
				S=min(S,Calc());
			}
			return S==O?-1:S;
		}
};
