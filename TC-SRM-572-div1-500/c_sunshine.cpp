∞#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class EllysBulls
{
	public:
	int n,m,l;
	vector<string> head,tail;
	vector<int> b;
	int nex[550000][10],cnt[550000],tot,root;
	string mem[550000],ans;
	int total;
	
	int samedigit(const string &a,const string &b)
	{
		int res=0;
		for(int i=a.size()-1;~i;i--)res+=a[i]==b[i];
		return res;
	}
	
	void Insert(string num)//Insert the bulls sequence into a trie.
	{
		int p=root,c;
		for(int i=0;i<n;i++)
		{
			c=samedigit(num,head[i]);
			if(!nex[p][c])nex[p][c]=++tot;
			p=nex[p][c];
		}
		mem[p]=num;cnt[p]++;
	}
	
	void Search(string num)//Search the trie for matching bulls sequences.
	{
		int p=root,c;
		for(int i=0;i<n&&p;i++)
		{
			c=b[i]-samedigit(num,tail[i]);
			p=nex[p][c];
		}
		if(p)
		{
			if(!total)ans=mem[p]+num;
			total+=cnt[p];
		}
	}
	
	void dfsh(int x,string num)
	{
		if(x==l)Insert(num);
		else
			for(char i='0';i<='9';i++)
				dfsh(x+1,num+i);
	}
	
	void dfst(int x,string num)
	{
		if(x==m-l)Search(num);
		else
			for(char i='0';i<='9';i++)
				dfst(x+1,num+i);
	}
	
	string getNumber(vector<string> guesses,vector<int> bulls)
	{
		b=bulls;tot=root=1;
		n=guesses.size(),m=guesses[0].size();l=m/2;
		string h,t;
		//Divide the number into two halfs.
		for(int i=0;i<n;i++)
		{
			h=t="";
			for(int j=0;j<m;j++)
				if(j<l)h+=guesses[i][j];
				else t+=guesses[i][j];
			head.push_back(h);
			tail.push_back(t);
		}
		//Pick all possible first halves and record them.
		dfsh(0,"");
		//Pick all possible second halves and search for the first halves that matches them.
		dfst(0,"");
		if(total>1)return "Ambiguity";
		if(total<1)return "Liar";
		else return ans;
	}
};

