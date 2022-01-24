#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Client {
  unsigned long id;
  string name;

  vector<string> likes;
  vector<string> dislikes;
  map<string, bool> likes_map;
  map<string, bool> dislikes_map;

  vector<Client> children;
};

vector<Client> clients;

int deepest = 0;
set<string> output;

void compute_children(Client *parent, vector<Client> *children,
                      map<string, bool> dislikes_map, set<string> ingredients,
                      int layer);

int main() {
  int C;
  cin >> C;

  for (int i = 0; i < C; i++) {
    int L, D;
    clients.push_back(Client());
    clients[i].id = i;

    cin >> L;
    for (int j = 0; j < L; j++) {
      string local;
      cin >> local;

      clients[i].likes.push_back(local);
      clients[i].likes_map[local] = true;
      clients[i].name += local;
    }
    clients[i].name += "_";

    cin >> D;
    for (int j = 0; j < D; j++) {
      string local;
      cin >> local;

      clients[i].dislikes.push_back(local);
      clients[i].dislikes_map[local] = true;
      clients[i].name += local;
    }
  }

  for (unsigned long x = 0; x < clients.size(); x++) {
    compute_children(&clients[x], &clients, clients[x].dislikes_map,
                     set<string>(), 1);
  }

  cout << output.size();

  for (auto out : output) {
    cout << " " << out;
  }

  return 0;
}

void compute_children(Client *parent, vector<Client> *children,
                      map<string, bool> dislikes_map, set<string> ingredients,
                      int layer) {
  vector<Client> clients = *children;

  for (unsigned long y = 0; y < clients.size(); y++) {
    if (parent->id == clients[y].id) {
      continue;
    }

    bool is_candidate = true;
    for (unsigned long i = 0; i < parent->likes.size(); i++) {
      if (clients[y].dislikes_map.count(parent->likes[i]) ||
          dislikes_map.count(parent->likes[i])) {
        is_candidate = false;
        break;
      }
    }

    if (is_candidate) {
      clients[y].children = vector<Client>();
      parent->children.push_back(clients[y]);
    }
  }

  if (layer > deepest) {
    deepest = layer;
    output = ingredients;
  }

  for (unsigned long i = 0; i < parent->likes.size(); i++) {
    ingredients.insert(parent->likes[i]);
  }

  for (unsigned long x = 0; x < parent->children.size(); x++) {
    map<string, bool> next_dislikes_map = dislikes_map;

    for (unsigned long i = 0; i < parent->children[x].dislikes.size(); i++) {
      next_dislikes_map[parent->children[x].dislikes[i]] = true;
    }

    compute_children(&parent->children[x], &parent->children, next_dislikes_map,
                     ingredients, layer + 1);
  }
}
