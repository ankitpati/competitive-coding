#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> list;
typedef pair<int, int> par;

int n;

struct point {
    int x, y, component, region[4];
    par links[4];

    point()
    {
        component = -1;

        for (int i = 0; i < 4; ++i)
            links[i] = par(-1, -1);

        for (int i = 0; i < 4; ++i)
            region[i] = -1;
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

inline int direction(int a, int b)
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
    int i, j, is_x, a, b, x;

    is_x = 1;
    for (i = 0; pts[i]; ++i)
        if (isdigit(pts[i])) {
            if (is_x)
                x = atoi(pts + i);
            else {
                point pt;
                pt.x = x;
                pt.y = atoi(pts + i);
                points.push_back(pt);
            }

            is_x = !is_x;

            while (isdigit(pts[i])) ++i;
        }

    is_x = 1;
    for (i = j = 0; wls[i]; ++i)
        if (isdigit(wls[i])) {
            if (is_x)
                a = atoi(wls + i) - 1;
            else {
                b = atoi(wls + i) - 1;

                points[a].links[direction(a, b)] = par(b, j);
                points[b].links[direction(b, a)] = par(a, j);

                ++j;
            }

            is_x = !is_x;

            while (isdigit(wls[i])) ++i;
        }
}

string result;
char *GetStrongWall(int n_, char *pts, int, char *wls)
{
    int i, j, r, a, b, s, number_of_components;

    n = n_;
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

    queue<int> q;

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

    list sol;

    for (a = 0; a < n; ++a)
        for (i = 0; i < 4; ++i) {
            b = points[a].links[i].first;

            if (b == -1 || b < a) continue;

            if (regions[points[a].region[direction(a, b)]].time_of_flooding ==
                regions[points[b].region[direction(b, a)]].time_of_flooding
            ) sol.push_back(points[a].links[i].second);
        }

    sort(sol.begin(), sol.end());

    char i2s[13];
    for (list::iterator i = sol.begin(); i != sol.end(); ++i) {
        sprintf(i2s, "%d", *i + 1);
        result += i2s;
        result += ',';
    }

    if (result.size())
        result.resize(result.size() - 1);
    else
        result += '0';

    return (char *)result.c_str();
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
