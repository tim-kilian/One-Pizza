#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<string, double> vals;
vector<string> out;

int main() {
  int n;
  cin >> n;

  for (int j = 0; j < n; j++) {
    int likes, dislikes;
    cin >> likes;
    for (int i = 0; i < likes; i++) {
      string local;
      cin >> local;
      vals[local] += (1 / (double)likes);
    }
    cin >> dislikes;
    for (int i = 0; i < dislikes; i++) {
      string local;
      cin >> local;
      vals[local] -= (1 / (double)dislikes);
    }
  }

  for (auto it : vals) {
    if (it.second > 0)
      out.push_back(it.first);
  }

  cout << out.size() << " ";

  for (auto it : out) {
    cout << it << " ";
  }
  
  return 0;
}
