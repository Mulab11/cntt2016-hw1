/*
	Firstly, judge if x = 0.
	Otherwise the result is a linear function of x: res = kx + b, here k = 0 or 1.
	Let x = 1, 2 and compute the result with brute force.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
struct stack233{
	LL arr[233], n;
	stack233(){
		memset(arr, 0, sizeof arr);
		n = 0;
	}
	LL pop(){
		return n ? arr[n--] : 0;
	}
	LL top(){
		return n ? arr[n] : 0;
	}
	void push(LL v){
		arr[++n] = v;
	}
};
class Suminator {
	public:
	LL run(vector<int> program){
		stack233 s;
		for (int i = 0; i < program.size(); ++i){
			int p = program[i];
			if (p) s.push(p);
			else s.push(s.pop() + s.pop());
		}
		return s.top();
	}
	int findMissing(vector <int> program, int res) {
		int pos = -1;
		for (int i = 0; i < program.size(); ++i)
			if (program[i] == -1){
				pos = i; break;
			}
		program[pos] = 0;
		if (run(program) == res) return 0;
		program[pos] = 1;
		LL ret1 = run(program);
		program[pos] = 2;
		LL ret2 = run(program);
		LL k = ret2 - ret1, b = ret1 - 1;
		if ((!k && b != res) || (k && b >= res)) return -1;
		if (!k) return 233;
		return res - b;
	}
};

/*
	'Inochi hakanai
	Koiseyo shoujo yo'
		- Wonder Stella
*/

