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

#define PB	push_back
#define DB		double
#define	lf		else if
#define I64		long long
#define	Rd()	(rand()<<15|rand())
#define For(i,a,b)	for(int i=a,lim=b;i<=lim;i++)
#define FORD(i,a,b)	for(int i=a,lim=b;i>=lim;i--)

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

class	KingdomAndDice{
	public:
	
	#define FOR(x,a,b) for (int x = a; x <= b; x++)
	int cnt[11111];

	double newFairness(vector < int > firstDie, vector < int > secondDie, int X) {
		int n = firstDie.size();//n is the number of sides in each dice

		set < int > infirst;//store fixed number in first dice
		FOR (i, 0, n- 1) infirst.insert(firstDie[i]);

		secondDie.PB(0);
		secondDie.PB(X + 1);
		sort (secondDie.begin(), secondDie.end());

		vector < int > S; //store the values f()s we can chose
		FOR (i, 0, n) {
			int cnt = 0;
			FOR (j, secondDie[i] + 1, secondDie[i + 1] - 1)
			if (infirst.find(j) == infirst.end()) {
				//call f(j) and push it in S
				int f = 0;
				FOR (k, 1, n) f += secondDie[k] < j;
				S.PB(f);

				cnt++;
				if (cnt == n) break;
			}
		}

		int m = 0;//number of un-fixed sides in 1st dice
		FOR (i, 0, n - 1) m += firstDie[i] == 0;

		//we now calculate the values cnt(s)
		cnt [0] = 0;
		FOR (i, 1, n * n) cnt[i] = m + 1;

		int z = S.size();
		FOR (i, 0, z - 1)
		FORD (j, n * n, 1)
			if (j - S[i] >= 0) cnt[j] = min(cnt[j], cnt[j - S[i]] + 1);

		//calculate the sum of f() value in all fixed label side of 1st dice
		int sum = 0;
		FOR (i, 0, n - 1)
		if (firstDie[i] != 0)
			FOR (j, 1, n) sum += firstDie[i] > secondDie[j];

		//find the final result
		int res = -1;
		FOR (i, 0, n * n)
		if (cnt[i] <= m) {
			if (res == -1) res = i + sum;
			else if (abs(2 * (sum + i) - n * n) < abs(2 * res - n * n)) res = i + sum;
		}

		return (double) res / (double) (n * n);
	}
};