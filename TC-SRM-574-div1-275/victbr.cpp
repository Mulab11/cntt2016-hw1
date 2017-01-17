#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

class TheNumberGame{
	public:
		string determineOutcome(int A, int B) {
			ll x = A,w = 1,C = 0;
			while (w <= B) w *= 10;
			while (x >= B){
				if ((x - B)% w == 0) return "Manao wins";
				x /= 10;
			}
			while (B){C *= 10;C += B%10;B/=10;}
			B = C;
			x = A;w = 1;
			while (w <= B) w *= 10;
			while (x >= B){
				if ((x - B)% w == 0) return "Manao wins";
				x /= 10;
			}
			return "Manao loses";
		}
};
