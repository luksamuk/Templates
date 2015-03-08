#include <iostream>
#include <cstring>
#include <string>
#include <map>
using namespace std;

bool dehue = false;
static char anagrhue_curr = ' ';
map<char, string> anagrHUEs;
map<string, char> anagrHUEs_rev;

void swap(char* a, char* b) {
	char c = *a;
	*a = *b;
	*b = c;
}

void permute(char* str, int begin, int end)
{
	if(begin == end) {
		string huehue = str;
		if(!dehue)	{
			if(anagrHUEs.find(anagrhue_curr) == anagrHUEs.end())
				anagrHUEs[anagrhue_curr] = huehue;
		}
		else {
			if(anagrHUEs_rev.find(huehue) == anagrHUEs_rev.end())
				anagrHUEs_rev[huehue] = anagrhue_curr;
		}
		anagrhue_curr++;
	}
	else {
		for(int j = begin; j <= end; j++) {
			swap((str + begin), (str + j));
			permute(str, begin + 1, end);
			swap((str + begin), (str + j));
		}
	}
}

int main(int argc, char** argv)
{
	for(int i = 1; i < argc; i++) {
		if(!strcmp(argv[i], "--hue")) {
			dehue = true;
			cout << "DeHUE" << endl;
		}
	}
	string text;
	char c;
	char* anagrhue = new char[10];
	strcpy(anagrhue, "HUEhue");
	permute(anagrhue, 0, strlen(anagrhue) - 1);
	delete [] anagrhue;

	while(true) {
		text = "";
		cout << "> ";
		getline(cin, text);
	
		if(!dehue) {
			for(int i = 0; text[i] != '\0'; i++) {
				cout << anagrHUEs[text.c_str()[i]];
			}
		}
		else {
			int curr = 0;
			while(text[curr] != '\0') {
				char buffer[10];
				text.copy(buffer, 6, curr);
				cout << anagrHUEs_rev[buffer];
				curr += 6;
			}
		}
		cout << endl;
	}
	return 0;
}
