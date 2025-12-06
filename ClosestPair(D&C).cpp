#include <bits/stdc++.h>
using namespace std;

using ld = long double;

struct Point{
    ld x, y;
};

ld dist(const Point &a, const Point& b){
    ld dx = a.x-b.x, dy = a.y-b.y;
    return sqrtl(dx*dx+dy*dy);
}

ld closestPair(vector<Point>& pts, int l, int r){
    if(r-l<=0)return 1e15;
    if(r-l==1)return dist(pts[l],pts[r]);
    int mid = (l+r)/2;
    ld d1 = closestPair(pts,l,mid);
    ld d2 = closestPair(pts, mid+1, r);
    ld d = min(d1,d2);
    vector<Point>strip;
    for(int i = l;i<=r;i++){
        if(abs(pts[i].x-pts[mid].x)<d)strip.push_back(pts[i]);
    }
    sort(strip.begin(), strip.end(), [](const Point &a, const Point &b){
        return a.y<b.y;
    });
    for(int i = 0;i<strip.size();i++){
        for(int j = i+1;j<strip.size() && (strip[j].y-strip[i].y<d);j++){
            d = min(d, dist(strip[i],strip[j]));
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<Point> pts(n);
    for (auto &p : pts) cin >> p.x >> p.y;
    sort(pts.begin(), pts.end(),
         [](const Point &a, const Point &b) { return a.x < b.x; });

    cout << fixed << setprecision(10) << closestPair(pts, 0, n) << '\n';
    return 0;
}