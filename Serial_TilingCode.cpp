#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
using namespace std; 

int main(){
	ofstream fout;
	fout.open("tilingData.txt", ios::out);
	int N=1600, numRC, origin, space=1, iteration, size, e, i, j, k;
	int *A, *B, *Bb, *C;
	A=(int*)malloc(1600*1600*sizeof(int));
	Bb=(int*)malloc(1600*1600*sizeof(int));
	B=(int*)malloc(1600*1600*sizeof(int));
	C=(int*)malloc(1600*1600*sizeof(int));
	for (int i=0; i<(1600*1600+1); i++){
		A[i] = rand()%100;
		Bb[i]= rand()%100;
		B[i] = 0;
	} 
	int *choiceA, *choiceB;
	choiceA=(int*)malloc(400*400*sizeof(int));
	choiceB=(int*)malloc(400*400*sizeof(int));
	for (int i=0; i<(400*400+1); i++){
		choiceA[i] = 0;
		choiceB[i] = 0;
	}
	
	/*Reindex Matrix B into col by row rather than row by col (flip over y=-x)
	 So we'll have:
	 B[1]  B[4]  B[7] 
	 B[2]  B[5]  B[8]
	 B[3]  b[6]  B[9]
	 INSTEAD of:
	 B[1]  B[2]  B[3]
	 B[4]  B[5]  B[6]
	 B[7]  B[8]  B[9]
	 
	 Now we can multiply the row of tile matrix A times the row of tile Matrix B
	 */
	int count=1;
	for (int i=j=1; i<(N*N+1); i+=N){
		if (count%N==0) {
			i-=(N*N-N-1);
		}
		B[j]=Bb[i];
		count++;
		j++;
	}
	// OR REINDEX this way:
	/*
	 for (i=0; i<N; i++){
	 for (j=0; j<N; j++){
	 B[i*N+j]=Bb[j*N+i];
	 }
	 }
	 */
	//Delete old Matrix Bb
	free(Bb);
	Bb=NULL;
	
	double time, final;
	
	for (N=400; N<1601; N++){
		time= clock();
		numRC=N/400; //we won't really be tiling until we hit 800*800 - we have enough memory for it to run fast enough on naive code until then
		size=N/numRC;
		//Find choiceA and choiceB
		iteration=0; //iteration keeps track of where in the matrix you are [normal indexing]
		//  0   1   2   3
		//  4   5   6   7
		//  8   9   10  11
		//  12  13  14  15
		if ((iteration+1)%numRC==0 || iteration==0){ 
			/*if the number of iterations + 1 (iterations start at zero) OR you are just starting with a small 
			 matrix, then you are at the end of the column and need to multiply a new set of tiles from matrix
			 A and B to add for a new component of C */
			if (iteration<(numRC+1)){
				origin = iteration*size+1; //finds the origin (when not in the first set of iterations)
			}
			else { /*if you are in the first row of tiles matrices, then origin equals which tile your using (iteration
					1   -400     401 -800
					801-         1201-
					--319600      --320000
					
					320001-      320401- */
				origin=(iteration%numRC)*size+1;
			}
			// This initiallizes the tiles into choiceA and choiceB matrices to be multiplied together
			// choiceA and chioceB were allocated and initalized, so we don't need to use any more memory than that - 
			// we can just reinitiallize over that to conserve as much memory as possible
			for (space=e=origin; e<(size*N-size*2+1); e++){
				choiceA[space] = A[e]; //e is the index for where in the large matrices A and B you are in
				choiceB[space] = B[e];
				if (e%size==0) {  // if e is at the end of the row for the tile, then it will be divisible by the size
					e+=(numRC-1)*size+1;  //and after we used the "e" all the way at the of the row, then we add the size times number of rows and 
					//columns minus 1 (since we are already at the end of the tile and want to get to the beginning
					//of the next row)
				}
				space++; //space is the loaction in the newly initiallized tiled matrices from 1 to size*size
			}
			//Multiply choiceA and choiceB with the naive code
			for (i=0; i<size; i++){
				for (j=0; j<size; j++) {
					for (k=0; k<size; k++){
						C[i*size+j] += A[i*size+k] * B[k*size+j];
					}
				}
			}
			//if the iteration (which starts at 0 so we have to add 1) is divisible by the number of rows/columns, then we need to 
			if ((iteration + 1)%numRC == 0){  
				origin+=N*size - (numRC*size);
			}
		}	
		
		final=(clock()-time)/N/N/N;
		fout<<N<<"   "<<final<<endl;
	}
	return 0;
}
