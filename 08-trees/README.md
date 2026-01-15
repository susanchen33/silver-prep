# 📚 Topic 8: Trees

## Overview

Trees are connected graphs with **N nodes** and **N-1 edges** and **no cycles**. They appear frequently in USACO Silver, especially problems involving subtrees, paths, and tree traversal.

---

## Key Concepts

### 1. Tree Properties

- **N nodes, N-1 edges** (always)
- **Exactly one path** between any two nodes
- **No cycles**
- Can be **rooted** (pick a root) or **unrooted**
- **Leaf:** node with degree 1 (or no children if rooted)

### 2. Tree Representation

```cpp
#include <vector>
using namespace std;

int n;
vector<vector<int>> adj;  // Adjacency list

void readTree() {
    cin >> n;
    adj.resize(n + 1);
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}
```

### 3. Rooting a Tree

Choose a root and establish parent-child relationships.

```cpp
vector<int> parent;
vector<int> depth;
vector<vector<int>> children;

void rootTree(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    
    for (int v : adj[u]) {
        if (v != p) {
            children[u].push_back(v);
            rootTree(v, u, d + 1);
        }
    }
}

void initRootedTree(int root) {
    parent.assign(n + 1, -1);
    depth.assign(n + 1, 0);
    children.resize(n + 1);
    
    rootTree(root, -1, 0);
}
```

### 4. Subtree Queries

Compute properties for each subtree.

```cpp
vector<int> subtreeSize;
vector<long long> subtreeSum;
vector<int> value;  // Value at each node

void dfsSubtree(int u, int p) {
    subtreeSize[u] = 1;
    subtreeSum[u] = value[u];
    
    for (int v : adj[u]) {
        if (v != p) {
            dfsSubtree(v, u);
            subtreeSize[u] += subtreeSize[v];
            subtreeSum[u] += subtreeSum[v];
        }
    }
}
```

### 5. Tree Diameter

Longest path in a tree. Can be found with **two BFS/DFS**.

```cpp
pair<int, int> bfsFarthest(int start) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    
    int farthestNode = start;
    int maxDist = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        if (dist[u] > maxDist) {
            maxDist = dist[u];
            farthestNode = u;
        }
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    return {farthestNode, maxDist};
}

int treeDiameter() {
    // Step 1: Find farthest node from any node (say node 1)
    auto [nodeA, dist1] = bfsFarthest(1);
    
    // Step 2: Find farthest node from nodeA
    auto [nodeB, diameter] = bfsFarthest(nodeA);
    
    return diameter;
}
```

### 6. Euler Tour (DFS Order)

Flatten tree into array for range queries on subtrees.

```cpp
vector<int> tin, tout;  // Entry and exit times
int timer = 0;

void eulerTour(int u, int p) {
    tin[u] = timer++;
    
    for (int v : adj[u]) {
        if (v != p) {
            eulerTour(v, u);
        }
    }
    
    tout[u] = timer;  // Or timer - 1 depending on convention
}

// After Euler tour:
// - Subtree of u contains nodes with tin[v] in [tin[u], tout[u])
// - Can use range queries on the flattened array
```

---

## Common Patterns

### Pattern 1: Counting Paths Through Each Edge

For each edge, count how many paths pass through it.

```cpp
// Each edge (u, v) where v is child of u:
// Number of paths = subtreeSize[v] * (n - subtreeSize[v])

long long countAllPaths() {
    long long total = 0;
    
    for (int u = 1; u <= n; u++) {
        for (int v : children[u]) {
            long long pathsThroughEdge = (long long)subtreeSize[v] * (n - subtreeSize[v]);
            total += pathsThroughEdge;
        }
    }
    
    return total;
}
```

### Pattern 2: Sum of Distances from Each Node

Calculate sum of distances from each node to all other nodes.

```cpp
vector<long long> sumDist;

void dfs1(int u, int p) {
    subtreeSize[u] = 1;
    sumDist[u] = 0;
    
    for (int v : adj[u]) {
        if (v != p) {
            dfs1(v, u);
            subtreeSize[u] += subtreeSize[v];
            sumDist[u] += sumDist[v] + subtreeSize[v];
        }
    }
}

void dfs2(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            // When moving from u to v:
            // - Nodes in v's subtree get 1 closer
            // - Other nodes get 1 farther
            sumDist[v] = sumDist[u] - subtreeSize[v] + (n - subtreeSize[v]);
            dfs2(v, u);
        }
    }
}

void computeAllDistances(int root) {
    subtreeSize.assign(n + 1, 0);
    sumDist.assign(n + 1, 0);
    
    dfs1(root, -1);  // Compute for root
    dfs2(root, -1);  // Propagate to all nodes
}
```

### Pattern 3: Lowest Common Ancestor (LCA) - Binary Lifting

Find LCA of two nodes in O(log N).

```cpp
const int LOG = 20;  // log2(max N)
vector<vector<int>> up;  // up[u][k] = 2^k ancestor of u

void preprocessLCA(int root) {
    up.assign(n + 1, vector<int>(LOG, -1));
    
    function<void(int, int)> dfs = [&](int u, int p) {
        up[u][0] = p;
        for (int k = 1; k < LOG; k++) {
            if (up[u][k-1] != -1) {
                up[u][k] = up[up[u][k-1]][k-1];
            }
        }
        
        for (int v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs(v, u);
            }
        }
    };
    
    depth.assign(n + 1, 0);
    dfs(root, -1);
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    int diff = depth[u] - depth[v];
    for (int k = 0; k < LOG; k++) {
        if ((diff >> k) & 1) {
            u = up[u][k];
        }
    }
    
    if (u == v) return u;
    
    for (int k = LOG - 1; k >= 0; k--) {
        if (up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    
    return up[u][0];
}

int distance(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}
```

### Pattern 4: Centroid of a Tree

Node whose removal creates subtrees of size ≤ N/2.

```cpp
int findCentroid(int root) {
    // First compute subtree sizes
    function<void(int, int)> computeSize = [&](int u, int p) {
        subtreeSize[u] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                computeSize(v, u);
                subtreeSize[u] += subtreeSize[v];
            }
        }
    };
    computeSize(root, -1);
    
    // Find centroid
    function<int(int, int)> dfs = [&](int u, int p) -> int {
        for (int v : adj[u]) {
            if (v != p && subtreeSize[v] > n / 2) {
                return dfs(v, u);
            }
        }
        return u;
    };
    
    return dfs(root, -1);
}
```

---

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| Tree traversal (DFS/BFS) | O(N) |
| Subtree size computation | O(N) |
| Tree diameter | O(N) |
| Euler tour | O(N) |
| LCA preprocessing | O(N log N) |
| LCA query | O(log N) |

---

## Common Mistakes

1. **Forgetting to exclude parent**
   - When traversing: `if (v != parent)` is crucial

2. **Confusing rooted vs unrooted**
   - Unrooted: edges go both ways
   - Rooted: clear parent-child relationship

3. **Off-by-one in Euler tour**
   - Clarify: is `tout[u]` inclusive or exclusive?

4. **Integer overflow in path counting**
   - `subtreeSize[v] * (n - subtreeSize[v])` can overflow int

5. **Not handling single-node tree**
   - Edge case: N = 1, no edges

---

## Practice Problems

### Easy
| Problem | Source | Link |
|---------|--------|------|
| Subordinates | CSES | [cses.fi](https://cses.fi/problemset/task/1674) |
| Tree Distances I | CSES | [cses.fi](https://cses.fi/problemset/task/1132) |
| Tree Distances II | CSES | [cses.fi](https://cses.fi/problemset/task/1133) |

### Medium
| Problem | Source | Link |
|---------|--------|------|
| Tree Diameter | CSES | [cses.fi](https://cses.fi/problemset/task/1131) |
| Milk Visits | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=968) |
| Clock Tree | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1016) |
| Max Flow | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=714) |
| Cow Land | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=921) |

### Hard
| Problem | Source | Link |
|---------|--------|------|
| Barn Tree | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1254) |
| Distance Queries | CSES | [cses.fi](https://cses.fi/problemset/task/1135) |
| Company Queries I | CSES | [cses.fi](https://cses.fi/problemset/task/1687) |
| Cow at Large | USACO Gold | More advanced |

---

## Key Takeaways

1. ✅ Trees have **N-1 edges**, unique paths, no cycles
2. ✅ **Root the tree** to establish parent-child relationships
3. ✅ **Subtree queries** use DFS to accumulate values
4. ✅ **Tree diameter** = two BFS/DFS from endpoints
5. ✅ **Euler tour** flattens tree for range queries
6. ✅ **LCA** enables efficient path queries
