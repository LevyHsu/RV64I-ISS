int leaf_example (int g, int h, int i, int j) {
  int f;
  f = (g + h) - (i + j);
  return f;
}


int main (void) {
  int g = 23;
  int h = 248;
  int i = 25;
  int j = 15;
  
  return leaf_example(g,h,i,j) != 231;

}
