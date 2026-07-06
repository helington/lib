using namespace std;
using ll = long long;
#define int ll
using pii = pair<int,int>;
using vi = vector<int>;


const double EPS = 1e-9;

int cmp(double a, double b){
    if (fabs(a - b) < EPS) return 0;
    return (a < b ? -1 : 1);
}
struct Point{
    double x,y;
    Point(double x = 0, double y = 0) : x(x),y(y){}//adicionar aqui se houver algum atributo a mais
    Point(const Point& p): x(p.x), y(p.y){}//aq tbm
    bool operator < (const Point &p) const {
        if(cmp(x, p.x) != 0) return x < p.x;
        return cmp(y, p.y) < 0;
    }
    bool operator == (const Point &p) const {return !cmp(x, p.x) && !cmp(y, p.y);}
    bool operator != (const Point &p) const {return !(p == *this);}

    // basic ops
    Point operator + (const Point& p) const {return Point(x+p.x,y+p.y);}
    Point operator - (const Point& p) const {return Point(x-p.x,y-p.y);}
    Point operator * (const double k) const {return Point(x*k,y*k);}
    Point operator / (const double k) const {return Point(x/k,y/k);}
};


double dot (const Point& p,const Point& q) { return p.x*q.x + p.y*q.y; }
double cross (const Point& p,const Point& q) { return p.x*q.y - p.y*q.x; }
double norm (const Point& p) { return hypot(p.x,p.y); }
double dist(const Point& p, const Point& q) { return hypot(p.x-q.x,p.y-q.y); }
double dist2(const Point& p, const Point& q) { return dot(p-q,p-q); }
Point normalize(const Point &p) { return p/hypot(p.x, p.y); }
double angle (const Point& p, Point& q) { return atan2(cross(p, q), dot(p, q)); }
double angle (const Point& p) { return atan2(p.y, p.x); }


bool OnSegment(const Point &p1, const Point &p2, const Point &p3){
    if(cmp(cross(p2-p1,p3-p1),0)!=0) return false;
    return true;
}
bool isInside(const vector<Point> &hull, Point pt) {
    int n = hull.size();
    Point v0 = pt - hull[0], v1 = hull[1] - hull[0], v2 = hull[n-1] - hull[0];
    if(cross(v0,v1) > 0 || cross(v0,v2) < 0) {
        return false;
    }

    int l = 1, r = n - 1;
    while(l != r) {
        int mid = (l + r + 1) / 2;
        Point v0 = pt - hull[0], v1 = hull[mid] - hull[0];
        if(cross(v0,v1) < 0) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    v0 = hull[(l+1)%n] - hull[l], v1 = pt - hull[l];
    return cross(v0,v1) >= 0;
}

//CUIDADO COM O CASO COLINEARES!!!
vector<Point> convexhull(vector<Point>& pts, bool sorted = false){ // pts.size() >= 3
    int n = pts.size();
    if(!sorted){
        sort(begin(pts), end(pts));
    }

    vector<Point> lower(n + 1), upper(n + 1);
    int s = 0;

    for(int i = 0; i < n; i++){
        lower[s++] = pts[i];
        while(s >= 3){
            Point a = lower[s-3], b = lower[s-2], c = lower[s-1];
            Point v1 = b - a, v2 = c - b;
            if(cross(v1, v2) >= 0){//>= se quero borda
                break;
            }
            lower[s-2] = lower[s-1];
            s--;
        }
    }
    lower.resize(s);

    s = 0;
    for(int i = 0; i < n; i++){
        upper[s++] = pts[i];
        while(s >= 3){
            Point a = upper[s-3], b = upper[s-2], c = upper[s-1];
            Point v1 = b - a, v2 = c - b;
            if(cross(v1, v2) <= 0){//<= se quero borda
                break;
            }
            upper[s-2] = upper[s-1];
            s--;
        }
    }

    upper.resize(s-1);
    reverse(begin(upper), end(upper));
    upper.pop_back();

    lower.insert(end(lower), begin(upper), end(upper));
    return lower;
}