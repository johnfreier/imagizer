/******************************************************************************
 * File:	imageProcessor.h
 *
 * Description: These functions are used to open and write to a JPEG image.
 *
 *****************************************************************************/
#ifndef IMAGE_PROCESSOR_
#define IMAGE_PROCESSOR_

#include "image.h"

int read_JPEG_file(char *filename, Image *image);
int write_JPEG_file(char *filename, Image *image);

#endif