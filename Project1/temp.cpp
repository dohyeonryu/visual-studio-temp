#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#define INT_MAX 2147483647
#define INF 1000000000
#define ll long long

using namespace std;

int n, m;
char table[1001][1001];
int zone[1001][1001];
bool visit[1001][1001];
bool ans[1000001];
stack<pair<int, int>> s;

int find(int a) {
    if (zone[a / m][a % m] == a) {
        return a;
    }
    else {
        return zone[a / m][a % m] = find(zone[a / m][a % m]);
    }
}

void union_zone(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        zone[a / m][a % m] = b;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int num = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < m; j++) {
            table[i][j] = str[j];
            zone[i][j] = num++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visit[i][j]) {
                continue;
            }
            while (!s.empty()) {
                s.pop();
            }
            s.push({ i,j });
            while (!s.empty()) {
                int x = s.top().second;
                int y = s.top().first;
                if (visit[y][x]) {
                    break;
                }
                visit[y][x] = 1;
                if (table[y][x] == 'U') {
                    union_zone(zone[y - 1][x], zone[y][x]);
                    s.push({ y - 1,x });
                }
                else if (table[y][x] == 'D') {
                    union_zone(zone[y + 1][x], zone[y][x]);
                    s.push({ y + 1,x });
                }
                else if (table[y][x] == 'L') {
                    union_zone(zone[y][x - 1], zone[y][x]);
                    s.push({ y,x - 1 });
                }
                else {
                    union_zone(zone[y][x + 1], zone[y][x]);
                    s.push({ y,x + 1 });
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << zone[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans[zone[i][j]] = 1;
        }
    }
    int safezone = 0;
    for (int i = 0; i < num; i++) {
        if (ans[i]) {
            safezone++;
        }
    }
    cout << safezone << "\n";

    return 0;
}
