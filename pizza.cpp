#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <omp.h>

using namespace std;

struct Client {
  unsigned long id;
  string name;

  vector<string> likes;
  vector<string> dislikes;
  map<string, bool> likes_map;
  map<string, bool> dislikes_map;
};

vector<Client> clients;

int deepest = 0;
set<string> output;

void compute_children(Client *parent, map<unsigned long, bool> visited,
                      map<string, bool> dislikes_map, set<string> ingredients,
                      int layer);

map<unsigned long, int> visited_paths;

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

#pragma omp parallel
  {

#pragma omp for
    for (unsigned long x = 0; x < clients.size(); x++) {
      map<unsigned long, bool> visited;
      visited[clients[x].id] = true;
      compute_children(&clients[x], visited, clients[x].dislikes_map,
                       set<string>(), 1);
    }
  }

  cout << output.size();

  for (auto out : output) {
    cout << " " << out;
  }

  return 0;
}

bool check(set<string> ingredients, Client *client,
           map<string, bool> dislikes_map) {
  for (auto ingredient : ingredients) {
    if (dislikes_map.count(ingredient)) {
      return false;
    }
  }
  for (auto ingredient : client->likes) {
    if (dislikes_map.count(ingredient)) {
      return false;
    }
  }
  return true;
}

void compute_children(Client *client_x, map<unsigned long, bool> visited,
                      map<string, bool> dislikes_map, set<string> ingredients,
                      int layer) {
  for (unsigned long i = 0; i < client_x->likes.size(); i++) {
    ingredients.insert(client_x->likes[i]);
  }

  if (layer > deepest) {
    deepest = layer;
    output = ingredients;
  }

  for (unsigned long y = 0; y < clients.size(); y++) {
    if (!visited.count(clients[y].id)) {
      map<string, bool> next_dislikes_map = dislikes_map;
      for (unsigned long i = 0; i < clients[y].dislikes.size(); i++) {
        next_dislikes_map[clients[y].dislikes[i]] = true;
      }

      if (check(ingredients, &clients[y], next_dislikes_map)) {
        visited[clients[y].id] = true;
        compute_children(&clients[y], visited, next_dislikes_map, ingredients,
                         layer + 1);
      }
    }
  }
}
