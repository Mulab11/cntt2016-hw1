/*
	For every line,
	either go back to a history with the longest prefix,
	or append keys to the last line.
*/
#include <bits/stdc++.h>
using namespace std;

class UndoHistory {
	public:
	int minPresses(vector <string> lines) {
		int n = lines.size(), ret = n; // n * 'Enter'
		string last;
		for (int i = 0; i < n; ++i){ // For every line
			int mx = 0;
			for (int j = 0; j < i; ++j){ // For every history
				int p = 0; // Find the longest prefix
				while (p < lines[i].length() && p < lines[j].length() && lines[i][p] == lines[j][p])
					++p;
				if (mx < p) mx = p;
			}
			mx -= 2; // double click costs 2
			if (last == string(lines[i], 0, last.length()) && mx < (int)last.length()) // Append
				mx = last.length();
			ret += lines[i].length() - mx; // Cost
			last = lines[i];
		}
		return ret;
	}
};

/*
	How fast can you go?
		- DeltaMAX
*/

