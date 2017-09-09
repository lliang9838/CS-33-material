/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include <pthread.h>
#include <semaphore.h>

//#define NUM_THREADS 8

int NUM_THREADS = 8;

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "204625818",            /* UID */

    "Leslie Liang",          /* Full name */
    "lliang9838@gmail.com",  /* Email */

    "",                   /* Leave Blank */
    ""                    /* Leave Blank */
};

//  You should modify only this file -- feel free to modify however you like!

/*
 * setup - This function runs one time, and will not be timed.
 *         You can do whatever initialization you need here, but
 *         it is not required -- don't use if you don't want to.
 */
void setup() {
  
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

typedef struct 
{
	pixel *src;
	pixel *dst;
	int my_id;
	int dim;

} thread_data;



/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;

    
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
    {
	   for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
        { 

	      accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
        }
    }


    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}










/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (j = 0; j < dim; j++) {
       for (i = 0; i < dim; i++) {	
           dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
       }
    }
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */

// Everything below is for Leslie Liang //





static inline int my_min(int a, int b) { return (a < b ? a : b); }
static inline int my_max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static inline void my_initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static inline void my_accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static inline void my_assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;

    
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static inline pixel my_avg(int dim, int i, int j, pixel *src)
{
	

	int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    pixel_sum temp;
 
    initialize_pixel_sum(&sum);

    int a =  i-1;
    int b = j-1;
    int c =i+1;
    int d =j+1;
    int bound = dim -1;

    int red;
    int green;
    int blue;
    int num;

  

    
    int firstMin = my_min(c, bound);
    int secondMin = my_min(d, bound);


    if ( i == 0 || j == 0 || i == bound || j == bound) //only run the code below
    {
    
    for(ii = my_max(a, 0); ii <= firstMin; ii++) //for edge cases
    {
	   for(jj = my_max(b, 0); jj <= secondMin; jj++) 
        { 
     		 //temp.red += src[RIDX(ii,jj,dim)].red;
    		// temp.green += src[RIDX(ii,jj,dim)].green;
    		// temp.blue += src[RIDX(ii,jj,dim)].blue;
    		// temp.num++;

        	red += src[RIDX(ii,jj,dim)].red;
    		green += src[RIDX(ii,jj,dim)].green;
    		blue += src[RIDX(ii,jj,dim)].blue;
    		num++;


	 // my_accumulate_sum(&temp, src[RIDX(ii, jj, dim)]); //store sum somewhere else
        }
    }
    
    }
    else
    {
    	for(ii = a ; ii <= c ; ii++) 
    {
	   for(jj = b ; jj <= d ; jj++) 
        { 
            // temp.red += src[RIDX(ii,jj,dim)].red;
    		// temp.green += src[RIDX(ii,jj,dim)].green;
    		// temp.blue += src[RIDX(ii,jj,dim)].blue;
    		// temp.num++;

    		red += src[RIDX(ii,jj,dim)].red;
    		green += src[RIDX(ii,jj,dim)].green;
    		blue += src[RIDX(ii,jj,dim)].blue;
    		num++;


	
		 // my_accumulate_sum(&temp, src[RIDX(ii, jj, dim)]);
        }
    }

    }

    sum.red = red;
    sum.green = green;
    sum.blue = blue;
    sum.num = num++;

    my_assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}


void * splice( void * arg)
{
    thread_data *data = (thread_data *) arg; //i've casted arg, and now data has the info
    //my_id in the struct contains the id that tells me how much to work on

    //wil attempt to partition based on data.my_id

    int dimension = data->dim;

    int s = data->my_id;
    int from = (s * dimension)/NUM_THREADS; //from this amt
    int to = ( (s+1)* dimension)/NUM_THREADS; //to this amt

    int i, j;

   pixel * source = data->src; //declaring these guys out here
   pixel * destination = data->dst;


    for (i = from; i < to; i++) {
       for (j = 0; j < dimension; j++) {
           destination[RIDX(i, j, dimension)] = my_avg(dimension, i, j, source);
       }
    }

}




char smooth_descr[] = "smooth: Current working version";
void inline smooth(int dim, pixel *src, pixel *dst) 
{	
	int i; //this is for creating my threads
	int res; //result of the p_thread create functions

	//int n = NUM_THREADS;


	// if ( dim < 130)
	// {
		
	// }

	if ( dim != 64) //bc the overhead of creating a thread for 64x64 is big
	{


	if ( dim < 250)
	{
		NUM_THREADS = 4; //do this so that for small arrays, fewer threads
	}
	else
	{
		NUM_THREADS =8;
	}
	
	thread_data t_data[NUM_THREADS]; //declaring an array of t_data struct's

    pthread_t tids[NUM_THREADS]; //statically create array 

	/* creating the threads */
	for ( i = 0; i < NUM_THREADS; ++i )
	{
		t_data[i].my_id = i; //my id is the number I'm in the loop
		t_data[i].src = src;
		t_data[i].dst = dst;
		t_data[i].dim = dim;
		pthread_create(&tids[i], NULL, splice, &t_data[i]); //creating threads
	}

	/* FOR JOINING THREADS */
	for ( i = 0; i < NUM_THREADS; ++i)
	{
		pthread_join(tids[i], NULL); //waiting for all my threads to join

	}

 }	
 else
 {
 	NUM_THREADS =1; //doing it the old fashion way but with one thread

 	thread_data one_data; //calling only one arg

 	one_data.src = src;
 	one_data.dst = dst;
 	one_data.my_id = 0;
 	one_data.dim = dim;
 	splice(&one_data);


 	// int i, j;

  //   for (j = 0; j < dim; j++) {
  //      for (i = 0; i < dim; i++) {	
  //          dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
  //      }
  //   }
 }
	// int i, j;

    // for (i = 0; i < dim; i++) {
    //    for (j = 0; j < dim; j++) {
    //        dst[RIDX(i, j, dim)] = my_avg(dim, i, j, src);
    //    }
    // }

    return 0;
}






/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
   
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    add_smooth_function(&smooth, smooth_descr);
    
    /* ... Register additional test functions here */
}






















// IGNORE EVERYTHING AFTER THIS POINT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
// You are not implementing rotate


/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    naive_rotate(dim, src, dst);
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}



