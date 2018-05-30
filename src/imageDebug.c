#include "imageDebug.h"

#include <stdio.h>

#include "image.h"
#include "imageColor.h"

/**
 * Helps print debug pixels.
 *
 * Example:debugPrintPixelColor(2, 15, &p_arrayImage, &imageWidth, &imageHeight);
 *
 * x
 * y
 * p_arrayImage
 * pImageWidth
 * pImageHeight
 */
void debugPrintPixelColor(int x, int y, unsigned char **p_arrayImage, int *pImageWidth, int *pImageHeight) {
	int imageFound = 0;
	int arrayImageindex = 0;
	int breakpoint = 0;
	int rowStride = *pImageWidth * ROW_STRIDE;
	int imageHeight = *pImageHeight;

	for(int heightIndex = 0; heightIndex < imageHeight; heightIndex++) {
		for(int widthIndex = 0; widthIndex < rowStride; widthIndex = widthIndex + ROW_STRIDE) {
			if (widthIndex == x && heightIndex == y) {
				int red   = (int) p_arrayImage[0][arrayImageindex + 0];
				int green = (int) p_arrayImage[0][arrayImageindex + 1];
				int blue  = (int) p_arrayImage[0][arrayImageindex + 2];

				printf("DEBUG: r: %i, g: %i, b: %i, widthIndex: %i, heightIndex: %i, arrayIndex: %i\n", red, green, blue, widthIndex, heightIndex, arrayImageindex);
				imageFound++;
			}
			arrayImageindex = arrayImageindex + ROW_STRIDE;
		}
	}

	if (imageFound == 0) {
		printf("ERROR: Image pixel not found. Make sure that x is divisible by 3. \n");
	}
}

/**
 * Debug print out the colors to the console.
 * red
 * green
 * blue
 */
void debugPrintColorRGB(int red, int green, int blue) {
	printf("Red: %d, Green: %d, Blue: %d\n", red, green, blue);
}

/**
 * Debug print out the color to the console.
 *
 * color Color structure.
 */
void debugPrintColor(Color *color) {
	debugPrintColorRGB(color->red, color->green, color->blue);
}