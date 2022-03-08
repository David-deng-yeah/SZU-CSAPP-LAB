/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "Exely", /* Team name */

    "Exely",            /* First member full name */
    "Exely@github.com", /* First member email address */

    "", /* Second member full name (leave blank if none) */
    ""  /* Second member email addr (leave blank if none) */
};

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
            dst[RIDX(dim - 1 - j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
 #define COPY(d,s) *(d)=*(s)
char rotate_descr[] = "rotate: Current working version";
void rotate( int dim,pixel *src,pixel *dst)
{
    int i,j;
    for(i=0;i<dim;i+=32)
    {
        for(j=dim-1;j>=0;j-=1)
        {       
            pixel*dptr=dst+RIDX(dim-1-j,i,dim);
            pixel*sptr=src+RIDX(i,j,dim);
            COPY(dptr,sptr); sptr+=dim;
            COPY(dptr+1,sptr); sptr+=dim;
            COPY(dptr+2,sptr); sptr+=dim;
            COPY(dptr+3,sptr); sptr+=dim;
            COPY(dptr+4,sptr); sptr+=dim;
            COPY(dptr+5,sptr); sptr+=dim;
            COPY(dptr+6,sptr); sptr+=dim;
            COPY(dptr+7,sptr); sptr+=dim;
            COPY(dptr+8,sptr); sptr+=dim;
            COPY(dptr+9,sptr); sptr+=dim;
            COPY(dptr+10,sptr); sptr+=dim;
            COPY(dptr+11,sptr); sptr+=dim;
            COPY(dptr+12,sptr); sptr+=dim;
            COPY(dptr+13,sptr); sptr+=dim;
            COPY(dptr+14,sptr); sptr+=dim;
            COPY(dptr+15,sptr); sptr+=dim;
            COPY(dptr+16,sptr); sptr+=dim;
            COPY(dptr+17,sptr); sptr+=dim;
            COPY(dptr+18,sptr); sptr+=dim;
            COPY(dptr+19,sptr); sptr+=dim;
            COPY(dptr+20,sptr); sptr+=dim;
            COPY(dptr+21,sptr); sptr+=dim;
            COPY(dptr+22,sptr); sptr+=dim;
            COPY(dptr+23,sptr); sptr+=dim;
            COPY(dptr+24,sptr); sptr+=dim;
            COPY(dptr+25,sptr); sptr+=dim;
            COPY(dptr+26,sptr); sptr+=dim;
            COPY(dptr+27,sptr); sptr+=dim;
            COPY(dptr+28,sptr); sptr+=dim;
            COPY(dptr+29,sptr); sptr+=dim;
            COPY(dptr+30,sptr); sptr+=dim;
            COPY(dptr+31,sptr);
        }
    }
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

/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct
{
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

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
    sum->red += (int)p.red;
    sum->green += (int)p.green;
    sum->blue += (int)p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum)
{
    current_pixel->red = (unsigned short)(sum.red / sum.num);
    current_pixel->green = (unsigned short)(sum.green / sum.num);
    current_pixel->blue = (unsigned short)(sum.blue / sum.num);
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
    for (ii = max(i - 1, 0); ii <= min(i + 1, dim - 1); ii++)
        for (jj = max(j - 1, 0); jj <= min(j + 1, dim - 1); jj++)
            accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

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

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
 #define fastmin(a,b)  (a < b ? a : b)
#define fastmax(a, b) (a > b ? a : b)
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst)
{
    int i, j, rij;
    int rindex = dim;
    // Corner cases
    dst[0].red = (src[0].red+src[1].red+src[dim].red+src[dim+1].red)>>2;
    dst[0].blue = (src[0].blue+src[1].blue+src[dim].blue+src[dim+1].blue)>>2;
    dst[0].green = (src[0].green+src[1].green+src[dim].green+src[dim+1].green)>>2;
    dst[dim-1].red = (src[dim-1].red+src[dim-2].red+src[dim*2-1].red+src[dim*2-2].red)>>2;
    dst[dim-1].blue = (src[dim-1].blue+src[dim-2].blue+src[dim*2-1].blue+src[dim*2-2].blue)>>2;
    dst[dim-1].green = (src[dim-1].green+src[dim-2].green+src[dim*2-1].green+src[dim*2-2].green)>>2;

    dst[dim*(dim-1)].red = (src[dim*(dim-1)].red+src[dim*(dim-1)+1].red+src[dim*(dim-2)].red+src[dim*(dim-2)+1].red)>>2;
    dst[dim*(dim-1)].blue = (src[dim*(dim-1)].blue+src[dim*(dim-1)+1].blue+src[dim*(dim-2)].blue+src[dim*(dim-2)+1].blue)>>2;
    dst[dim*(dim-1)].green = (src[dim*(dim-1)].green+src[dim*(dim-1)+1].green+src[dim*(dim-2)].green+src[dim*(dim-2)+1].green)>>2;

    dst[dim*dim-1].red = (src[dim*dim-1].red+src[dim*dim-2].red+src[dim*(dim-1)-1].red+src[dim*(dim-1)-2].red)>>2;
    dst[dim*dim-1].blue = (src[dim*dim-1].blue+src[dim*dim-2].blue+src[dim*(dim-1)-1].blue+src[dim*(dim-1)-2].blue)>>2;
    dst[dim*dim-1].green = (src[dim*dim-1].green+src[dim*dim-2].green+src[dim*(dim-1)-1].green+src[dim*(dim-1)-2].green)>>2;
    for (j = 1; j < dim-1; j++)
    {
        dst[j].red = (src[j].red+src[j-1].red+src[j+1].red+src[j+dim].red+src[j+1+dim].red+src[j-1+dim].red)/6;
        dst[j].green = (src[j].green+src[j-1].green+src[j+1].green+src[j+dim].green+src[j+1+dim].green+src[j-1+dim].green)/6;
        dst[j].blue = (src[j].blue+src[j-1].blue+src[j+1].blue+src[j+dim].blue+src[j+1+dim].blue+src[j-1+dim].blue)/6;
    }
    for (j = dim*(dim-1)+1; j < dim*dim-1; j++)
    {
        dst[j].red = (src[j].red+src[j-1].red+src[j+1].red+src[j-dim].red+src[j+1-dim].red+src[j-1-dim].red)/6;
        dst[j].green = (src[j].green+src[j-1].green+src[j+1].green+src[j-dim].green+src[j+1-dim].green+src[j-1-dim].green)/6;
        dst[j].blue = (src[j].blue+src[j-1].blue+src[j+1].blue+src[j-dim].blue+src[j+1-dim].blue+src[j-1-dim].blue)/6;
    }
    for (j = dim; j < dim*(dim-1); j+=dim)
    {
        dst[j].red = (src[j].red+src[j-dim].red+src[j+1].red+src[j+dim].red+src[j+1+dim].red+src[j-dim+1].red)/6;
        dst[j].green = (src[j].green+src[j-dim].green+src[j+1].green+src[j+dim].green+src[j+1+dim].green+src[j-dim+1].green)/6;
        dst[j].blue = (src[j].blue+src[j-dim].blue+src[j+1].blue+src[j+dim].blue+src[j+1+dim].blue+src[j-dim+1].blue)/6;
    }
    for (j = dim+dim-1; j < dim*dim-1; j+=dim)
    {
        dst[j].red = (src[j].red+src[j-1].red+src[j-dim].red+src[j+dim].red+src[j-dim-1].red+src[j-1+dim].red)/6;
        dst[j].green = (src[j].green+src[j-1].green+src[j-dim].green+src[j+dim].green+src[j-dim-1].green+src[j-1+dim].green)/6;
        dst[j].blue = (src[j].blue+src[j-1].blue+src[j-dim].blue+src[j+dim].blue+src[j-dim-1].blue+src[j-1+dim].blue)/6;
    }
    for (i = 1; i < dim-1; i++)
    {
        for (j = 1; j < dim-1; j++)
        {
            rij = rindex+j;
            dst[rij].red = (src[rij].red+src[rij-1].red+src[rij+1].red+src[rij-dim].red+src[rij-dim-1].red+src[rij-dim+1].red+src[rij+dim].red+src[rij+dim+1].red+src[rij+dim-1].red)/9;
            dst[rij].green = (src[rij].green+src[rij-1].green+src[rij+1].green+src[rij-dim].green+src[rij-dim-1].green+src[rij-dim+1].green+src[rij+dim].green+src[rij+dim+1].green+src[rij+dim-1].green)/9;
            dst[rij].blue = (src[rij].blue+src[rij-1].blue+src[rij+1].blue+src[rij-dim].blue+src[rij-dim-1].blue+src[rij-dim+1].blue+src[rij+dim].blue+src[rij+dim+1].blue+src[rij+dim-1].blue)/9;
        }
        rindex += dim;
    }
}
/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions()
{
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}
