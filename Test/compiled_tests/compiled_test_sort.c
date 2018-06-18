/* Random number generator based on
   Pseudo-Random Sequence Generator for 32-Bit CPUs
   A fast, machine-independent generator for 32-bit Microprocessors
   B. Schneier
   Dr. Dobb's Journal, v. 17, n. 2, February 1992, pp. 34-40.
   https://www.schneier.com/paper-pseudorandom-sequence.html
 */

unsigned int random (unsigned int seed) {
  seed = ((((seed >> 31)   /*Shift the 32nd bit to the first bit*/
	    ^ (seed >> 6)  /*XOR it with the seventh bit*/
	    ^ (seed >> 4)  /*XOR it with the fifth bit*/
	    ^ (seed >> 2)  /*XOR it with the third bit*/
	    ^ (seed >> 1)  /*XOR it with the second bit*/
	    ^ seed)        /*and XOR it with the first bit.*/
	   & 0x0000001)    /*Strip all the other bits off and*/
	  <<31)            /*move it back to the 32nd bit.*/
    | (seed >> 1);         /*Or with the seed shifted right.*/
  return seed;
}

void init_vector (unsigned int v[], unsigned int n) {
  unsigned int i;
  unsigned int num;
  num = 0x12345678;
  for (i = 0; i < n; i++) {
    num = random(num);
    v[i] = num;
  }
}

void swap (unsigned int v[], unsigned int k) {
  unsigned int temp;
  temp = v[k];
  v[k] = v[k+1];
  v[k+1] = temp;
}

void sort (unsigned int v[], unsigned int n) {
  unsigned int i;
  unsigned int j;
  for (i = 0 ; i < ( n - 1 ); i++) {
    for (j = 0 ; j < n - i - 1; j++) {
      if (v[j] > v[j+1]) {
	swap (v, j);
      }
    }
  }
}

unsigned int verify_sorted (unsigned int v[], unsigned int n) {
  unsigned int i;
  for (i = 0; i < n - 1; i++) {
    if (v[i] > v[i+1])
      return 0;
  }
  return 1;
}

#define VECTOR_SIZE 1000

unsigned int main() {
  unsigned int v[VECTOR_SIZE];
  init_vector(v, VECTOR_SIZE);
  sort(v, VECTOR_SIZE);
  return !verify_sorted(v, VECTOR_SIZE);
}
