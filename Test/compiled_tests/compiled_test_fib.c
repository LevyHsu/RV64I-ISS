unsigned int fib (unsigned int n) {
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return (fib(n - 1) + fib(n - 2));
}

int main (void) {
  int n = 25;
  
  return fib(n) != 75025;

}
