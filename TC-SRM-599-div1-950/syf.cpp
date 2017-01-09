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

class	SimilarNames{
	public:
		static const int MAX_VALID_MASKS = 6561;
 
		vector <int> child[51]; //child[x][i] is the i-th child of string x.
		int N,T,K;
		 
		int validSets[MAX_VALID_MASKS]; // List of valid sets
		int id[(1<<16)];                //Id (position in validSets) of a set
		vector<int> validSubsets[MAX_VALID_MASKS];
		// validSubsets[i], list of all the valid sets of set with id i.
		 
		int f[51][MAX_VALID_MASKS];
		int g[51][MAX_VALID_MASKS];
		const int MOD = 1000000007;
		 
		void dfs(int x) {
			int s = child[x].size();
			for (int i = 0; i < s; i++) {
				dfs(child[x][i] );
			}
			// Fill f[x][i]:
			//  Number of ways to distribute set i of conditional string positions
			//  in the subtree of prefixes rooted at x.
			//
			// First fill g[i][j]:
			//  Number of ways to distribute set i of conditional string positions
			//  in the first j children of x.
			memset(g, 0, sizeof(g));
			g[0][0] = 1;
			for (int i = 1; i <= s; i++) {
				for (int a = 0; a < T; a++) {
					int A = validSets[a];
					g[i][a] = 0;
					for (int B: validSubsets[a]) {
						int b = id[B];
						int w = id[A ^ B];
						long p = g[i-1][w];
						long q = f[child[x][i-1]][b];
						g[i][a] = (int)( (g[i][a] + p*q) % MOD );                    
					}
				}
			}
			for (int a = 0; a < T; a++) {
				int A = validSets[a];
				// don't pick any position for node x: 
				f[x][a] = g[s][a];
				if ( x != N ) {
					// Pick a position for node x. We cannot pick positions for
					// the root. So if x == N we shouldn't do it.
					for (int j = 0; j < K; j++) {
						// j must be in A:
						if ( A & (1<<j) ) {
							int b = id[ A ^ (1<<j) ];
							if (b != -1) {
								f[x][a] = (f[x][a] + g[s][b]) % MOD;
							}
						}                    
					}
				}
			}
		}
		// Is b a prefix of a?
		bool isPrefix(string a, string b)
		{
			return (b.length() <= a.length() && a.substr(0, b.length()) == b);
		}
		 
		void compress(vector<int> & info, map<int,int> & id)
		{
			for (int &x : info) {
				if ( id.count(x) == 0) {
					id[x] = id.size() - 1;
				}
				x = id[x];
			}
		}
		 
		int count(vector <string> names, vector <int> info1, vector <int> info2){
			N = names.size();
			// Make a tree of prefixes:
			sort(names.begin(), names.end());
			for (int i = 0; i < N; i++) {
				int parent = N;
				for ( int j = 0; j < i; j++ ) { 
					if ( isPrefix(names[i], names[j]) ) {
						if ( (parent == N || names[j].length() > names[parent].length()) ) {
							parent = j;
						}
					}
				}
				child[parent].push_back(i);
			}
			int M = info1.size();
			// Fix the indexes that are used to info1, info2 to the first K positions
			// update the arrays.
			{
				map <int, int> idmap;
				compress(info1, idmap);
				compress(info2, idmap);
				K = idmap.size();
			}
			// Find the valid sets of conditional string positions.
			T = 0;
			memset(id, -1, sizeof(id));
			for (int i = 0; i < (1 << K); i++) {
				bool bad = false;
				for (int j = 0; j < M; j++) {
					// A set is invalid if it contains info1 and does not contain info2
					bool in1 = (i & (1 << info1[j]) );
					bool in2 = (i & (1 << info2[j]) );
					bad = ( bad || ( in1 && ! in2) );
				}
				if (!bad) {
					validSets[T] = i;
					id[i] = T++;
				}
			}
			// Maximum number of valid sets is 3^8 
			assert(T <= MAX_VALID_MASKS);
			 
			for (int i=0; i<T; i++) {
				for (int j=0; j<T; j++) {
					// if mask j is a subset of mask i:
					if ( (validSets[i] & validSets[j]) == validSets[j] ) {
						if ( id[ validSets[i]^ validSets[j] ] != -1 ) { 
							validSubsets[i].push_back( validSets[j] );
						}
					}
				}
			}
			// fill the dp tables:
			dfs(N);
			//Multiply by (N-K)!
			long ans = f[N][T-1];
			for (int i = 1; i <= N - K; i++) {
				ans = (ans * i) % MOD;
			}
			return (int)ans;
		}
};