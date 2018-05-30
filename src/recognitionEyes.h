/******************************************************************************
 * File:	recognitionEyes.h
 *
 * Description: An attempt to find the eyes of cat in an image.
 *
 *****************************************************************************/
#ifndef RECOGNITION_EYES_
#define RECOGNITION_EYES_

#include "image.h"

// Eye structure - The initial first structure to find the eyes of an image.
typedef struct {
	int x;
	int y;
} Eye;

// main function for finding the eyes.
void findEyes(Image *image);

// This is a test of trying to identify the head of a cat.
void findEyes2(Image *image);

#endif