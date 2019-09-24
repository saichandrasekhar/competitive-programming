#include <bits/stdc++.h>
using namespace std;

#define N 110000
#define M 3500000
int n, i, m, l, r, now, x, len, root[N], son[M][2], sum[M], k;

void modify(int &k, int k1, int q, int h, int x) {
	k = ++len;
	sum[k] = sum[k1] + 1;
	if (q == h)	return ;
	else	if (x <= (q + h) / 2)	modify(son[k][0], son[k1][0], q, (q + h) / 2, x), son[k][1] = son[k1][1];
	else	modify(son[k][1], son[k1][1], (q + h) / 2 + 1, h, x), son[k][0] = son[k1][0];
}

int query(int k1, int k2, int q, int h, int x) {
	if (q == h)	return q;
	int cur = sum[son[k2][0]] - sum[son[k1][0]];
	if (cur >= x)	return query(son[k1][0], son[k2][0], q, (q + h) / 2, x);
	return query(son[k1][1], son[k2][1], (q + h) / 2 + 1, h, x - cur);
}

int b[N], a[N];

int main() {
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; i++) {
	    scanf("%d", &a[i]);
	    b[i] = a[i];
	}
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++) {
    	    a[i] = lower_bound(b+1,b+n+1,a[i]) - b;
	}
	for(int i=1; i <= n; i++) {
		x = a[i];
		modify(root[i], root[i - 1], 1, 1000000001, x);
	}
	while (m--) {
		scanf("%d%d%d", &l, &r, &k);
    		int pos = query(root[l - 1], root[r], 1, 1000000001, k);
		printf("%d\n", b[pos]);
	}
}
