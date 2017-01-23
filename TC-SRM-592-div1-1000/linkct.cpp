#include <bits/stdc++.h>
using namespace std;
const int MAXN = 27;
const double PI = acos(-1.0);

class SplittingFoxes2{
public:
	struct Complex{
		double r, i;
		Complex(){r = i = 0.0;}
		Complex(double a, double b): r(a), i(b) {}
		Complex operator * (const Complex &rhs) const{
			return Complex(r * rhs.r - i * rhs.i, r * rhs.i + i * rhs.r);
		}
		void operator += (const Complex rhs){
			r += rhs.r, i += rhs.i;
		}
	}w[MAXN], tmp[MAXN], a[MAXN], b[MAXN];
	int n, N;
	void DFT(Complex x[]){
		int i, j;
		for(i = 0; i < n; ++ i){
			tmp[i] = Complex(0.0, 0.0);
			for(j = 0; j < n; ++ j)
				tmp[i] += x[j] * w[i * j % n];
		}
		for(i = 0; i < n; ++ i)
			x[i] = tmp[i];
	}
	inline bool compare(vector <int> &x, vector <int> &y){
		for(int i = 0; i < n; ++ i)
			if(x[i] != y[i]) return x[i] < y[i];
		return false;
	}
	Complex sqrt(Complex x){
		double ang = atan2(x.i, x.r) / 2.0, len = std :: sqrt(std :: sqrt(x.r * x.r + x.i * x.i));
		return Complex(len * cos(ang), len * sin(ang));
	}
	inline bool check(const vector <int> &x, const vector <int> &y){
		int i, j, k;
		for(i = 0; i < n; ++ i){
			for(j = k = 0; j < n; ++ j)
				k += x[j] * x[(i - j + n) % n];
			if(k != y[i]) return false;
		} return true;
	}
	vector <int> getPattern(vector <int> a_){
		int i, j; vector <int> b_, ans;
		n = a_.size();
		w[0].r = 1.0, w[0].i = 0.0;
		w[1].r = cos(2 * PI / n), w[1].i = sin(2 * PI / n);
		for(i = 2; i < n; ++ i)
			w[i] = w[i - 1] * w[1];
		for(i = 0; i < n; ++ i)
			a[i].r = a_[i];
		DFT(a);
		for(i = 0; i < n; ++ i){
			a[i] = sqrt(a[i]);
			w[i].i = - w[i].i;
		} b_.resize(n);
		for(i = 0, N = 1 << (n / 2 + 1); i < N; ++ i){
			for(j = 0; j < n; ++ j){
				b[j] = a[j];
				if(i & (1 << min(j, n - j)))
					b[j].r = - b[j].r, b[j].i = - b[j].r;
			} DFT(b);
			for(j = 0; j < n; ++ j){
				b_[j] = int(b[j].r / n + 0.5 + 1e-5);
				if(b_[j] < 0) break;
			} if(j < n) continue;
			if(check(b_, a_) && (ans.empty() || compare(b_, ans)))
				ans = b_;
		} if(ans.empty()) ans.push_back(-1);
		return ans;
	}
};
