/*
 * USACO Silver Template
 * Standard C++ competitive programming template
 */

#include <bits/stdc++.h>
using namespace std;

// Type aliases for convenience
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;
typedef vector<string> vs;

// Shortcuts
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

// Constants
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

// Direction arrays for grid problems
const int dx[] = {0, 0, 1, -1};  // right, left, down, up
const int dy[] = {1, -1, 0, 0};

// Fast I/O
void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

// Debug macro (comment out for submission)
#define debug(x) cerr << #x << " = " << x << endl

/*
 * Useful functions
 */

// Check if coordinates are within bounds
bool inBounds(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

// GCD (built-in __gcd also works)
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// LCM
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

// Binary exponentiation
ll binpow(ll a, ll b, ll m = MOD) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void solve() {
    // Your solution here
    
}

int main() {
    fastIO();
    
    // For USACO file I/O (uncomment for USACO problems)
    // freopen("problem.in", "r", stdin);
    // freopen("problem.out", "w", stdout);
    
    int t = 1;
    // cin >> t; // Uncomment for multiple test cases
    while (t--) {
        solve();
    }
    
    return 0;
}
