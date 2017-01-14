#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int inf=1<<20;

class YetAnotherBoardGame
{
	public:
	
	int n,m,all;
	int S[15],T[15];
	int A0[8192],A1[8192],C[8192];
	
	int work(int s,int t)
	{
		int res=0;
		for(int i=0;i<n;i++)S[i]=T[i];
		if(s&t)
			S[0]^=A1[t];
		else
			S[0]^=A0[t];
		S[1]^=t;
		res+=C[t];
		for(int i=1;i<n;i++)//Determine the moves of all cells
		{
			t=S[i-1];
			if((t&s)&&(t&(all^s)))return inf;//Conflict between the rows and columns' type limit.
			if(t&s)
				S[i]^=A1[t];
			else
				S[i]^=A0[t];
			S[i-1]^=t;
			S[i+1]^=t;
			res+=C[t];
		}
		//Check if the last row is done.
		if(S[n-1]==0)return res;
		return inf;
	}
	
	int minimumMoves(vector<string> board)
	{
		//First, we try all possible types of moves of columns
		//Then we can attemp all possible moves in the first row
		//Then we can use the current first row's status to determine the moves in the second row, then the third ...
		//We can determine moves in each cell, and then we can check it and update the answer.
		//Notice that the row can only contain one kind of moves, so the time complexity is O(2^m).
		n=board.size();
		m=board[0].size();
		all=(1<<m)-1;
		//Get the effect(fliped set) of two types of moves to current row and adjacent rows.
		for(int i=1;i<1<<m;i++)
		{
			C[i]=C[i&i-1]+1;
			for(int j=0;j<m;j++)
				if(i>>j&1)
				{
					if(j>0)A0[i]^=1<<j-1;
					if(j+1<m)A0[i]^=1<<j+1;
					if(j>0)A1[i]^=1<<j-1;
					A1[i]^=1<<j;
					if(j+1<m)A1[i]^=1<<j+1;
				}
		}
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				S[i]|=(board[i][j]=='W')<<j;
		memcpy(T,S,sizeof(S));
		int ans=n*m+1;
		//Try all possible types of moves of columns
		for(int s=0;s<1<<m;s++)
		{
			//Attemp all possible moves in the first row
			ans=min(ans,work(s,0));//no move
			for(int i=s;i;i=i-1&s)
				ans=min(ans,work(s,i));//first type of moves
			for(int i=(all^s);i;i=i-1&(all^s))
				ans=min(ans,work(s,i));//second type of moves
		}
		if(ans<=n*m)return ans;
		return -1;
	}
};

