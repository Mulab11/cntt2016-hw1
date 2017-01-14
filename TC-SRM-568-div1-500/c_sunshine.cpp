#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int M=1000000007;

class EqualSums
{
	public:
	int n;
	int num[105],vis[105];
	vector<string> board;
	
	bool check(int i)//Use Depth First Search to traversal this component and determine all X[i]/Y[i], or find it impossible.
	{
		vis[i]=1;
		bool res=1;
		if(i<n)
		{
			for(int k=0;k<n;k++)
				if(board[i][k]!='-')
				{
					int t=board[i][k]-'0'-num[i];//determine Y[k]
					if(t<0)return 0;//Y[k] should be non-negative.
					if(num[k+n]==-1)num[k+n]=t,res&=check(k+n);
					else if(num[k+n]!=t)return 0;//There is a conflict
				}
		}
		else
		{
			//Samilar with above.
			for(int k=0;k<n;k++)
				if(board[k][i-n]!='-')
				{
					int t=board[k][i-n]-'0'-num[i];
					if(t<0)return 0;
					if(num[k]==-1)num[k]=t,res&=check(k);
					else if(num[k]!=t)return 0;
				}
		}
		return res;
	}
	
	int count(vector<string> board)
	{
		//We can prove that there exist two arrays X,Y satisfying A[i][j]=X[i]+Y[j].
		//Only need to count the number of (X,Y).
		this->board=board;
		n=board.size();
		LL sumn=1,sump=1;//the number of ways that all X[i]/Y[i] are non-negative/positive
		//Treat each known cell (i,x) as an edge <X[i],Y[j]>, and limit that X[i]+Y[j]=A[i][j]
		for(int i=0;i<n+n;i++)
			if(!vis[i])//This row/column hasn't been visted.
			{
				//Now we consider this component.
				int sn=0,sp=0;
				for(int x=0;x<10;x++)//Pick all possible X[i]/Y[j] for this row/column.
				{
					memset(num,-1,n+n<<2);
					num[i]=x;
					if(check(i))
					{
						sn++,sp++;
						for(int i=0;i<n;i++)
							if(num[i]==0){sp--;break;}
					}
				}
				sumn=(LL)sumn*sn%M;
				sump=(LL)sump*sp%M;
			}
		int ans=(sumn-sump+M)%M;
		return ans;
	}
};

