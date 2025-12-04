#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class CityGraph {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjList; // pasangan (vertex, jarak)
    vector<string> cityNames;
    map<string, int> cityIndex;

public:
    CityGraph(int V) {
        numVertices = V;
        adjList.resize(numVertices);
    }

    void addCity(int index, string name) {
        if (index >= 0 && index < numVertices) {
            cityNames.push_back(name);
            cityIndex[name] = index;
        }
    }

    void addEdge(string city1, string city2, int distance) {
        if (cityIndex.find(city1) == cityIndex.end() || cityIndex.find(city2) == cityIndex.end()) {
            cout << "Kota tidak valid." << endl;
            return;
        }
        int i = cityIndex[city1];
        int j = cityIndex[city2];
        adjList[i].push_back({j, distance});
        adjList[j].push_back({i, distance});
    }

    void displayCities() {
        cout << "\n===== DAFTAR KOTA =====" << endl;
        for (int i = 0; i < cityNames.size(); i++) {
            cout << i + 1 << ". " << cityNames[i] << endl;
        }
    }

    struct PathResult {
        vector<string> path;
        int totalDistance;
    };

    PathResult bfsShortestPath(string startCity, string endCity) {
        PathResult result;
        result.totalDistance = -1;

        if (cityIndex.find(startCity) == cityIndex.end() || cityIndex.find(endCity) == cityIndex.end()) {
            cout << "Kota asal atau tujuan tidak valid." << endl;
            return result;
        }

        int start = cityIndex[startCity];
        int end = cityIndex[endCity];

        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1);
        vector<int> distance(numVertices, 0);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();

            if (currentVertex == end) break;

            for (auto& edge : adjList[currentVertex]) {
                int nextVertex = edge.first;
                int edgeDistance = edge.second;

                if (!visited[nextVertex]) {
                    visited[nextVertex] = true;
                    parent[nextVertex] = currentVertex;
                    distance[nextVertex] = distance[currentVertex] + edgeDistance;
                    q.push(nextVertex);
                }
            }
        }

        //rekonstruksi path, maksudnya mengembalikan jalur
        if (visited[end]) {
            result.totalDistance = distance[end];
            int current = end;
            while (current != -1) {
                result.path.push_back(cityNames[current]);
                current = parent[current];
            }
            reverse(result.path.begin(), result.path.end());
        }
        return result;
    }
};

int main() {
    system("cls");

    CityGraph graph(6);

    //daftar kota
    graph.addCity(0, "Medan");
    graph.addCity(1, "Tebing Tinggi");
    graph.addCity(2, "Berastagi");
    graph.addCity(3, "Pematangsiantar");
    graph.addCity(4, "Sidikalang");
    graph.addCity(5, "Parapat");

    //jarak antar kota (dalam km)
    graph.addEdge("Medan", "Tebing Tinggi", 70);
    graph.addEdge("Medan", "Berastagi", 60);
    graph.addEdge("Tebing Tinggi", "Pematangsiantar", 50);
    graph.addEdge("Berastagi", "Sidikalang", 90);
    graph.addEdge("Berastagi", "Pematangsiantar", 80);
    graph.addEdge("Pematangsiantar", "Parapat", 45);
    graph.addEdge("Pematangsiantar", "Sidikalang", 65);
    graph.addEdge("Sidikalang", "Parapat", 120);

    cout << "Kota yang tersedia: " << endl;
    graph.displayCities();
    //input kota asal
    string startCity, endCity;
    cout << "Masukkan vertex asal: ";
    getline(cin, startCity);

    cout << "Masukkan vertex tujuan: ";
    getline(cin, endCity);

    CityGraph::PathResult result = graph.bfsShortestPath(startCity, endCity);
    if (result.totalDistance != -1) {
        cout << "Rute: ";
        for (int i = 0; i < result.path.size(); i++) {
            cout << result.path[i];
            if (i < result.path.size() - 1) cout << " -> ";
        }
        cout << "\nTotal Jarak: " << result.totalDistance << " km" << endl;
    } else {
        cout << "Rute tidak ditemukan!" << endl;
    }
    return 0;
}