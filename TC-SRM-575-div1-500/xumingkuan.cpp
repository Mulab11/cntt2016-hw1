#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;
class TheSwapsDivOne
{
private:
	int n;
	string a;//the sequence
	//double f[2];//f[i & 1]: i swaps, probability of (j -> j) (any j)
	string concatenate(const vector<string> &vec)
	{
		string ret;
		for(int i = 0; i < vec.size(); i++)
			ret += vec[i];
		return ret;
	}
public:
	double find(vector<string> sequence, int k)
	{
		a = concatenate(sequence);
		n = a.size();
		double ans = 0, prob = pow((double)(n - 3) / (n - 1), k) * (n - 1) / n + 1.0 / n;//see solution
		//f[0] = 1;
		//for(int i = 1; i <= k; i++)
		//	f[i & 1] = f[~i & 1] * (n - 2) / n + (1 - f[~i & 1]) / ((n * (n - 1) / 2));
		int sum = 0;
		for(int i = 0; i < n; i++)
			sum += (a[i] -= '0');
		for(int i = 0; i < n; i++)
			ans += (prob * a[i] + (1 - prob) * (sum - a[i]) / (n - 1)) * (i + 1) * (n - i);
		ans /= (n * (n + 1) / 2);
		return ans;
	}
};

