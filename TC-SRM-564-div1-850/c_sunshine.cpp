#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
const int M=1000000007;

class DefectiveAddition
{
	public:
	int count(vector<int> cards,int n)
	{
		int m=cards.size();
		sort(cards.begin(),cards.end());
		int t=1;
		for(;t+t<=cards[m-1]+1;t+=t);//t is the heightest bit of the maximum number in the given sequence.
		if(n>=t+t)return 0;//Impossible.
		int f0=1,f1=0,g0,g1;
		//f0/1 : the number of ways to use the number except the maximum one and make the xor-sum 0/1 at bit t.
		for(int i=0;i<m-1;i++)
		{
			g0=((LL)f0*min(cards[i]+1,t)+(LL)f1*max(cards[i]-t+1,0))%M;
			g1=((LL)f1*min(cards[i]+1,t)+(LL)f0*max(cards[i]-t+1,0))%M;
			f0=g0,f1=g1;
		}
		int res;
		//Count the ways that we can choose the last number in [0,t-1] freely.
		if(n>=0&&n<t)res=f0;
		else res=f1;
		//Consider the onther situation, the last number is greater than or equal t.
		//We can simply subtract t from the last number, and change n into n xor t.
		//It will become a subproblem because the number of "1"s in base 2 is always decreasing.
		if(cards[m-1]>=t)
		{
			vector<int> cards_=cards;
			cards_[m-1]-=t;
			res=(res+count(cards_,n^t))%M;//Solve subproblem.
		}
		return res;
	}
};

