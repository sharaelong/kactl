/**
 * Author:
 * Description: Calculate the area of union of circle.
 * Usage:
 * Time:
 */
#pragma once

inline ld sqr(ld x) {
  return x*x;
}
inline int sgn(ld x) {
  return abs(x)<1e-19L? 0: x > 0? 1 : -1;
}

struct vec2{
  ld x,y;
  vec2(){}
  vec2(ld _x, ld _y): x(_x), y(_y){}
  ld norm()const{return sqrtl(sqr(x)+sqr(y)); }
  ld angle()const{return atan2l(y,x);}

  friend vec2 operator+(vec2 a, vec2 b){return vec2(a.x+b.x, a.y+b.y); }
  friend vec2 operator-(vec2 a, vec2 b){return vec2(a.x-b.x, a.y-b.y); }
  friend vec2 operator*(vec2 a, ld b){return vec2(a.x*b, a.y*b); }
  friend vec2 operator / (vec2 a, ld b){return vec2(a.x / b, a.y / b); }
  friend bool operator == (vec2 a, vec2 b){return sgn(a.x-b.x) == 0 && sgn(a.y-b.y) == 0; }
  friend bool operator < (vec2 a, vec2 b){return sgn(a.x-b.x) < 0 || (sgn(a.x-b.x) == 0 && sgn(a.y-b.y) < 0); }


  vec2 rotate(vec2 p, ld ang) {
    vec2 v=(*this)-p;
    vec2 ret;
    ret.x=v.x*cosl(ang)-v.y*sinl(ang);
    ret.y=v.y*cosl(ang)+v.x*sinl(ang);
    return ret+p;
  }
};
int circle_inter_circle(vec2 c1, ld r1, vec2 c2, ld r2, vec2 *res)
{
  ld d=(c1-c2).norm();
  if (sgn(d) == 0) {
    if (sgn(r1-r2) == 0) return -1;
    return 0;
  }
  if (sgn(r1+r2-d) < 0) return 0;
  if (sgn(fabs(r1-r2)-d) > 0) return 0;

  ld ang=atan2((c2-c1).y, (c2-c1).x);
  ld vang=acosl( (sqr(r1)+sqr(d)-sqr(r2)) / (2*r1*d) );
  res[0]=vec2(c1.x+r1, c1.y).rotate(c1, ang+vang);
  res[1]=vec2(c1.x+r1, c1.y).rotate(c1, ang-vang);
  if (res[0] == res[1]) return 1;
  return 2;
}

struct region{
  ld st, ed;
  region(){}
  region(ld _st, ld _ed): st(_st), ed(_ed) {}
  bool operator < (const region &a)const {
    return sgn(st-a.st) < 0 || (sgn(st-a.st) == 0 && sgn(ed-a.ed) < 0);
  }
};

struct Circle{
  vec2 c;
  ld r;
  vector<region> reg;
  Circle(){}
  Circle(vec2 _c, ld _r): c(_c), r(_r) {}

  void add(const region r={}){reg.emplace_back(r); }
  ld area(ld ang=M_PI){return ang*sqr(r); }
  vec2 makepoint(ld ang){return vec2(c.x+r*cosl(ang) , c.y+r*sinl(ang)); }

  bool operator<(const Circle &a)const {
    return sgn(r-a.r) < 0 || (sgn(r-a.r) == 0 && c < a.c);
  }
  bool operator==(const Circle &a)const {
    return sgn(r-a.r) == 0 && c == a.c;
  }
};

ld area_of_circles(Circle *cir, int n){
  bool ok[n+5];
  memset(ok, true, sizeof ok);
  ld ans=0;
  for (int i=0; i < n; i++) {
    for (int j=0; j < n; j++) if (ok[j]) {
      if (i == j) continue;
      ld d=(cir[i].c-cir[j].c).norm();
      if (sgn(d+cir[i].r-cir[j].r) <= 0){//!!!!
        ok[i]=false;
        break;
      }
    }
  }
  for (int i=0; i < n; i++) if (ok[i]) {
    vec2 p[2];
    bool flag=false;
    for (int j=0; j < n; j++) if(ok[j]) {
      if (i == j) continue;
      int k=circle_inter_circle(cir[i].c, cir[i].r, cir[j].c, cir[j].r, p);
      if (k != 2) continue;
      flag=true;

      ld ang1=(p[1]-cir[i].c).angle(), ang2=(p[0]-cir[i].c).angle();
      if (sgn(ang1) < 0) ang1+=2*M_PI;
      if (sgn(ang2) < 0) ang2+=2*M_PI;
      if (sgn(ang1-ang2) > 0) cir[i].add(region(ang1, 2*M_PI)), cir[i].add(region(0, ang2));
      else cir[i].add(region(ang1, ang2));
    }
    if (!flag) {
      ans+=cir[i].area();
      continue;
    }
    sort(cir[i].reg.begin(), cir[i].reg.end());
    int cnt=1;
    for (int j=1; j < int(cir[i].reg.size()); j++) {
      if (sgn(cir[i].reg[cnt-1].ed-cir[i].reg[j].st) >= 0) {
        cir[i].reg[cnt-1].ed=max(cir[i].reg[cnt-1].ed, cir[i].reg[j].ed);
      }
      else {
        cir[i].reg[cnt++]=cir[i].reg[j];
      }
    }
    cir[i].add();
    cir[i].reg[cnt]=cir[i].reg[0];
    for (int j=0; j < cnt; j++) {
      p[0]=cir[i].makepoint(cir[i].reg[j].ed);
      p[1]=cir[i].makepoint(cir[i].reg[j+1].st);
      ans+=(p[0].x*p[1].y-p[1].x*p[0].y)/2.L;
      ld ang=cir[i].reg[j+1].st-cir[i].reg[j].ed;
      if (sgn(ang) < 0) ang+=2*M_PI;
      ans+=0.5*sqr(cir[i].r)*(ang-sinl(ang));
    }
  }
  return ans;
}

ld total_area(vector<ld> cx,vector<ld> cy,vector<ld> cr){
  size_t const n=cx.size();
  vector<Circle> c(n);
  for (int i=0; i<n; i++){
    c[i].c.x=cx[i];
    c[i].c.y=cy[i];
    c[i].r=cr[i];
  }
  return area_of_circles(&c[0],n);
}

int main(){
  ld angle=0.45692586256L;

  int n; ld area; cin>>n>>area;
  vector<ld> cx(n),cy(n),cr(n);
  for (int i=n; i--;){
    ld x,y,r; cin>>x>>y>>r;
    cx[i]=cosl(angle)*x+sinl(angle)*y;
    cy[i]=cosl(angle)*y-sinl(angle)*x;
    cr[i]=r;
  }

  ld min_rad=cr[0];
  for (auto const &i: cr) min_rad=min(min_rad,i);

  ld lef=min_rad;
  ld rgt=min_rad+sqrtl(area/M_PI);
  for (int iter=200; iter--;){
    ld const mid=(lef+rgt)/2.L;

    vector<ld> tcr=cr;
    for (int i=0; i<n; i++) tcr[i]=max(mid-cr[i],0.L);
    ld const total=total_area(cx,cy,tcr);
    if (total<area){
      lef=mid;
    }else{
      rgt=mid;
    }
  }

  cout.precision(12);
  cout<<fixed<<lef<<endl;
}

