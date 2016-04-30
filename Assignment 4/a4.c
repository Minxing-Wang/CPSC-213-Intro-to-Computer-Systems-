struct S {
            int       x[2];
            int*      y;
            struct S* z;
};

int      i;
int      v;
struct S s;
      

void foo () {
    v = s.x[i];
    v = s.y[i];
    v = s.z->x[i];
}
