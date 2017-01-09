//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include "vector"
#include "stack"
using namespace std;

#define FOR(i,a,b) for (int i = a; i <= b; i++)

class Suminator {
public:
	long long cal(vector <int> program, int x) {
		//this function return the result we will receive if change -1 in vector <int> program to x
		int n = program.size();
		FOR (i, 0, n - 1) if (program[i] == -1) program[i] = x;

		stack <long long> S;
		//push enough zeroes in stack S, infact, n + 2 is enough.
		FOR (i, 1, 1000) S.push(0);

		FOR (i, 0, n - 1)
			if (program[i]) S.push(program[i]);
			else {
				long long u = S.top();
				S.pop();
				long long v = S.top();
				S.pop();

				S.push(u + v);
			}

		return S.top();
	}

	int findMissing(vector <int> program, int wantedResult) {
		//if replacing -1 by 0 can give us the needed result, return 0
		if (cal(program, 0) == wantedResult) return 0;

		//if replacing -1 by 1 can give us the needed result, return 1
		long long u = cal(program, 1);
		if (u == wantedResult) return 1;

		long long v = cal(program, 2);

		//if the result is not change when we changed the -1 number to 1 and to 2
		//then the program result does not depend on the -1 element.
		if (u == v) return -1;

		//otherwise, the answer is wantedResult - u + 1
		if (u < wantedResult) return wantedResult - u + 1;
		else return -1;
	}
};