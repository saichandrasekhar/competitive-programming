#include <bits/stdc++.h>

using namespace std;

#define DEBUG

const long long INF = 0x3f3f3f3f3f3f3f3fLL;
const int MOD = 1e9 + 7;

//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    os << '{';
    string sep;
    for (const auto &x : v) os << sep << x, sep = ", ";
    return os << '}';
}

template<typename T, size_t size>
ostream &operator<<(ostream &os, const array<T, size> &arr) {
    os << '{';
    string sep;
    for (const auto &x : arr) os << sep << x, sep = ", ";
    return os << '}';
}

template<typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }

void dbg_out() { cerr << endl; }

template<typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}

#ifdef DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<array<int, 2>> queries(n);
        vector<int> a;
        for (int i = 0; i < n; i++) {
            cin >> queries[i][0] >> queries[i][1];
            a.push_back(queries[i][0]);
            a.push_back(queries[i][1]);
        }
        auto b = a;
        b.erase(unique(b.begin(), b.end()), b.end());
        map<int, int> id;
        for (int i = 0; i < a.size(); i++) {
            int pos = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
            id[a[i]] = pos;
        }
        vector<int> T(8 * n), lazy(8 * n);
        auto push = [&](int v) {
            if (lazy[v]) lazy[v * 2] = lazy[v * 2 + 1] = lazy[v];
            lazy[v] = 0;
        };
        function<void(int, int, int, int, int, int)> update = [&](int v, int l, int r, int x, int y, int val) {
            if (l > y || r < x) return;
            if (l >= x && r <= y) {
                lazy[v] = val;
                return;
            }
            int m = (l + r) / 2;
            push(v);
            update(v * 2, l, m, x, y, val);
            update(v * 2 + 1, m + 1, r, x, y, val);
        };
        set<int> s;
        function<void(int, int, int)> count = [&](int v, int l, int r) {
            if (lazy[v]) {
                s.insert(lazy[v]);
                return;
            }
            if (l == r) return;
            int m = (l + r) / 2;
            count(v * 2, l, m);
            count(v * 2 + 1, m + 1, r);
        };
        for (int i = 0; i < n; i++) {
            int l = id[queries[i][0]], r = id[queries[i][1]];
            update(1, 0, b.size(), l, r, i + 1);
        }
        count(1, 0, b.size());
        int ans = s.size();
        cout << ans << '\n';
    }
}
