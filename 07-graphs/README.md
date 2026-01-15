# 📚 Topic 7: Graph Traversal (DFS/BFS)

## Overview

Graphs are fundamental data structures in competitive programming. USACO Silver requires understanding graph representation, traversal (DFS/BFS), and common graph problems like finding connected components.

---

## Key Concepts

### 1. Graph Representation

**Adjacency List** (preferred for sparse graphs):

```cpp
#include <vector>
using namespace std;

int n, m;  // n nodes, m edges
vector<vector<int>> adj;  // adj[u] = list of neighbors of u

void buildGraph() {
    adj.resize(n + 1);  // 1-indexed
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);  // For undirected graph
    }
}
```

**Weighted Graph:**

```cpp
vector<vector<pair<int, int>>> adj;  // adj[u] = {{v, weight}, ...}

void addEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});  // For undirected
}
```

### 2. DFS (Depth-First Search)

Explores as deep as possible before backtracking.

```cpp
#include <vector>
using namespace std;

int n;
vector<vector<int>> adj;
vector<bool> visited;

void dfs(int u) {
    visited[u] = true;
    
    // Process node u here
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

void traverseAll() {
    visited.assign(n + 1, false);
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
}
```

**Iterative DFS (avoids stack overflow):**

```cpp
#include <stack>

void dfsIterative(int start) {
    stack<int> st;
    st.push(start);
    
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                st.push(v);
            }
        }
    }
}
```

### 3. BFS (Breadth-First Search)

Explores level by level. **Finds shortest path in unweighted graphs.**

```cpp
#include <vector>
#include <queue>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> dist;

void bfs(int start) {
    dist.assign(n + 1, -1);
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}
```

**BFS with Path Reconstruction:**

```cpp
vector<int> parent;

void bfsWithPath(int start, int end) {
    dist.assign(n + 1, -1);
    parent.assign(n + 1, -1);
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
    
    // Reconstruct path from start to end
    if (dist[end] == -1) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
}
```

### 4. Connected Components

Find all connected components in an undirected graph.

```cpp
int n;
vector<vector<int>> adj;
vector<int> component;  // component[u] = which component node u belongs to

int countComponents() {
    component.assign(n + 1, -1);
    int numComponents = 0;
    
    for (int i = 1; i <= n; i++) {
        if (component[i] == -1) {
            // BFS/DFS to mark all nodes in this component
            queue<int> q;
            q.push(i);
            component[i] = numComponents;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (int v : adj[u]) {
                    if (component[v] == -1) {
                        component[v] = numComponents;
                        q.push(v);
                    }
                }
            }
            
            numComponents++;
        }
    }
    
    return numComponents;
}
```

---

## Common Patterns

### Pattern 1: Cycle Detection (Undirected)

Check if an undirected graph has a cycle.

```cpp
bool hasCycle = false;

void dfsCycle(int u, int parent) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfsCycle(v, u);
        } else if (v != parent) {
            hasCycle = true;  // Back edge found
        }
    }
}
```

### Pattern 2: Cycle Detection (Directed)

Use colors: WHITE (0) = unvisited, GRAY (1) = in current path, BLACK (2) = finished.

```cpp
vector<int> color;  // 0, 1, 2
bool hasCycle = false;

void dfsCycleDirected(int u) {
    color[u] = 1;  // GRAY - currently exploring
    
    for (int v : adj[u]) {
        if (color[v] == 1) {
            hasCycle = true;  // Back edge to node in current path
        } else if (color[v] == 0) {
            dfsCycleDirected(v);
        }
    }
    
    color[u] = 2;  // BLACK - finished
}
```

### Pattern 3: Bipartite Check (Graph Coloring)

Check if graph can be 2-colored.

```cpp
vector<int> colorNode;

bool isBipartite() {
    colorNode.assign(n + 1, -1);
    
    for (int i = 1; i <= n; i++) {
        if (colorNode[i] == -1) {
            queue<int> q;
            q.push(i);
            colorNode[i] = 0;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (int v : adj[u]) {
                    if (colorNode[v] == -1) {
                        colorNode[v] = 1 - colorNode[u];  // Alternate color
                        q.push(v);
                    } else if (colorNode[v] == colorNode[u]) {
                        return false;  // Same color neighbors
                    }
                }
            }
        }
    }
    
    return true;
}
```

### Pattern 4: Functional Graph (Each Node Has One Outgoing Edge)

Common in USACO Silver. Each node points to exactly one other node.

```cpp
int n;
vector<int> succ;  // succ[i] = where node i points to

// Find cycle in functional graph
pair<int, int> findCycle() {  // Returns {cycle_start, cycle_length}
    vector<int> visited(n + 1, 0);
    vector<int> order(n + 1, 0);
    
    int node = 1;
    int step = 1;
    
    while (visited[node] == 0) {
        visited[node] = 1;
        order[node] = step++;
        node = succ[node];
    }
    
    int cycleStart = node;
    int cycleLength = step - order[node];
    
    return {cycleStart, cycleLength};
}
```

### Pattern 5: Tree Traversal (Special Graph)

Trees are connected graphs with N-1 edges and no cycles.

```cpp
vector<vector<int>> adj;
vector<int> parent;
vector<int> depth;
vector<int> subtreeSize;

void dfsTree(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    subtreeSize[u] = 1;
    
    for (int v : adj[u]) {
        if (v != p) {
            dfsTree(v, u, d + 1);
            subtreeSize[u] += subtreeSize[v];
        }
    }
}

// Call with root:
// dfsTree(1, -1, 0);
```

---

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| DFS/BFS | O(V + E) |
| Find connected components | O(V + E) |
| Cycle detection | O(V + E) |
| Bipartite check | O(V + E) |

Where V = number of vertices, E = number of edges.

---

## Common Mistakes

1. **Forgetting to handle disconnected graphs**
   - Loop through all nodes, not just starting from node 1

2. **Not excluding parent in undirected graph DFS**
   - Every edge creates a "back" to parent; don't count as cycle

3. **1-indexed vs 0-indexed**
   - Be consistent; USACO often uses 1-indexed

4. **Stack overflow with recursive DFS**
   - Use iterative BFS/DFS for large graphs (N > 10^5)

5. **Missing edges in input**
   - Remember to add both directions for undirected graphs

---

## Practice Problems

### Easy
| Problem | Source | Link |
|---------|--------|------|
| Building Roads | CSES | [cses.fi](https://cses.fi/problemset/task/1666) |
| Message Route | CSES | [cses.fi](https://cses.fi/problemset/task/1667) |
| Fence Planning | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=944) |
| Moocast | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=668) |

### Medium
| Problem | Source | Link |
|---------|--------|------|
| Building Teams | CSES | [cses.fi](https://cses.fi/problemset/task/1668) |
| Wormhole Sort | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=992) |
| The Great Revegetation | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=920) |
| Closing the Farm | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=644) |
| Round Trip | CSES | [cses.fi](https://cses.fi/problemset/task/1669) |

### Hard
| Problem | Source | Link |
|---------|--------|------|
| Swapity Swap | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1014) |
| Clock Tree | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1016) |
| Maze Tac Toe | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1186) |
| Cycle Finding | CSES | [cses.fi](https://cses.fi/problemset/task/1197) |

---

## Key Takeaways

1. ✅ Use **adjacency list** for graph representation
2. ✅ **BFS** for shortest path in unweighted graphs
3. ✅ **DFS** for exploring/detecting cycles/tree problems
4. ✅ Remember to handle **disconnected** graphs
5. ✅ Track **parent** to avoid false cycle detection in undirected graphs
