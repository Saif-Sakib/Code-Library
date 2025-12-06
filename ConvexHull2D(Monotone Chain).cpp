#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Point{
    ll x, y;
};

ll orientation(const Point& a, const Point& b, const Point& c){
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}

vector<Point> convexHull(vector<Point> pts){
    int n = pts.size();
    if(n<=1)return pts;
    sort(pts.begin(),pts.end(),[](const Point& a, const Point& b){
        return a.x<b.x || (a.x==b.x && a.y<b.y);
    });
    vector<Point>up, lo;

    for(const Point& p:pts){
        while(lo.size()>=2 && orientation(lo[lo.size()-2],lo.back(),p)<=0)lo.pop_back();
        lo.push_back(p);
    }

    for(int i = n-1;i>=0;i--){
        while(up.size()>=2 && orientation(up[up.size()-2],up.back(),pts[i])<=0)up.pop_back();
        up.push_back(pts[i]);
    }

    lo.pop_back(); up.pop_back();
    lo.insert(lo.end(),up.begin(),up.end());
    return lo;
}