# 🧠 Pattern Recognition: When to Use Graph Traversal

## Trigger Phrases

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

---

## Problem Characteristics

**Graph traversal is likely needed when:**

1. ✅ Input explicitly gives **nodes and edges**
2. ✅ Need to determine **reachability** or **connectivity**
3. ✅ Need **shortest path** in unweighted setting
4. ✅ Need to find **connected components**
5. ✅ Need to detect **cycles**
6. ✅ Need to **color** or **partition** nodes

---

## Graph vs Flood Fill

| Feature | Use Graph Traversal | Use Flood Fill |
|---------|---------------------|----------------|
| Input type | Node/edge list | 2D grid |
| Structure | Arbitrary connections | Grid adjacency |
| Neighbors | From adjacency list | 4 or 8 directions |

---

## DFS vs BFS for Graphs

| Use DFS when... | Use BFS when... |
|-----------------|-----------------|
| Detecting cycles | Need **shortest path** |
| Checking connectivity | Need **distance** from source |
| Topological sort | Level-order processing |
| Finding any path | Finding shortest path |

---

## Pattern Recognition Exercises

### Exercise 1: Graph traversal or not?

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

### Exercise 2: DFS or BFS?

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

### Exercise 3: Model as graph

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

---

## Quick Decision Flowchart

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

## Key Recognition Rule

> **Nodes + edges + connectivity/reachability → Think graph traversal!**
