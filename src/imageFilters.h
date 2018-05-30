/******************************************************************************
 * File:	imageFilters.h
 *
 * Description: These are filters that can be applied to a image to manipulate
 * 	the image data.
 *
 *****************************************************************************/
#ifndef IMAGE_FILTERS_
#define IMAGE_FILTERS_

#include "image.h"
#include "imageColor.h"

/*
There is a base function that will loop through all the pixels of an image and replace apply the RGB through a seperate filter.

Example of how to declare the function pointers.
	void (*fun_ptr_filterBlackCat)(int *, int *, int *) = filterBlackCat;
	void (*fun_ptr_filterColorRed)(int *, int *, int *) = filterColorRed;
	void (*fun_ptr_filterRedBlackCat)(int *, int *, int *) = filterRedBlackCat;

	// Apply the filter to an image.
	applyFilter(filterRedBlackCat, &image);

*/

// Filters for the applyFilter function, it follows the API of red, green, blue.
void filterColorRed(int *red, int *green, int *blue);
void filterBlack(int *red, int *green, int *blue);
void filterRedBlack(int *red, int *green, int *blue);

// Function for applying a filter, filters are listed above.
void applyFilter(void (*fnc_ptr)(int *, int *, int *), Image *image);

// Add one image on top of another image.
void applyImage(Image *baseImage, Image *newImage, int x, int y, Color baseColor);

#endif