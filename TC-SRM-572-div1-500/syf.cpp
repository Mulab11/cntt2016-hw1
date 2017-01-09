//============================================================================
// Author       : Sun YaoFeng
//============================================================================

//#pragma 	comment(linker, "/STACK:100240000,100240000")
//#include	<cstdio>
//#include	<cstdlib>
//#include	<cstring>
//#include	<algorithm>

#include	<bits/stdc++.h>

using	namespace	std;

#define DB		double
#define	lf		else if
#define I64		long long
#define	Rd()	(rand()<<15|rand())
#define For(i,a,b)	for(int i=a,lim=b;i<=lim;i++)
#define Rep(i,a,b)	for(int i=a,lim=b;i>=lim;i--)

#define	fi	first
#define se	second
#define MK	make_pair
#define PA	pair<int, int>

//#define	min(a,b)	((a)<(b)?(a):(b))
//#define	max(a,b)	((a)<(b)?(b):(a))

#define	CH	(ch=getchar())
int		IN()	{
		int x= 0, f= 0, ch;
		for	(; CH < '0' || ch > '9';)	f= (ch == '-');
		for	(; ch >= '0' && ch <= '9'; CH)	x= x*10 + ch -'0';
		return	f? -x : x;
}

#define Vec	vector<int>
#define Ves	vector<string>

int		N, L, M, tot;
string	Ans;

Ves		S;
Vec		B;

map<Vec, Ves >	G;

void	DFS1(int d, string now)	{	//暴搜其中一边
		if	(d > M)	{
			Vec	x;
			For(i, 1, N)	{
				int	cnt= 0;
				For(j, 1, M)	cnt+= (now[j-1] == S[i-1][j-1]);
				x.push_back(cnt);
			}

			G[x].push_back(now);
			
			return;
		}
	
		For(i, 0, 9)	DFS1(d+1, now + ((char)('0' + i)));
}

void	DFS2(int d, string now)	{		//在另外一边求满足要求的个数
		if	(d > L)	{
			Vec	x= B;
			For(i, 1, N)	{
				int	cnt= 0;
				For(j, M+1, L)	cnt+= (now[j-M-1] == S[i-1][j-1]);
				x[i-1]-= cnt;
			}
			
			if	(! G[x].size())	return;
			if	(G[x].size() > 1)	tot= 2;	
			lf	(tot)	tot= 2;
				else	tot= 1, Ans= G[x][0] + now;
			
			return;
		}
		
		For(i, 0, 9)	DFS2(d+1, now + ((char)('0' + i)));
}

class	EllysBulls{
	public:
		string getNumber(Ves S, Vec B){	//Meet-in-middle
			::S= S;
			::B= B;
			
			N= S.size();
			L= S[0].length();
			M= L >> 1;
			
			DFS1(1, "");	//将前后两段分别暴搜出来
			DFS2(M+1, "");
			
			if	(tot > 1)	return	"Ambiguity";
			if	(tot == 0)	return	"Liar";
			return	Ans;
		}
};