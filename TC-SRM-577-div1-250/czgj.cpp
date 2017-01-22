/*
	Expectation, Implementation(concatenating strings)
*/

#include <bits/stdc++.h>
using namespace std;

class EllysRoomAssignmentsDiv1 {
	public:
	double getAverage(vector <string> ratings) {
		char st[6666] = ""; int a[666];
		for (int i = 0; i < ratings.size(); ++i) strcat(st, ratings[i].c_str()); // concatenation
		int n = (strlen(st) + 1) / 5; // number of contestants
		for (int i = 0; i < n; ++i) a[i] = st[i * 5] * 1000 + st[i * 5 + 1] * 100 + st[i * 5 + 2] * 10 + st[i * 5 + 3] - '0' * 1111; // atoi
		// my score; rooms; maximum people in a room; remainder
		int c = a[0], room = (n + 19) / 20, mxp = 1 + (n - 1) / room, r = (n - 1) % room + 1; 
		sort(a, a + n, greater<int>());
		double ret1 = 0, ret2 = 0;
		for (int i = 0; i < mxp - 1; ++i){ // if there are mxp - 1 people in my room
			int sum = 0; bool ok = 1;
			for (int j = i * room; j < (i + 1) * room; ++j) // go over the round
				if (a[j] == c) {ok = 0; break;} else sum += a[j]; // if I am in this round
			ret1 += ok ? (double)sum / room : c;
		}
		ret2 = ret1; bool ok = 1; int sum = 0; // if there are mxp people in my room
		for (int i = (mxp - 1) * room; i < n; ++i) // go over the remainder
			if (a[i] == c){ok = 0; break;} else sum += a[i]; // if I am in this round
		ret2 += ok ? (double)sum / r : c;
		return ok ? ret1 / (mxp - 1) * (room - r) / room + ret2 / mxp * r / room : ret2 / mxp;
	}
};

/*
	Everytime, everywhere,
	I will surely get your honest love.
	Daisuke...
		- Daisuke
*/
