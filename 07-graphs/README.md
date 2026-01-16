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

---

## 🧠 Pattern Recognition: When to Use Graph Traversal

### Trigger Phrases

When you see these in a problem, **think graph traversal:**

| Trigger Phrase | Why Graphs? |
|----------------|-------------|
| "**Nodes and edges**" explicitly | Direct graph problem |
| "**Connected**" or "**reachable**" | DFS/BFS connectivity |
| "**Shortest path**" (unweighted) | BFS |
| "**Relationships** between entities" | Model as graph |
| "**Network**" or "**connections**" | Graph structure |
| "**Cycle** detection" | DFS with coloring |
| "**Bipartite**" or "**two groups**" | Graph coloring |
| "**Functional graph**" (each node → one node) | Cycle detection |

### Problem Characteristics

**Graph traversal is likely needed when:**

1. ✅ Input explicitly gives **nodes and edges**
2. ✅ Need to determine **reachability** or **connectivity**
3. ✅ Need **shortest path** in unweighted setting
4. ✅ Need to find **connected components**
5. ✅ Need to detect **cycles**
6. ✅ Need to **color** or **partition** nodes

### Graph vs Flood Fill

| Feature | Use Graph Traversal | Use Flood Fill |
|---------|---------------------|----------------|
| Input type | Node/edge list | 2D grid |
| Structure | Arbitrary connections | Grid adjacency |
| Neighbors | From adjacency list | 4 or 8 directions |

### DFS vs BFS for Graphs

| Use DFS when... | Use BFS when... |
|-----------------|-----------------|
| Detecting cycles | Need **shortest path** |
| Checking connectivity | Need **distance** from source |
| Topological sort | Level-order processing |
| Finding any path | Finding shortest path |

### Pattern Recognition Exercises

**Exercise 1:** Graph traversal or not?

| Problem | Graph? | Why? |
|---------|--------|------|
| "N people, M friendships. Count friend groups." | | |
| "Grid maze, find shortest path" | | |
| "N computers, M cables. Are all connected?" | | |
| "Find minimum cost to connect all cities" | | |
| "Assign N tasks to M workers optimally" | | |

<details>
<summary>Answers</summary>

1. **Yes** - Connected components (each friend group is a component)
2. **Flood fill** - Grid-based, not general graph
3. **Yes** - Check if graph is connected (one component)
4. **Yes** - Minimum Spanning Tree (MST)
5. **No** - This is assignment/matching, different technique

</details>

**Exercise 2:** DFS or BFS?

| Problem | DFS or BFS? | Why? |
|---------|-------------|------|
| "Find if graph has a cycle" | | |
| "Shortest path from A to B (unweighted)" | | |
| "Check if graph is bipartite" | | |
| "Count connected components" | | |
| "Find path that visits all nodes" | | |

<details>
<summary>Answers</summary>

1. **DFS** - Track visited states, detect back edges
2. **BFS** - BFS gives shortest path in unweighted graphs
3. **Either** - Usually BFS (natural level coloring)
4. **Either** - Both work, DFS often simpler
5. **DFS** - With backtracking (Hamiltonian path)

</details>

**Exercise 3:** Model as graph

"There are N cows. Cow i hates cow hate[i]. If two cows that hate each other are in the same barn, they fight. Can we split cows into 2 barns with no fights?"

1. What are the nodes? _____________
2. What are the edges? _____________
3. What graph problem is this? _____________

<details>
<summary>Answers</summary>

1. Nodes = cows (N nodes)
2. Edges = hate relationships (cow i -- hate[i])
3. **Bipartite check** - Can we 2-color the graph?

</details>

### Quick Decision Flowchart

```
Is input NODE/EDGE based (not a grid)?
  │
  ├─ NO → Consider flood fill (if grid) or other technique
  │
  └─ YES → What do you need?
              │
              ├─ Connectivity/components → DFS or BFS
              │
              ├─ Shortest path (unweighted) → BFS
              │
              ├─ Cycle detection → DFS
              │
              ├─ Bipartite check → BFS/DFS with coloring
              │
              └─ Weighted shortest path → Dijkstra (Gold level)
```

---

## Key Takeaways

1. ✅ Use **adjacency list** for graph representation
2. ✅ **BFS** for shortest path in unweighted graphs
3. ✅ **DFS** for exploring/detecting cycles/tree problems
4. ✅ Remember to handle **disconnected** graphs
5. ✅ Track **parent** to avoid false cycle detection in undirected graphs
6. ✅ **Recognition:** Nodes + edges + connectivity/reachability → Think graph traversal!