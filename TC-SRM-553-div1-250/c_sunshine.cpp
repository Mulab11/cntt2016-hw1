#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
class Suminator
{
	public:
	
	vector<LL> st;
	
	LL run(vector<int> &pro)//Run the program.
	{
		st.clear();
		for(int i=0;i<=pro.size();i++)
			st.push_back(0);
		LL a,b;
		for(int i=0;i<pro.size();i++)
		{
			if(pro[i])st.push_back(pro[i]);
			else
			{
				a=st.back();
				st.pop_back();
				b=st.back();
				st.pop_back();
				st.push_back(a+b);
			}
		}
		return st.back();
	}
	
	int findMissing(vector<int> program,int wantedResult)
	{
		int pos;
		for(int i=0;i<program.size();i++)
			if(program[i]==-1)pos=i;
		program[pos]=0;
		if(run(program)==wantedResult)return 0;//the unknown element is 0. 
		program[pos]=1;
		LL ans1=run(program);
		program[pos]=2;
		LL ans2=run(program);
		LL dta=wantedResult-ans1;
		//result = kx + b ( 0 <= k <= 1 )
		if(dta==0)return 1;//Any number fits.
		if(dta<0||ans1==ans2)return -1;//We can't change the result by changing the value of the varible.
		return dta+1;
	}
};

