#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> list;
typedef pair<int, int> par;

int n, w;
char *wls_end;

struct point {
    int x, y, component, region[4];
    par links[4];

    point()
    {
        int i;

        component = -1;

        for (i = 0; i < 4; ++i) links [i] = par(-1, -1);
        for (i = 0; i < 4; ++i) region[i] = -1;
    }
};

vector<point> points;

struct region {
    int time_of_flooding;
    long long area;
    list series;

    region()
    {
        area = 0;
        time_of_flooding = -1;
    }
};

__attribute__((always_inline)) inline int direction(int a, int b)
{
    return points[a].y == points[b].y ? points[a].x < points[b].x ? 0 : 2
                                      : points[a].y > points[b].y ? 1 : 3;
}

void bfs(int x, int component)
{
    int i, y;
    queue<int> q;

    points[x].component = component;

    for (q.push(x); !q.empty(); q.pop()) {
        x = q.front();

        for (i = 0; i < 4; ++i) {
            y = points[x].links[i].first;
            if (y != -1 && points[y].component == -1) {
                points[y].component = component;
                q.push(y);
            }
        }
    }
}

void visit(int i, int j, region &r, int id)
{
    int k;

    r.series.push_back(i);

    while (points[i].region[j] == -1) {
        points[i].region[j] = id;

        k = points[i].links[j].first;

        r.area += (points[i].x - points[k].x) * (long long)points[i].y;
        r.series.push_back(k);

        i = k;

        for (j = (j + 3) % 4; points[i].links[j].first == -1; j = (j + 1) % 4);
    }

    r.area = abs(r.area);
}

void deflate(char *pts, char *wls)
{
    int i, c, j, a, b;

    for (i = 1, c = 0; c < n; ++c, i += 3) {
        point pt;

        for (pt.x = 0; pts[i] != ','; ++i) pt.x = pt.x * 10 + pts[i] - '0';

        ++i;
        for (pt.y = 0; pts[i] != ')'; ++i) pt.y = pt.y * 10 + pts[i] - '0';

        points.push_back(pt);
    }

    for (i = 1, j = 0; w--; ++j, i += 3) {
        for (a = 0; wls[i] != ','; ++i) a = a * 10 + wls[i] - '0';
        --a;

        ++i;
        for (b = 0; wls[i] != ')'; ++i) b = b * 10 + wls[i] - '0';
        --b;

        points[a].links[direction(a, b)] = par(b, j);
        points[b].links[direction(b, a)] = par(a, j);
    }
}

void my_itoa(int i)
{
    char *t, tc, *a;

    a = t = wls_end;
    do *t++ = '0' + i % 10;
    while (i /= 10);
    *t = '\0';
    wls_end = t;

    for (--t; a < t; ++a, --t)
        tc = *a,
        *a = *t,
        *t = tc;
}

char *GetStrongWall(int n_, char *pts, int w_, char *wls)
{
    int i, j, r, a, b, s, number_of_components;
    list sol;
    queue<int> q;

    n = n_;
    w = w_;

    points.reserve(n);
    deflate(pts, wls);

    number_of_components = 0;

    for (i = 0; i < n; ++i)
        if (points[i].component == -1)
            bfs(i, number_of_components++);

    list out_region(number_of_components, -1);
    vector<region> regions;

    for (i = 0; i < n; ++i)
        for (j = 0; j < 4; ++j)
            if (points[i].links[j].first != -1 && points[i].region[j] == -1) {
                r = regions.size();

                regions.push_back(region());
                visit(i, j, regions[r], r);

                int &out = out_region[points[i].component];

                if (out == -1 || regions[r].area > regions[out].area) out = r;
            }

    for (i = 0; i < number_of_components; ++i) {
        if (out_region[i] == -1) continue;

        regions[out_region[i]].time_of_flooding = 0;
        q.push(out_region[i]);
    }

    while (!q.empty()) {
        r = q.front();

        for (unsigned i = 1; i < regions[r].series.size(); ++i) {
            a = regions[r].series[i];
            b = regions[r].series[i - 1];
            s = points[a].region[direction(a, b)];

            if (regions[s].time_of_flooding == -1) {
                regions[s].time_of_flooding = regions[r].time_of_flooding + 1;
                q.push(s);
            }
        }

        q.pop();
    }

    for (a = 0; a < n; ++a)
        for (i = 0; i < 4; ++i) {
            b = points[a].links[i].first;

            if (b == -1 || b < a) continue;

            if (regions[points[a].region[direction(a, b)]].time_of_flooding ==
                regions[points[b].region[direction(b, a)]].time_of_flooding
            ) sol.push_back(points[a].links[i].second);
        }

    sort(sol.begin(), sol.end());

    *wls = '\0';
    wls_end = wls;
    for (list::iterator i = sol.begin(); i != sol.end(); ++i) {
        my_itoa(*i + 1);

        *wls_end++ =  ',';
        *wls_end   = '\0';
    }

    if (*wls)
        *--wls_end = '\0';
    else {
        *wls_end++ =  '0';
        *wls_end   = '\0';
    }

    return wls;
}

int main()
{
    int n, w;
    char *points, *walls;

    cin >> n;
    points = new char[(3 + 6*2 + 1) * n];
    cin >> points;

    cin >> w;
    walls = new char[(3 + 6*2 + 1) * w];
    cin >> walls;

    cout << GetStrongWall(n, points, w, walls) << endl;

    return 0;
}
