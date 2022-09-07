#include <ctime>
#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include<sstream>
#include<iterator>
#include<algorithm>
#include <ctime>
using namespace std;
//creates randomized strings and prints the ones that match
void gen_random(set<string> dictionary) {
    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz"
        " ";
    string tmp_s;
    int bigSize=0;
    while(!dictionary.empty()) {
        while (true) {
            char character = alphanum[rand() % (sizeof(alphanum) - 1)];
            if (character != ' ') {
                tmp_s += character;
            }
            else{
                if (dictionary.find(tmp_s)!=dictionary.end()) {
                    if (tmp_s.size() > bigSize) {
                        bigSize = tmp_s.size();
                    }
                    cout << "string found:\t" << tmp_s << "\twords reamaining: " << dictionary.size() <<"\tBiggest string found:\t" <<bigSize << endl;
                    dictionary.erase(tmp_s);
                }
                tmp_s = "";
                break;
            }
        }
    }
}
set<string> getSet(string filename) {
    ifstream infile(filename);

    string line;
    set<string> rawDictionary;
    set<string> dictionary;
    while(getline(infile, line)) {
        stringstream ss(line);
        istream_iterator<string>begin(ss);
        istream_iterator<string> end;
        vector<string> splitStrings(begin, end);

        for (auto& s: splitStrings) {
            rawDictionary.insert(s);
        }
    }
    for (string s : rawDictionary) {
        for (int i = 0, len = s.size(); i < len; i++) {
            if (ispunct(s[i])) {
                s.erase(i--, 1);
                len = s.size();
            }
        }
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        dictionary.insert(s);
    }
    return dictionary;
}
int main(int argc, char* argv[]) {
    srand((unsigned)time(NULL));
    string filename;
    cout << "input file name" << endl;
    cin >> filename;
    set<string> dictionary = getSet(filename);
    gen_random(dictionary);
    return 0;
}