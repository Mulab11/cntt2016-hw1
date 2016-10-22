#include <bits/stdc++.h>

using namespace std;

class BoundedOptimization
{
	int X[15][15], n;
	
	double ans, V[15];
	
	bool check(int S) //check if it has aij=0
	{
		for(int i = 0; i < n; i++)
			for(int j = i + 1; j < n; j++)
				if(((S >> i) & 1) && ((S >> j) & 1) && !X[i][j]) return 0;
		return 1;
	}
	
	public: double maxValue(vector <string> expr, vector <int> L, vector <int> U, int S)
	{
		string st;
		for(int i = 0; i < expr.size(); i++) st += expr[i];
		n = L.size(), ans = -1;
		for(int i = 0; i < st.size(); i += 3) X[st[i] - 'a'][st[i + 1] - 'a']++, X[st[i + 1] - 'a'][st[i] - 'a']++;
		int tmp = 0;
		for(int i = 0; i < n; i++) tmp += U[i];
		S = min(S, tmp);
		for(int i = 0; i < (1 << n); i++) if(check((1 << n) - i - 1))
			for(int j = i; j >= 0; j = !j ? -1 : (j - 1) & i) {
				int tot = 0, fg = 0;
				double rs = S, nw = 0;//rs means the sum of all the unknown variable, nw means ans
				for(int s = 0; s < n; s++) V[s] = 0;//V means the value of the variable
				for(int s = 0; s < n; s++)
					if((j >> s) & 1) rs -= V[s] = U[s];
					else if((i >> s) & 1) rs -= V[s] = L[s];
					else tot++;
				if(!tot) continue;
				for(int s = 0; s < n; s++) if(!((i >> s) & 1))
					for(int p = 0; p < n; p++) if(((i >> p) & 1) && X[s][p])
						V[s] += V[p], rs -= V[p];
				for(int s = 0; s < n; s++) if(!((i >> s) & 1)) V[s] += rs / tot;
				for(int s = 0; s < n; s++) if(V[s] > U[s] + 1e-7 || V[s] < L[s] - 1e-7) {fg = 1; break;}
				if(fg) continue;
				for(int s = 0; s < n; s++)
					for(int p = s + 1; p < n; p++) if(X[s][p]) nw += V[s] * V[p];
				ans = max(ans, nw);
			}
		return ans;
	}
} calc;
