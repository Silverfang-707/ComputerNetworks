#include <iostream>
#include <vector>
using namespace std;

#define MAX_NODES 10
#define INF 999

class Router {
public:
    int dist[MAX_NODES][MAX_NODES];
    int via[MAX_NODES][MAX_NODES];

    Router() {
        for (int i = 0; i < MAX_NODES; i++) {
            for (int j = 0; j < MAX_NODES; j++) {
                if (i == j) {
                    dist[i][j] = 0;
                } else {
                    dist[i][j] = INF;
                }
                via[i][j] = j;
            }
        }
    }

    void init(int num_nodes, vector<vector<int>> edges) {
        for (auto edge : edges) {
            int src = edge[0];
            int dest = edge[1];
            int weight = edge[2];
            dist[src][dest] = weight;
        }
    }

    void update() {
        int temp[MAX_NODES][MAX_NODES];
        for (int i = 0; i < MAX_NODES; i++) {
            for (int j = 0; j < MAX_NODES; j++) {
                temp[i][j] = dist[i][j];
                via[i][j] = j;
            }
        }

        for (int i = 0; i < MAX_NODES; i++) {
            for (int j = 0; j < MAX_NODES; j++) {
                for (int k = 0; k < MAX_NODES; k++) {
                    if ((temp[i][k] + temp[k][j]) < temp[i][j]) {
                        temp[i][j] = temp[i][k] + temp[k][j];
                        via[i][j] = k;
                    }
                }
            }
        }

        for (int i = 0; i < MAX_NODES; i++) {
            for (int j = 0; j < MAX_NODES; j++) {
                dist[i][j] = temp[i][j];
            }
        }
    }

    void print_routing_table() {
        cout << "Routing Table: " << endl;
        for (int i = 0; i < MAX_NODES; i++) {
            cout << "Node " << i << ": ";
            for (int j = 0; j < MAX_NODES; j++) {
                if (dist[i][j] != INF) {
                    cout << "(" << j << ", " << dist[i][j] << ", " << via[i][j] << ") ";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    Router router;

    int num_nodes = 3;
    vector<vector<int>> edges{{0, 1, 2}, {1, 2, 3}, {2, 0, 4}};
    router.init(num_nodes, edges);

    router.update();
    router.print_routing_table();

    return 0;
}
