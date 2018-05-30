/******************************************************************************
 * File:	image.h
 *
 * Description: This file contains some of the core items needed throughout
 *	the imagizer.
 *
 *****************************************************************************/
#ifndef IMAGE_
#define IMAGE_

#define ROW_STRIDE 3 // Skip number for R G B in a char array.

// Image structure - Holds important data about an image.
typedef struct {
	int width;
	int height;
	unsigned char *data;
} Image;

#endif