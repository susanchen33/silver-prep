# 🧠 Pattern Recognition: When to Use Trees

## Trigger Phrases

When you see these in a problem, **think trees:**

| Trigger Phrase | Why Trees? |
|----------------|------------|
| "**N nodes, N-1 edges, connected**" | Definition of a tree |
| "**Hierarchy**" or "**parent-child**" | Tree structure |
| "**Subtree**" queries | DFS on rooted tree |
| "**Path** between two nodes" | Unique path in tree |
| "**Root**" mentioned | Rooted tree operations |
| "**Ancestor**" or "**descendant**" | Tree relationships |
| "**Diameter** of tree" | Longest path problem |
| "**Distance** between nodes" | LCA or BFS |

---

## Problem Characteristics

**Tree algorithms are likely needed when:**

1. ✅ Input is **N nodes with N-1 edges** (connected)
2. ✅ Problem mentions **subtrees** or **ancestors**
3. ✅ Need to find **path** between nodes (unique in trees)
4. ✅ Need to compute values for **all subtrees**
5. ✅ Need **distance** between arbitrary pairs
6. ✅ Problem has hierarchical structure

---

## Tree vs General Graph

| Feature | Tree | General Graph |
|---------|------|---------------|
| Edges | N-1 | Any number |
| Cycles | None | May have cycles |
| Path A to B | Unique | Multiple possible |
| Connected | Always (by definition) | Not guaranteed |

---

## Common Tree Operations

| Operation | Technique | Complexity |
|-----------|-----------|------------|
| Subtree sum/count | DFS accumulation | O(N) |
| Diameter | Two BFS/DFS | O(N) |
| Distance between u,v | LCA | O(log N) per query |
| All distances from node | BFS | O(N) |
| Subtree range queries | Euler tour + segment tree | O(log N) per query |

---

## Pattern Recognition Exercises

### Exercise 1: Tree problem or not?

| Problem | Tree? | Why? |
|---------|-------|------|
| "Company hierarchy: each employee has one boss" | | |
| "N cities connected by N roads" | | |
| "N nodes, N-1 edges, all connected" | | |
| "Binary search tree operations" | | |
| "Find shortest path in undirected graph" | | |

<details>
<summary>Answers</summary>

1. **Yes** - Classic tree structure (each node has one parent)
2. **No** - N nodes, N edges means there's a cycle (not a tree)
3. **Yes** - This is the definition of a tree
4. **Yes** - BST is a type of tree
5. **Maybe** - If it's a tree use tree distance, otherwise BFS

</details>

### Exercise 2: Which tree technique?

| Problem | Technique |
|---------|-----------|
| "Sum of values in subtree of node X" | |
| "Longest path in the tree" | |
| "Distance between node A and node B" | |
| "For each node, sum of distances to all other nodes" | |
| "Find lowest common ancestor of two nodes" | |

<details>
<summary>Answers</summary>

1. **DFS subtree accumulation** - Compute during traversal
2. **Tree diameter** - Two BFS/DFS from endpoints
3. **LCA** - dist(A,B) = depth[A] + depth[B] - 2*depth[LCA]
4. **Rerooting DP** - Compute for root, then propagate
5. **Binary lifting** - Preprocess ancestors, query in O(log N)

</details>

### Exercise 3: Design the approach

"Given a tree, for each node, find the size of its subtree."

1. How do you root the tree? _____________
2. What do you compute during DFS? _____________
3. In what order do you process? _____________
4. What's the time complexity? _____________

<details>
<summary>Answers</summary>

1. Pick any node as root (often node 1)
2. subtreeSize[u] = 1 + sum of subtreeSize[child] for all children
3. Post-order: process children before parent
4. O(N) - visit each node once

</details>

---

## Quick Decision Flowchart

```
Is input N nodes with N-1 edges (connected)?
  │
  ├─ NO → Not a tree (use general graph techniques)
  │
  └─ YES → What do you need?
              │
              ├─ Subtree properties → DFS from root
              │
              ├─ Diameter → Two BFS/DFS
              │
              ├─ Distance queries → LCA (binary lifting)
              │
              ├─ Path between nodes → LCA for path, DFS for values
              │
              └─ All distances from one node → Single BFS/DFS
```

---

## Key Recognition Rule

> **N-1 edges + connected + subtrees/paths → Think trees!**
