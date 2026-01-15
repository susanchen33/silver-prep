# 📚 Topic 6: Flood Fill (Grid DFS/BFS)

## Overview

Flood fill is the technique of exploring connected regions in a 2D grid. It's implemented using **DFS** or **BFS** and appears frequently in USACO Silver problems.

---

## Key Concepts

### 1. Grid Representation

```cpp
#include <vector>
#include <string>
using namespace std;

int n, m;  // Rows and columns
vector<string> grid;  // Character grid
// OR
vector<vector<int>> grid;  // Integer grid

// 4-directional movement (up, down, left, right)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// 8-directional movement (includes diagonals)
int dx8[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy8[] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Check if coordinates are valid
bool inBounds(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}
```

### 2. DFS Flood Fill (Recursive)

```cpp
#include <vector>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<bool>> visited;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m) return;  // Out of bounds
    if (visited[x][y]) return;  // Already visited
    if (grid[x][y] == '#') return;  // Wall/obstacle
    
    visited[x][y] = true;
    
    // Explore all 4 directions
    for (int d = 0; d < 4; d++) {
        dfs(x + dx[d], y + dy[d]);
    }
}

int countComponents() {
    visited.assign(n, vector<bool>(m, false));
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                dfs(i, j);
                count++;
            }
        }
    }
    
    return count;
}
```

### 3. BFS Flood Fill (Iterative)

BFS is useful when you need **shortest path** or want to avoid stack overflow.

```cpp
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<int>> dist;  // Distance from start

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void bfs(int startX, int startY) {
    dist.assign(n, vector<int>(m, -1));  // -1 = not visited
    queue<pair<int, int>> q;
    
    q.push({startX, startY});
    dist[startX][startY] = 0;
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (grid[nx][ny] == '#') continue;
            if (dist[nx][ny] != -1) continue;  // Already visited
            
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
}

int shortestPath(int x1, int y1, int x2, int y2) {
    bfs(x1, y1);
    return dist[x2][y2];  // -1 if unreachable
}
```

### 4. Component Size & Properties

Track properties of each component.

```cpp
#include <vector>
using namespace std;

int n, m;
vector<string> grid;
vector<vector<int>> component;  // Component ID for each cell

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

int currentSize;
int minX, maxX, minY, maxY;

void dfs(int x, int y, int id) {
    if (x < 0 || x >= n || y < 0 || y >= m) return;
    if (component[x][y] != -1 || grid[x][y] == '#') return;
    
    component[x][y] = id;
    currentSize++;
    minX = min(minX, x);
    maxX = max(maxX, x);
    minY = min(minY, y);
    maxY = max(maxY, y);
    
    for (int d = 0; d < 4; d++) {
        dfs(x + dx[d], y + dy[d], id);
    }
}

void findComponents() {
    component.assign(n, vector<int>(m, -1));
    int id = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && component[i][j] == -1) {
                currentSize = 0;
                minX = maxX = i;
                minY = maxY = j;
                
                dfs(i, j, id);
                
                // Now currentSize, minX, maxX, minY, maxY describe component id
                id++;
            }
        }
    }
}
```

---

## Common Patterns

### Pattern 1: Counting Regions

Count connected regions of same type.

```cpp
// "Counting Rooms" style problem
int countRooms() {
    visited.assign(n, vector<bool>(m, false));
    int rooms = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                dfs(i, j);
                rooms++;
            }
        }
    }
    
    return rooms;
}
```

### Pattern 2: Finding Perimeter

Calculate perimeter of a region.

```cpp
int perimeter;

void dfsPerimeter(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] != 'X') {
        perimeter++;  // Edge of region
        return;
    }
    if (visited[x][y]) return;
    
    visited[x][y] = true;
    
    for (int d = 0; d < 4; d++) {
        dfsPerimeter(x + dx[d], y + dy[d]);
    }
}
```

### Pattern 3: Multi-Source BFS

Start BFS from multiple sources simultaneously.

```cpp
// Distance to nearest 'X' from each cell
void multiSourceBFS() {
    dist.assign(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    
    // Add all sources
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'X') {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (dist[nx][ny] != -1) continue;
            
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
}
```

### Pattern 4: Flood Fill with State

Track additional state during flood fill.

```cpp
// Example: Find if path exists that collects key then reaches door
struct State {
    int x, y;
    bool hasKey;
};

bool canReachDoor(int startX, int startY) {
    vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(m, vector<bool>(2, false)));
    queue<State> q;
    
    q.push({startX, startY, false});
    visited[startX][startY][0] = true;
    
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        
        if (grid[cur.x][cur.y] == 'D' && cur.hasKey) {
            return true;  // Reached door with key!
        }
        
        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];
            bool key = cur.hasKey;
            
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (grid[nx][ny] == '#') continue;
            
            if (grid[nx][ny] == 'K') key = true;
            
            if (!visited[nx][ny][key]) {
                visited[nx][ny][key] = true;
                q.push({nx, ny, key});
            }
        }
    }
    
    return false;
}
```

---

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| DFS/BFS flood fill | O(N × M) |
| Count components | O(N × M) |
| Shortest path (BFS) | O(N × M) |

Each cell is visited at most once → O(N × M) for the entire grid.

---

## Common Mistakes

1. **Stack overflow with DFS**
   - For large grids (N × M > 10^6), use iterative BFS instead
   - Or increase stack size: `ulimit -s unlimited` (Linux)

2. **Forgetting bounds check**
   - Always check `0 <= x < n && 0 <= y < m`

3. **Wrong direction arrays**
   - Double-check dx, dy arrays match intended directions
   - Don't mix up rows (x) and columns (y)

4. **Not marking visited immediately**
   - In BFS, mark visited when adding to queue, not when popping

5. **Off-by-one in grid indexing**
   - Be consistent: 0-indexed or 1-indexed

---

## Practice Problems

### Easy
| Problem | Source | Link |
|---------|--------|------|
| Counting Rooms | CSES | [cses.fi](https://cses.fi/problemset/task/1192) |
| Cross Country Skiing | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=380) |
| Where's Bessie | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=740) |

### Medium
| Problem | Source | Link |
|---------|--------|------|
| Build Gates | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=596) |
| Why Did the Cow Cross the Road III | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=716) |
| Switching on the Lights | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=570) |
| Mooyo Mooyo | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=860) |
| Icy Perimeter | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=895) |
| Labyrinth | CSES | [cses.fi](https://cses.fi/problemset/task/1193) |

### Hard
| Problem | Source | Link |
|---------|--------|------|
| Snow Boots | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=811) |
| Monster | CSES | [cses.fi](https://cses.fi/problemset/task/1194) |
| Fire | Codeforces | [codeforces.com](https://codeforces.com/problemset/problem/35/E) |

---

## Key Takeaways

1. ✅ Flood fill = DFS/BFS on a grid
2. ✅ Use **BFS** for shortest path, **DFS** for simpler traversal
3. ✅ Always check bounds and visited status
4. ✅ Multi-source BFS starts from all sources simultaneously
5. ✅ Track component properties (size, perimeter, bounding box) during traversal
