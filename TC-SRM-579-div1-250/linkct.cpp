#include <bits/stdc++.h>
using namespace std;

class UndoHistory{
public:
	set <string> undo;
	int minPresses(vector <string> lines){
		int i, j, ans = lines[0].length() + 1;
		undo.insert("");
		for(i = 0; i < int(lines[0].length()); ++ i)
			undo.insert(lines[0].substr(0, i + 1));
		for(i = 1; i < int(lines.size()); ++ i){
			++ ans;
			for(j = lines[i].length(); j >= 0; -- j){
				if(undo.count(lines[i].substr(0, j)))
					break;
				undo.insert(lines[i].substr(0, j));
			}
			if(lines[i].length() >= lines[i - 1].length() && lines[i].substr(0, lines[i - 1].length()) == lines[i - 1])
				ans += min(2 + lines[i].length() - j, lines[i].length() - lines[i - 1].length());
			else ans += 2 + lines[i].length() - j;
		} return ans;
	}
};
