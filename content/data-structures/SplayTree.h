/**
 * Author:
 * Description:
 */
#pragma once

typedef ll TCON; // content
const TCON initval = 0;
typedef ll TV; // subtree value
const TV id = 0;
typedef ll TLAZ; // lazy value
const TLAZ S_unused = 0;

struct Snode{
  Snode *l, *r, *p;
  int cnt;
    
  TCON content = initval;
  TV val;
  TLAZ lazy = S_unused;

  void init(){
    // Initialize value using CONTENT
    val = content;
  }
  TV combine(TV a, TV b){
    // Real value when a <-- b
    return a+b;
  }
  TLAZ combineL(TLAZ a, TLAZ b){
    // Lazy value when a <-- b
    return a+b;
  }
  void unlazy_inner(){
    // Update CONTENT and VAL using LAZY
    content+= lazy;
    val+= lazy * cnt;
  }

  void update(){
    cnt = 1;
    init();
    if(l) l->unlazy(), cnt+= l->cnt,
            val = combine(l->val, val);
    if(r) r->unlazy(), cnt+= r->cnt,
            val = combine(val, r->val);
  }
    
  void lazy_add(TLAZ x){lazy = combineL(lazy, x);}
  void unlazy(){
    if(lazy == S_unused) return;
    unlazy_inner();
    if(l) l->lazy_add(lazy);
    if(r) r->lazy_add(lazy);
    lazy = S_unused;
  }

  void debug_inorder(){
    unlazy();
    if(l) l->debug_inorder();
    //cout << content << ' ';
    if(r) r->debug_inorder();
  }
};

// 1-indexed; has sentinel nodes on both ends
struct Splay{
  Snode *root;

  Splay(int n){
    Snode *x;
    root = x = new Snode;
    x->l = x->r = x->p = NULL;
    x->cnt = n, x->lazy = S_unused;
    x->init();
    for(int i=1; i<n+2; i++){
      x->r = new Snode;
      x->r->p = x; x = x->r;
      x->l = x->r = NULL;
      x->cnt = n-i, x->lazy = S_unused;
      x->init();
    }
  }
    
  void rotate(Snode *x){
    // x goes to parent of x
    Snode *p = x->p, *b = NULL;
    if(x == p->l) p->l = b = x->r, x->r = p;
    else p->r = b = x->l, x->l = p;
    x->p = p->p, p->p = x;
    if(b) b->p = p;
    (x->p ? p == x->p->l ? x->p->l : x->p->r : root) = x;
    p->update(), x->update();
  }
    
  Snode* splay(Snode *x){
    // x becomes the root
    while(x->p){
      Snode *p = x->p, *g = p->p;
      if(g) rotate((x == p->l) == (p == g->l) ? p : x);
      rotate(x);
    }
    return root = x;
  }
    
  Snode* kth(int k){
    // kth becomes the root
    // DO NOT USE IT FOR POINT UPDATE!! USE INTERVAL(k,k)!!!!
    Snode *x = root; x->unlazy();
    while(1){
      while(x->l && x->l->cnt > k) (x = x->l)->unlazy();
      if(x->l) k-= x->l->cnt;
      if(!k--) break;
      (x = x->r)->unlazy();
    }
    return splay(x);
  }

  Snode* interval(int l, int r){
    // l to r goes to root->r->l
    kth(l-1);
    Snode *x = root;
    root = x->r; root->p = NULL;
    kth(r-l+1);
    x->r= root; root->p = x; root = x;
    (x = root->r->l)->unlazy();
    return x;
  }

  void insert(int k, TCON v){
    // insert CONTENT v at index k, which becomes root
    kth(k);
    Snode *x = new Snode;
    if(root->l) root->l->p = x;
    x->l = root->l; root->l = x; x->p = root; x->r = NULL;
    x->content = v; x->init();
    splay(x);
  }

  void remove(int k){
    // remove k-th node
    kth(k);
    Snode *p = root;
    p->unlazy();
    if(p->l){
      if(p->r){
        root = p->l; root->p = NULL;
        Snode *cur = root;
        cur->unlazy();
        while (cur->r) cur = cur->r, cur->unlazy();
        cur->r = p->r; p->r->p = cur;
        splay(cur); delete p;
      }
      else{root = p->l; root->p = NULL; delete p;}
    }
    else{root = p->r; if(root) root->p = NULL; delete p;}
  }
};
