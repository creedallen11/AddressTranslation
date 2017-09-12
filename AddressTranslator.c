#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* This function takes a page mask, the ammount to right shift the result, and an address,
		and returns the physical page dictated by the virtual address */
int getPage(unsigned int pageMask, unsigned int rightShift, unsigned int address){
	return (address & pageMask) >> rightShift;
}

/* This function takes an offset mask, and an address	and returns the
 		offset dictated by the virtual address */
int getOffset(unsigned int offsetMask, unsigned int address){
	return offsetMask & address;
}

int main(int argc, char* argv[]){
	unsigned int n = 0; /* The n lowest significant bits that represent the offset */
	unsigned int m = 0; /* The next m bits that represent the page number */
	/* m+n  == 16 is presumed*/
	unsigned int v = 0; /* a virtual address */
	unsigned int pageMask;
	unsigned int offsetMask;

	if(argc < 1){
		printf("No input file specified...");
		return 1;
	}
	FILE *input;
	input = fopen(argv[1], "r");

	fscanf(input, "%u\n", &n); /*get the number of offset bits*/
	fscanf(input, "%u\n", &m); /*get the number of page bits*/

	if(m+n != 16){
		printf("m+n do not equal 16. There is a problem with the input file semantics.");
		return 1;
	}

	/* construct bit masks for offset and page fields of a virtual address */
	offsetMask = (unsigned) (pow(2,n)-1);
	pageMask = ((unsigned) pow(2,m)) << n - 1;

	/* while there exists more virtual addresses, compute their pages and offsets and print them */
	while(fscanf(input, "%u\n", &v) > 0){
		printf("virtual address %d is in page number %d and offset %d\n", v, getPage(pageMask, n, v), getOffset(offsetMask, v));
	}

	return fclose(input);
}
