# 📚 Topic 1: Sorting & Custom Comparators

## Overview

Sorting is fundamental to competitive programming. Many Silver problems require sorting data before processing, and custom comparators allow you to sort by complex criteria.

---

## Key Concepts

### 1. Standard Sorting

C++ provides `std::sort()` which runs in **O(N log N)** time.

```cpp
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {5, 2, 8, 1, 9};
    
    // Sort ascending (default)
    sort(arr.begin(), arr.end());
    // Result: {1, 2, 5, 8, 9}
    
    // Sort descending
    sort(arr.begin(), arr.end(), greater<int>());
    // Result: {9, 8, 5, 2, 1}
    
    return 0;
}
```

### 2. Custom Comparators

When you need to sort by custom criteria, use a comparator function.

**A comparator returns `true` if the first argument should come BEFORE the second.**

```cpp
#include <algorithm>
#include <vector>
using namespace std;

struct Cow {
    string name;
    int milk;
    int weight;
};

// Method 1: Comparator function
bool compareMilk(const Cow& a, const Cow& b) {
    return a.milk > b.milk;  // Sort by milk descending
}

// Method 2: Lambda function
auto compareLambda = [](const Cow& a, const Cow& b) {
    return a.weight < b.weight;  // Sort by weight ascending
};

// Method 3: Operator overloading (for structs)
struct Event {
    int time;
    int type;  // 0 = start, 1 = end
    
    bool operator<(const Event& other) const {
        if (time != other.time) return time < other.time;
        return type < other.type;  // Start before end if same time
    }
};

int main() {
    vector<Cow> cows = {{"Bessie", 10, 500}, {"Elsie", 15, 400}};
    
    sort(cows.begin(), cows.end(), compareMilk);
    sort(cows.begin(), cows.end(), compareLambda);
    
    vector<Event> events;
    sort(events.begin(), events.end());  // Uses operator<
    
    return 0;
}
```

### 3. Sorting Pairs and Tuples

Pairs and tuples sort lexicographically (first element, then second, etc.).

```cpp
vector<pair<int, int>> points = {{3, 2}, {1, 5}, {3, 1}};
sort(points.begin(), points.end());
// Result: {{1, 5}, {3, 1}, {3, 2}}
// Sorted by first element, then by second

// Sort by second element
sort(points.begin(), points.end(), [](auto& a, auto& b) {
    return a.second < b.second;
});
```

### 4. Coordinate Compression

Coordinate compression maps large values to smaller indices while preserving order.

```cpp
vector<int> arr = {1000000, 5, 999999, 5, 100};

// Step 1: Create sorted, unique copy
vector<int> sorted_arr = arr;
sort(sorted_arr.begin(), sorted_arr.end());
sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());
// sorted_arr = {5, 100, 999999, 1000000}

// Step 2: Map original values to compressed indices
for (int& x : arr) {
    x = lower_bound(sorted_arr.begin(), sorted_arr.end(), x) - sorted_arr.begin();
}
// arr = {3, 0, 2, 0, 1}
```

---

## Common Patterns

### Pattern 1: Event-Based Sorting

Many problems involve processing events in sorted order.

```cpp
struct Event {
    int position;
    int type;  // +1 for start, -1 for end
};

vector<Event> events;
// Add start and end events for each interval
for (auto& interval : intervals) {
    events.push_back({interval.start, +1});
    events.push_back({interval.end, -1});
}

sort(events.begin(), events.end(), [](auto& a, auto& b) {
    if (a.position != b.position) return a.position < b.position;
    return a.type < b.type;  // End before start at same position
});

int active = 0;
for (auto& e : events) {
    active += e.type;
    // Process...
}
```

### Pattern 2: Sweep Line

Process sorted events while maintaining state.

```cpp
// Count maximum overlapping intervals
vector<pair<int, int>> intervals;  // {start, end}

vector<pair<int, int>> events;  // {time, type}
for (auto& [s, e] : intervals) {
    events.push_back({s, 1});   // +1 at start
    events.push_back({e, -1});  // -1 at end
}
sort(events.begin(), events.end());

int current = 0, maxOverlap = 0;
for (auto& [time, delta] : events) {
    current += delta;
    maxOverlap = max(maxOverlap, current);
}
```

---

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| `sort()` | O(N log N) |
| `stable_sort()` | O(N log N) |
| `lower_bound()` | O(log N) |
| `unique()` | O(N) |

---

## Common Mistakes

1. **Incorrect comparator logic**
   - Comparator must be a strict weak ordering
   - Never return `true` for equal elements (`a < b` when `a == b`)

2. **Modifying during iteration**
   - Don't modify a container while iterating with iterators

3. **Off-by-one in bounds**
   - Remember `end()` points PAST the last element

4. **Integer overflow in comparisons**
   - Use subtraction carefully: `a.x - b.x` can overflow

---

## Practice Problems

### Easy
| Problem | Source | Link |
|---------|--------|------|
| Lifeguards | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=786) |
| Sort a List | CSES | [cses.fi](https://cses.fi/problemset/task/1621) |

### Medium
| Problem | Source | Link |
|---------|--------|------|
| Rental Service | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=787) |
| Mountain View | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=896) |
| Convention | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=858) |
| Movie Festival | CSES | [cses.fi](https://cses.fi/problemset/task/1629) |

### Hard
| Problem | Source | Link |
|---------|--------|------|
| Out of Sorts | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=834) |
| Berry Picking | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=990) |
| Cow Dance Show | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=690) |
| Social Distancing | USACO Silver | [usaco.org](http://usaco.org/index.php?page=viewproblem2&cpid=1038) |

---

## Key Takeaways

1. ✅ Master `std::sort()` with custom comparators
2. ✅ Learn to convert problems into sorting + sweep line
3. ✅ Practice coordinate compression
4. ✅ Understand when to sort by different criteria
5. ✅ Always verify comparator is a strict weak ordering
