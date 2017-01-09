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

#define n	55

int		N, M, F[n][n][3][3];

string	Ans, C;

bool	check(string A, string B, string Min){
	//	cout << "## " << A << " " << B << " " << Min << endl;
	
		M= B.length() - 1;
		
		For(i, 0, N+1)	For(j, 0, N+1)	For(a, 0, 2)	For(b, 0, 2)	F[i][j][a][b]= 0;
		F[N+1][0][1][1]= 1;
		
		//用一个simple的Dp来判断可行性。
		
		Rep(i, N, 0)	For(j, 0, N+1)	For(a, 0, 2)	For(b, 0, 2)
		if	(F[i+1][j][a][b])	{
			int	l= j, r= N - (N-i-j);
			
			if	((l <= M && A[i] == B[l]) || l > M)	{	//枚举放左的
				if	(a == 1)	{
					if	(A[i] == Min[l])	F[i][l+1][1][b]= 1;
					lf	(A[i] > Min[l])	F[i][l+1][2][b]= 1;
				}
				lf	(a == 2)	{
					F[i][l+1][2][b]= 1;
				}
			}
			
			if	((r <= M && A[i] == B[r]) || r > M)	{	//枚举放右的
				if	(A[i] > Min[r])	F[i][l][a][2]= 1;
				lf	(A[i] == Min[r])	F[i][l][a][b]= 1;
					else	F[i][l][a][0]= 1;
			}
		}
		
	//	printf("%d %d %d\n", F[3][0][1][1], F[2][0][1][0], F[1][1][1][0]);
		
		For(i, 0, N+1)	For(a, 0, 2)	For(b, 0, 2)
			if	((a == 2 || (a == 1 && b != 0)) && F[0][i][a][b])	return	1;
			
		return	0;
}

class	LeftRightDigitsGame2{
	public:
		string minNumber(string A, string Min){
			N= A.length() - 1;
			
			int	flag= 0;
			For(i, 0, N)	{	//逐位确定
				if	(! flag)	{	//需要卡住边界
					For(j, Min[i]-'0', 9)	{
						C= Ans + (char)('0' + j);
						
						if	(check(A, C, Min))	{
							Ans= C;
							if	(j > Min[i] - '0')	flag= 1;
							break;
						}
					}
				}	else	{	//不需要卡住边界
					For(j, 0, 9)	{
						C= Ans + (char)('0' + j);
						
						if	(check(A, C, Min))	{
							Ans= C;
							break;
						}
					}
				}
				
			//	cout << "--" << Ans << endl;
				
				if	((int)(Ans.length()) != i+1)	return	"";
			}
			
			return	Ans;
		}
};