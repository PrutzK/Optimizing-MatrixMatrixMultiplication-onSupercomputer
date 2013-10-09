/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  Test of Matrix Multiplication timing
 *
 *        Version:  1.0
 *        Created:  08/30/2012 11:06:17 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Eric Dilmore (), ericdilmore@student.lsmsa.edu
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

float dtime ( struct timespec *start, struct timespec *end );

/*********************MAIN**********************/
int main ( int argc, char *argv[] )
{
	const int N = 1000;
	int n;
	int i, j, k;

	struct timespec startTime, endTime;

	// initialize random number
	printf ( "Initializing rand()\n" );
	unsigned int sseed;
	sseed = time ( NULL );
	srand ( sseed );

	// initialize matrices
	printf ( "Initializing matrices\n" );
	int *A, *B, *C;
	A = ( int * ) malloc ( sizeof ( int ) * N * N );
	B = ( int * ) malloc ( sizeof ( int ) * N * N );
	C = ( int * ) malloc ( sizeof ( int ) * N * N );
	printf ( "Filling matrices\n" );
	for ( i = 0; i < 1000 * 1000; ++i )
	{
		A[ i ] = rand() % 100;
		B[ i ] = rand() % 100;
	}

	// open file
	FILE	*outfile;										/* output-file pointer */
	char	*outfile_file_name = "time.dat";		/* output-file name    */

	printf ( "Opening output file\n" );
	outfile	= fopen( outfile_file_name, "w" );
	if ( outfile == NULL )
	{
		fprintf ( stderr, "couldn't open file '%s'",
				outfile_file_name );
		exit (EXIT_FAILURE);
	}

	printf ( "Beginning multiplication...\n" );
	// loop through different sizes of n
	for ( n = 1; n < N; ++n )
	{
		// start clock
		clock_gettime ( CLOCK_MONOTONIC, &startTime ); 

		// loop through rows
		for ( i = 0; i < n; ++i )
		{
			// loop through columns
			for ( j = 0; j < n; ++j )
			{
				// loop through elements
				for ( k = 0; k < n; ++k )
				{
					C[ N * i + j ] += A[ N * i + k ] * B[ N * k + j ];
				}
			}
		}
		clock_gettime ( CLOCK_MONOTONIC, &endTime );
		fprintf ( outfile, "%d %f\n", n, dtime ( &startTime, &endTime ) );
		printf ( "%d %f\n", n, dtime ( &startTime, &endTime ) );
	}
	
	// close file
	printf ( "Closing output file\n" );
	if( fclose(outfile) == EOF )
	{
		fprintf ( stderr, "couldn't close file '%s'",
				outfile_file_name );
		exit (EXIT_FAILURE);
	}


	// free memory allocation
	printf ( "Freeing memory\n" );
	free ( A );
	A = NULL;
	return 0;
}

float dtime ( struct timespec *start, struct timespec *end )
{
	float accum;
    accum = ( end->tv_sec - start->tv_sec )
          + ( float ) ( end->tv_nsec - start->tv_nsec )
            / 1E9;
	return accum;
}
