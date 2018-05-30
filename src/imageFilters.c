#include "imagefilters.h"

#include <stdio.h>

#include "image.h"
#include "imageColor.h"
#include "imageDebug.h"

/**
 * Darken the color red.
 *
 * red
 * green
 * blue
 */
void filterColorRed(int *red, int *green, int *blue) {
	if (*red + 155 <= 255) {
		*red = *red + 155;
	}
}

/**
 * If the color pixels are less then 100 then make the colors black.
 *
 * red
 * green
 * blue
 */
void filterBlack(int *red, int *green, int *blue) {
	int blackShade = 100;
	if (*red < blackShade && *green < blackShade && *blue < blackShade) {
		*red = 0;
		*green = 0;
		*blue = 0;
	} else {
		*red = 255;
		*green = 255;
		*blue = 255;
	}
}

/**
 * Change all tones of black that are less then 150 to the color red.
 *
 * red
 * green
 * blue
 */
void filterRedBlack(int *red, int *green, int *blue) {
	int blackShade = 150;
	if (*red < blackShade && *green < blackShade && *blue < blackShade) {
		*red = 0;
		*green = 0;
		*blue = 0;
	} else {
		*red = 255;
		*green = 0;
		*blue = 0;
	}
}

/**
 * Apply a filter to every pixel in the image.
 *
 * fnc_ptr - Function that each pixel gets ran through.
 * image - Image that gets the filter function applied.
 */
void applyFilter(void (*fnc_ptr)(int *, int *, int *), Image *image) {

	int imageWidth  = (*image).width;
	int imageHeight = (*image).height;
	unsigned char *arrayImage = (*image).data;

	int arrayWidth = imageWidth * ROW_STRIDE;
	int arrayImageindex = 0;

	for (int heightIndex = 0; heightIndex < imageHeight; heightIndex++) {
		for (int widthIndex = 0; widthIndex < arrayWidth; widthIndex = widthIndex + 3) {

			int red   = (int) arrayImage[arrayImageindex + 0];
			int green = (int) arrayImage[arrayImageindex + 1];
			int blue  = (int) arrayImage[arrayImageindex + 2];

			(fnc_ptr)(&red, &green, &blue);

			arrayImage[arrayImageindex + 0]  = (char) red;
			arrayImage[arrayImageindex + 1]  = (char) green;
			arrayImage[arrayImageindex + 2]  = (char) blue;

			arrayImageindex = arrayImageindex + ROW_STRIDE;

		}

	}

}
/**
 * Apply an image on top of another image.
 *
 * baseImabe - The image that will get the image placed on.
 * newImage - The new image to place on top.
 * x - x cord of the new image, do not include the rowStride.
 * y - y cord of the new image.
 * baseColor - is the transparent color on the base image to ignore.
 */
void applyImage(Image *baseImage, Image *newImage, int x, int y, Color baseColor) {

	int imageWidth  = (*baseImage).width;
	int imageHeight = (*baseImage).height;
	unsigned char *arrayImage = (*baseImage).data;


	int newImageWidth = (*newImage).width;
	int newImageHeight = (*newImage).height;
	unsigned char *newArrayImage = (*newImage).data;

	int arrayWidth = imageWidth * ROW_STRIDE;
	int arrayImageindex = 0;
	int newArryImageIndex = 0;

	int newImageXStart = (x * 3);
	int newImageXEnd = ((newImageWidth + 1) * ROW_STRIDE) + newImageXStart;

	dprintf("ImageWidth: %i, ImageEnd: %i\n", newImageWidth, newImageXEnd);

	for (int heightIndex = 0; heightIndex < imageHeight; heightIndex++) {
		for (int widthIndex = 0; widthIndex < arrayWidth; widthIndex = widthIndex + ROW_STRIDE) {

			if (((widthIndex > newImageXStart) && (widthIndex < newImageXEnd))
				&& ((heightIndex > y) && (heightIndex < (y + newImageHeight)))) {

				int red   = newArrayImage[newArryImageIndex + 0];
				int green = newArrayImage[newArryImageIndex + 1];
				int blue  = newArrayImage[newArryImageIndex + 2];


				if (red <= baseColor.red && green <= baseColor.green && blue <= baseColor.blue) {

					arrayImage[arrayImageindex + 0] = (char) red;
					arrayImage[arrayImageindex + 1] = (char) green;
					arrayImage[arrayImageindex + 2] = (char) blue;

				}

				newArryImageIndex = newArryImageIndex + ROW_STRIDE;
			}

			arrayImageindex = arrayImageindex + ROW_STRIDE;

		}
	}

}