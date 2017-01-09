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

#define	n	55

int		N;

DB		Pr[n], Pp[n], Ps[n], C[n][n], Fr[n][n][n], Fp[n][n][n], Fs[n][n][n], F0[n][n][n];

class	RockPaperScissors{
	public:
		DB	bestScore(vector <int> rP, vector <int> pP, vector <int> sP){
			N= rP.size();
			For(i, 1, N)	{
				Pr[i]= rP[i-1] / 300.;
				Pp[i]= pP[i-1] / 300.;
				Ps[i]= sP[i-1] / 300.;
			}
			
			//F0[a][b][c] 表示出现(a,b,c)这个局面的概率
			//Fr,Fp,Fs 表示出现(a,b,c)后，剩余哪些物品的，剪刀、石头、步的出现概率
			
			F0[0][0][0]= 1;
			For(i, 1, N)	Rep(a, i, 0)	Rep(b, i, 0)	Rep(c, i, 0)	{	//逐个枚举每一个数，考虑它的出现形态，进行转移
				Fr[a+1][b][c]+= Fr[a][b][c] * Pr[i];
				Fr[a][b+1][c]+= Fr[a][b][c] * Pp[i];
				Fr[a][b][c+1]+= Fr[a][b][c] * Ps[i];
				
				Fp[a+1][b][c]+= Fp[a][b][c] * Pr[i];
				Fp[a][b+1][c]+= Fp[a][b][c] * Pp[i];
				Fp[a][b][c+1]+= Fp[a][b][c] * Ps[i];
				
				Fs[a+1][b][c]+= Fs[a][b][c] * Pr[i];
				Fs[a][b+1][c]+= Fs[a][b][c] * Pp[i];
				Fs[a][b][c+1]+= Fs[a][b][c] * Ps[i];
				
				Fr[a][b][c]+= F0[a][b][c] * Pr[i];
				Fp[a][b][c]+= F0[a][b][c] * Pp[i];
				Fs[a][b][c]+= F0[a][b][c] * Ps[i];
				
				F0[a+1][b][c]+= F0[a][b][c] * Pr[i];
				F0[a][b+1][c]+= F0[a][b][c] * Pp[i];
				F0[a][b][c+1]+= F0[a][b][c] * Ps[i];
			}
			
			For(i, 0, N)	{
				C[i][0]= 1;
				For(j, 1, i)	C[i][j]= C[i-1][j-1] + C[i-1][j];
			}
			
			DB	Ans= 0;
			For(a, 0, N)	For(b, 0, N)	For(c, 0, N)	{
				int	t= a + b + c;
				if	(t >= N)	break;
				
			//	printf("%lf %lf %lf %lf\n", Fr[a][b][c], Fp[a][b][c], Fs[a][b][c], F0[a][b][c]);
				
				Fs[a][b][c]/= C[N][t] * (N-t);	//最后除以总方案数就是概率了
				Fr[a][b][c]/= C[N][t] * (N-t);
				Fp[a][b][c]/= C[N][t] * (N-t);
				
				DB	ret= 0;
				ret= max(ret, Fs[a][b][c] * 3 + Fr[a][b][c]);
				ret= max(ret, Fr[a][b][c] * 3 + Fp[a][b][c]);
				ret= max(ret, Fp[a][b][c] * 3 + Fs[a][b][c]);
				
				Ans+= ret;
			}
			
			return	Ans;
		}
};