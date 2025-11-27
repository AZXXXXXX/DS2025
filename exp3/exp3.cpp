#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int n;
    vector<vector<int>> g; 
    Graph(int n) : n(n), g(n, vector<int>(n, 0)) {}

    void addEdge(int u, int v, int w = 1) {
        g[u][v] = w;
        g[v][u] = w;
    }

    void printMatrix() {
        cout << "邻接矩阵 (n = " << n << "):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << g[i][j] << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    void BFS(int start) {
        vector<bool> vis(n, false);
        queue<int> q;
        vis[start] = true;
        q.push(start);
        cout << "BFS from " << char('A' + start) << ": ";

        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << char('A' + u) << " ";
            for (int v = 0; v < n; v++)
                if (g[u][v] && !vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
        }
        cout << "\n\n";
    }

    void dfsRec(int u, vector<bool>& vis) {
        vis[u] = true;
        cout << char('A' + u) << " ";
        for (int v = 0; v < n; v++)
            if (g[u][v] && !vis[v])
                dfsRec(v, vis);
    }

    void DFS(int start) {
        vector<bool> vis(n, false);
        cout << "DFS from " << char('A' + start) << ": ";
        dfsRec(start, vis);
        cout << "\n\n";
    }

    void Dijkstra(int start) {
        const int INF = 1e9;
        vector<int> dist(n, INF), vis(n, 0);
        dist[start] = 0;

        for (int i = 0; i < n; i++) {
            int u = -1, best = INF;
            for (int j = 0; j < n; j++)
                if (!vis[j] && dist[j] < best)
                    u = j, best = dist[j];

            if (u == -1) break;
            vis[u] = 1;

            for (int v = 0; v < n; v++)
                if (g[u][v] && dist[u] + g[u][v] < dist[v])
                    dist[v] = dist[u] + g[u][v];
        }

        cout << "Dijkstra distances from " << char('A' + start) << ":\n";
        for (int i = 0; i < n; i++) {
            cout << char('A' + start) << " -> "
                 << char('A' + i) << " : ";
            if (dist[i] == INF) cout << "INF\n";
            else cout << dist[i] << "\n";
        }
        cout << "\n";
    }

    void Prim(int start) {
        const int INF = 1e9;
        vector<int> low(n, INF), vis(n, 0);
        low[start] = 0;
        int total = 0;
        cout << "Prim from " << char('A' + start) << ":\n";

        for (int i = 0; i < n; i++) {
            int u = -1, best = INF;
            for (int j = 0; j < n; j++)
                if (!vis[j] && low[j] < best)
                    best = low[j], u = j;

            if (u == -1) break;
            vis[u] = 1;

            if (u != start) {
                cout << char('A' + u)
                     << " added with weight " << best << "\n";
                total += best;
            }

            for (int v = 0; v < n; v++)
                if (g[u][v] && !vis[v] && g[u][v] < low[v])
                    low[v] = g[u][v];
        }
        cout << "Prim total weight: " << total << "\n\n";
    }

    vector<int> dfn, low, parent;
    vector<bool> isCut;
    int timer;

    void tarjanDFS(int u) {
        dfn[u] = low[u] = ++timer;
        int child = 0;

        for (int v = 0; v < n; v++) {
            if (!g[u][v]) continue;

            if (!dfn[v]) {
                parent[v] = u;
                child++;
                tarjanDFS(v);
                low[u] = min(low[u], low[v]);

                if (parent[u] == -1 && child > 1)
                    isCut[u] = true;
                if (parent[u] != -1 && low[v] >= dfn[u])
                    isCut[u] = true;

            } else if (v != parent[u]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

    void articulationPoints() {
        dfn.assign(n, 0);
        low.assign(n, 0);
        parent.assign(n, -1);
        isCut.assign(n, false);
        timer = 0;

        for (int i = 0; i < n; i++)
            if (!dfn[i]) tarjanDFS(i);

        cout << "关节点: ";
        bool any = false;
        for (int i = 0; i < n; i++)
            if (isCut[i]) {
                cout << char('A' + i) << " ";
                any = true;
            }

        if (!any) cout << "无";
        cout << "\n\n";
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << "==== 图 1 结果 ====\n";

    Graph G1(8);
    // A=0,B=1,C=2,D=3,E=4,F=5,G=6,H=7
    G1.addEdge(0,1,4);
    G1.addEdge(0,3,6);
    G1.addEdge(0,6,7);
    G1.addEdge(1,2,12);
    G1.addEdge(2,3,9);
    G1.addEdge(2,4,1);
    G1.addEdge(2,5,2);
    G1.addEdge(2,7,10);
    G1.addEdge(3,6,2);
    G1.addEdge(3,4,13);
    G1.addEdge(4,6,11);
    G1.addEdge(4,5,5);
    G1.addEdge(4,7,8);
    G1.addEdge(5,7,3);
    G1.addEdge(6,7,14);

    G1.printMatrix();
    G1.BFS(0);
    G1.DFS(0);
    G1.Dijkstra(0);
    G1.Prim(0);
    G1.articulationPoints();

    cout << "==== 图 2 结果 ====\n";

    Graph G2(12);
    // A=0,B=1,C=2,D=3,E=4,F=5,G=6,H=7,I=8,J=9,K=10,L=11
    G2.addEdge(0,1); 
    G2.addEdge(0,4); 
    G2.addEdge(1,5);  
    G2.addEdge(2,3);
    G2.addEdge(2,7); 
    G2.addEdge(2,5);
    G2.addEdge(3,7);
    G2.addEdge(4,5);
    G2.addEdge(4,8);
    G2.addEdge(5,8);
    G2.addEdge(5,6);
    G2.addEdge(5,9);
    G2.addEdge(5,10);
    G2.addEdge(6,10);
    G2.addEdge(9,10);
    G2.addEdge(10,11);

    G2.printMatrix();
    G2.BFS(0);
    G2.DFS(0);
    G2.Dijkstra(0);
    G2.Prim(0);
    G2.articulationPoints();

    return 0;
}
