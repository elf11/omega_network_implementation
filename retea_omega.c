#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main() {

	int n, np;
	int et = 0, temp;

	FILE * f = fopen ("intrari", "r");

	fscanf(f,"%d", &n);							//dim retea
	fscanf(f,"%d", &np);						// nr perechi

	if (np<1 || n<2)
		return 0;
	
	int *pair = (int*)malloc(2 * np * sizeof(int));	// toate valorile (valori 2 cate 2)
	int *val = (int*)malloc(np * sizeof(int));	// toate xor-urile valorilor 2 cate 2
	int *binaryVal = (int *)malloc(np * 3 * sizeof(int));
	int i;
	for (i=0; i<2*np; i+=2)	
		fscanf(f,"%d %d", &pair[i], &pair[i+1]);
	
	int t1 = 0, t2 = 0, t3 = 0;
	for (i = 0; i < np; i += 1) {
        t1 = 0;
        t2 = 0;
        t3 = 0;
		temp = pair[2 * i + 1];
		//printf("valoare %d \n", temp);	
		t1 = temp % 2;
		temp = temp / 2;
		//printf("valoarea lui temp %d\n", temp);
        t2 = temp % 2;
		temp = temp / 2;
        //printf("valoarea lui temp %d\n", temp);
		t3 = temp % 2;
		binaryVal[3 * i] = t3;
		binaryVal[3 * i + 1] = t2;
		binaryVal[3 * i + 2] = t1;
		//printf("valoarea in binar %d %d %d \n", t3, t2, t1);
	}

    //for (i = 0; i < 3 *np; i += 3)
    //    printf("\n%d %d %d", binaryVal[i], binaryVal[i+1], binaryVal[i+2]);

	int N = (int)log2(n);						// nr de etaje
	int mask = n-1, *aux = (int*)malloc(np*sizeof(int));

	for(i=0; i<2*np; i=i+2)
		val[i/2] = pair[i]^pair[i+1];			// init xor-uri

	for (i=0; i<2*np; i+=2) { 					//pt fiecare pereche

		aux[i/2] = pair[i];
		aux[i/2] = (aux[i/2] << 1) & mask | (aux[i/2] >> (N-1));
	}
	
	/*printf("vals :\n");
	for(i=0; i< np; i++)
		printf("%d ", val[i]);
	printf("\n");
	
	printf("aux vals :\n");
	for (i = 0; i < np; i += 1) {
		printf("%d ", aux[i]);
	}
	printf("\n");
	*/
	int j;
	printf ("Perechi testate: \n");
	for (j=0; j<2*np-2; j+=2)
		printf("(%d,%d), ", pair[j], pair[j+1]);
	printf("(%d,%d)\n", pair[2*np-2], pair[2*np-1]);


	for (j=0; j<log2(n); j++) {				// pt fiecare etaj

		printf ("Etajul %d: blocuri \n", (int)log2(n)-j-1);
		et = (int)log2(n)-j-1;
		
		for (i=0; i<2*np; i+=2) {
			int k = i / 2;

			//printf ("%d ", aux[i/2] / 2);
			if (val[i/2] >> (2-j) & 1)
				if (aux[i/2] % 2 == 0) 
					aux[i/2]++;
				else
					aux[i/2]--;
			//printf("\nvaloarea %d si et %d \n", binaryVal[3 * i + et], et);
			if (binaryVal[3 * k + et] == 1) {
				printf("C0 = 1; C1 = 1; down\n");
			} else {
				printf("C0 = 0; C1 = 0; up\n");
			}
 			aux[i/2] = (aux[i/2] << 1) & mask | (aux[i/2] >> (N-1));
		}
		printf("\n");
		
	}

	return 0;
}
