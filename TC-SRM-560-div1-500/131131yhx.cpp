#include <bits/stdc++.h>

using namespace std;

const int L = 138;

struct DrawingPointsDivOne
{
	int A[1010][1010];
	
	int maxSteps(vector <int> x, vector <int> y)
	{
		int n = x.size();
		for(int i = 0; i < n; i++) x[i] = x[i] * 2 + 500, y[i] = y[i] * 2 + 500;//to avoid some problem
		for(int T = 1; T <= L; T++) {
			memset(A, 0, sizeof A);
			for(int i = 0; i < n; i++)
				for(int j = x[i] - T; j <= x[i] + T; j += 2)
					for(int k = y[i] - T; k <= y[i] + T; k += 2) A[j][k] = 1;//fill with model square(the defination is in the solution)
			for(int i = 360 - T; i <= 640 + T; i++)
				for(int j = 360 - T; j <= 640 + T; j++) A[i][j] -= A[i - 1][j - 1] - A[i - 1][j] - A[i][j - 1];//2D prefix_sum
			int ans = 0;
			for(int i = 360; i <= 640; i++)
				for(int j = 360; j <= 640; j++)
					if(A[i + T][j + T] - A[i - T - 1][j + T] - A[i + T][j - T - 1] + A[i - T - 1][j - T - 1] == (T + 1) * (T + 1)) ans++;//check every point in the [-70,70],[-70,70] range
			if(ans != n) return T - 1;//check if k=T is vaild
		}
		return -1;
	}
};
