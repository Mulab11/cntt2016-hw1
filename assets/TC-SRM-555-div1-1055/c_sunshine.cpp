#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int N=100;

class MapGuessing
{
	public:
	int n,m,L,R;
	LL co[N+5][N+5];
	string G,C;
	vector<LL> num;
	
	int count(LL x)
	{return x?1+count(x&x-1):0;}
	
	LL getval(int pos)
	{
		//Find the set of the matched bits.
		bool ch[40],flag;
		string be(n,' ');
		memset(ch,0,sizeof(ch));
		LL res=0,tmp;
		for(int i=0;i<m;i++)//Run the program.
		{
			if(C[i]=='<')pos--;
			else if(C[i]=='>')pos++;
			else if(C[i]=='0')ch[pos]=1,be[pos]='0';
			else ch[pos]=1,be[pos]='1';
			flag=1,tmp=0;
			for(int j=0;j<n&&flag;j++)
			{
				if(ch[j]&&be[j]!=G[j])flag=0;
				if(ch[j])tmp|=1LL<<j;
			}
			if(flag)res=tmp;//the number of "1"s in tmp are always increasing.
		}
		return res;
	}
	
	LL calc(int x,LL s)
	{
		if(!s)return 0;
		if(x==num.size())return (1LL<<count(s))-1;
		return calc(x+1,s)-calc(x+1,s&num[x]);//use subtraction here because of the inclusion-exclusion principle
	}
	
	LL countPatterns(string goal,vector<string> code)
	{
		G=goal;n=G.size();
		for(int i=0;i<code.size();i++)
			C+=code[i];
		m=C.size();
		for(int i=0,j;i<=N;i++)
			for(co[i][0]=co[i][i]=j=1;j<i;j++)
				co[i][j]=co[i-1][j-1]+co[i-1][j];
		int pos=0;
		//Find the range of the pointer.
		L=R=0;
		for(int i=0;i<m;i++)
		{
			if(C[i]=='<')L=min(L,--pos);
			if(C[i]=='>')R=max(R,++pos);
		}
		L=-L;
		for(pos=L;pos<n-R;pos++)
			num.push_back(getval(pos));
		if(num.empty())return 0;
		LL res=calc(0,(1LL<<n)-1);//We can prove that the time complexity is O(sqrt(n*2^n)).
		return (1LL<<n)-res;
	}
};


