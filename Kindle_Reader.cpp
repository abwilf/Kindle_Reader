//
//  Kindle Reader
//	by Alex Wilf 3/7/18

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <utility>
#include <sys/stat.h>	// for mkdir
#include <unistd.h>	// for home directory
#include <sys/types.h>
#include <pwd.h>

using namespace std;

// book title, book notes
using Map_Type = unordered_map<string, vector<string>>;



int main() {
	Map_Type m;
	ifstream is("My Clippings.txt");
	string str;
	int counter = 0;
	Map_Type::iterator recent;
	
	// read everything into a map
	while (getline(is, str)) {
		if (str[0] == '=' ) {
			counter = 0;
		}
		else if (str[0] == '-') {
			counter = 1;
		}
		else if (str[0] == '\r' || str[0] == '\n') {
			continue;
		}
		else if (counter % 2 == 0) {	// title
			recent = m.insert(make_pair(str, vector<string>())).first;
			++counter;
		}
		else {	// notes
			recent->second.push_back(str);
			++counter;
		}
	}
	
	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;	// home directory
	
	string path(homedir);
	path += "/Desktop/Kindle Notes/";

	mkdir(path.c_str(), 0755);

	// write
	for (auto it : m) {
		string title = path + it.first + ".txt";
		ofstream of(title);
		of << it.first << "\n------------------\n\n";
		for (auto j : it.second) {
			of << j << "\n\n";
		}
		of << "\n";
	}
	
	return 0;
}
