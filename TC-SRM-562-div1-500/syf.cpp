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

#define n	255
#define Bit	bitset<n>

int		N, M;

struct	Nod{
		int x, y;
		
		Nod	operator -	(const Nod&b)	const{
			return	(Nod){x - b.x, y - b.y};
		}
		I64	operator *	(const Nod&b)	const{
			return	1ll*x*b.y - 1ll*y*b.x;
		}
}A[n], B[n];

Bit		U[n][n], L[n][n], R[n][n];

class	CheckerFreeness{
	public:
		string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY){
			{
				string	s= "";
				For(i, 1, whiteX.size())	s+= whiteX[i-1];
				
				int len= s.length();
				for (int i= 0, j; i < len ; i= j+1)	{
					int x= 0;
					for (j= i; j < len && s[j] != ' '; j++)	x= x*10 + s[j] - '0';
					A[++ N].x= x;
				}
			}
			
			{
				string	s= "";
				For(i, 1, whiteY.size())	s+= whiteY[i-1];
				
				N= 0;
				int len= s.length();
				for (int i= 0, j; i < len ; i= j+1)	{
					int x= 0;
					for (j= i; j < len && s[j] != ' '; j++)	x= x*10 + s[j] - '0';
					A[++ N].y= x;
				}
			}
			
			//预处理
			
			{
				string	s= "";
				For(i, 1, blackX.size())	s+= blackX[i-1];
				
				int len= s.length();
				for (int i= 0, j; i < len ; i= j+1)	{
					int x= 0;
					for (j= i; j < len && s[j] != ' '; j++)	x= x*10 + s[j] - '0';
					B[++ M].x= x;
				}
			}
			
			{
				string	s= "";
				For(i, 1, blackY.size())	s+= blackY[i-1];
				
				M= 0;
				int len= s.length();
				for (int i= 0, j; i < len ; i= j+1)	{
					int x= 0;
					for (j= i; j < len && s[j] != ' '; j++)	x= x*10 + s[j] - '0';
					B[++ M].y= x;
				}
			}
			
			//将两两直接的连线，顺指针方向和逆时针方向上的点们都用bitset统计。
			
			For(i, 1, N)	For(j, 1, N)	if	(i != j)	For(k, 1, M)
				if	( (B[k]-A[j]) * (A[i]-A[j]) > 0 )	U[i][j][k]= 1;
			
			For(i, 1, N)	For(j, 1, M)	For(k, 1, M)
				if	( (B[k]-B[j]) * (A[i]-B[j]) > 0)	R[i][j][k]= 1;
			
			For(i, 1, N)	For(j, 1, M)	For(k, 1, M)
				if	( (B[k]-B[j]) * (A[i]-B[j]) < 0)	L[i][j][k]= 1;
			
			For(i, 1, N)	For(j, 1, N)	if	(i != j)	For(k, 1, M)	//计算答案
				if	((U[i][j] & R[i][k] & L[j][k]).count() && ! U[i][j][k])	return	"NO";
			
			return	"YES";
		}
};