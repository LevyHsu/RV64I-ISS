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

unsigned int random_n (unsigned int seed, unsigned int n) {
  unsigned int i;
  unsigned int num;
  num = seed;
  for (i = 0; i < n; i++)
    num = random(num);
  return num;
}


int main (void) {
  int seed = 0x12345678;
  int num = 100;
  
  return random_n(seed, num) != 0x0f1aca19;

}
