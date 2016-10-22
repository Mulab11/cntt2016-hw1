#include <bits/stdc++.h>
#define M 14

using namespace std;

class BoundedOptimization
{
	int n, X[M][M], B[M], F[M], Can[1 << M], S;
	
	double Mat[M][M], V[1 << M][M][M], ans;
	
	vector <int> U, L;
	
	int calc(int id)
	{
		int cnt = 0;
		for(int i = 0; i < n; i++) if(!B[i]) V[id][cnt][cnt] = -1, F[i] = cnt++;
		V[id][cnt][cnt] = 1, memset(Mat, 0, sizeof Mat);
		for(int i = 0; i < n; i++) if(!B[i])
			for(int j = 0; j < n; j++) if(!B[j]) Mat[F[i]][F[j]] = X[i][j];
		for(int i = 0; i < cnt; i++) Mat[cnt][i] = Mat[i][cnt] = 1;//initalize the matrix
		for(int i = 0; i <= cnt; i++) {
			int v = -1;
			for(int j = i; j <= cnt; j++) if(abs(Mat[j][i]) > 1e-7) {v = j; break;}
			if(v == -1) return 0;
			swap(Mat[i], Mat[v]), swap(V[id][i], V[id][v]);
			for(int j = 0; j <= cnt; j++) V[id][i][j] /= Mat[i][i];
			for(int j = cnt; j >= i; j--) Mat[i][j] /= Mat[i][i];
			for(int j = i + 1; j <= cnt; j++) {
				for(int k = 0; k <= cnt; k++) V[id][j][k] -= Mat[j][i] * V[id][i][k];
				for(int k = cnt; k >= i; k--) Mat[j][k] -= Mat[j][i] * Mat[i][k];
			}
		}//gaussian elimination
		for(int i = cnt; i > 0; i--)
			for(int j = i - 1; j >= 0; j--)
				for(int k = 0; k <= cnt; k++)
					V[id][j][k] -= Mat[j][i] * V[id][i][k];
		return 1;
	}
	
	void calc2(int id)
	{
		if(!Can[id]) return;
		double K[15], tmp[15], nw = 0, sm = S;
		int S[15], cnt = -1;
		memset(K, 0, sizeof K);
		for(int i = 0; i < n; i++) if(B[i]) sm -= K[i] = (B[i] == 1 ? U[i] : L[i]);
		for(int i = 0; i < n; i++) if(!B[i]) {
			tmp[++cnt] = 0, S[cnt] = i;
			for(int j = 0; j < n; j++) if(B[j]) tmp[cnt] += X[i][j] * K[j];
		}
		tmp[++cnt] = sm;
		for(int i = 0; i < cnt; i++)
			for(int j = 0; j <= cnt; j++) K[S[i]] += tmp[j] * V[id][i][j];//calculate each variable
		for(int i = 0; i < n; i++) if(K[i] > U[i] || K[i] < L[i]) return;//check if vaild
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j < n; j++) nw += X[i][j] * K[i] * K[j];//calculate the ans
		ans = max(ans, nw);
	}
	
	void Search(int x, int nw = 0) //search all of the possible state
	{
		if(x == n) calc2(nw); else for(B[x] = 0; B[x] < 3; B[x]++) Search(x + 1, nw + ((B[x] > 0) << x));
	}
	
	public: double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum)
	{
		string st;
		for(int i = 0; i < expr.size(); i++) st += expr[i];
		U = upperBound, L = lowerBound,	n = lowerBound.size(), ans = -1, S = maxSum;
		for(int i = 0; i < st.size(); i += 3) X[st[i] - 'a'][st[i + 1] - 'a']++, X[st[i + 1] - 'a'][st[i] - 'a']++;
		int s = 0;
		for(int i = 0; i < n; i++) s += U[i];
		S = min(S, s);//check if maxsum is larger than the sum of the upperbound
		for(int i = 0; i < (1 << n); Can[i] = calc(i), i++)
			for(int j = 0; j < n; j++) B[j] = (i >> j) & 1;//pretreatment all the matrix
		Search(0);
		return ans;
	}
};
