#include "recognitionEyes.h"

#include <stdio.h>

#include "image.h"
#include "imageColor.h"
#include "imageFilters.h"

/**
 * Fill all white spaces with red, if the pixel to the left is also red.
 * Red Lines Left -> Right
 *
 * image - The image structure.
 */
int findEyes_LeftToRight(Image *image) {

	int imageWidth = (*image).width;
	int imageHeight = (*image).height;

	int changeCount = 0;

	int arrayWidth = imageWidth * ROW_STRIDE;
	int arrayImageindex = 0;

	for (int heightIndex = 0; heightIndex < imageHeight; heightIndex++) {
		for (int widthIndex = 0; widthIndex < arrayWidth; widthIndex = widthIndex + ROW_STRIDE) {

			int red   = (int) (*image).data[arrayImageindex + 0];
			int green = (int) (*image).data[arrayImageindex + 1];
			int blue  = (int) (*image).data[arrayImageindex + 2];

			if (widthIndex >= 3) {

				int redLeft   = (int) (*image).data[arrayImageindex - 3];
				int greenLeft = (int) (*image).data[arrayImageindex - 2];
				int blueLeft  = (int) (*image).data[arrayImageindex - 1];

				if ((redLeft == 255 && greenLeft == 0 && blueLeft == 0) && (red == 255 && green == 255 && blue == 255)) {
					red = 255;
					green = 0;
					blue = 0;
					changeCount++;
				}

			} else {
				red = 255;
				green = 0;
				blue = 0;
			}

			(*image).data[arrayImageindex + 0]  = (char) red;
			(*image).data[arrayImageindex + 1]  = (char) green;
			(*image).data[arrayImageindex + 2]  = (char) blue;

			arrayImageindex = arrayImageindex + ROW_STRIDE;

		}
	}

	return changeCount;
}

/**
 * Fill the image from right to left.
 *
 * image - The image structure.
 */
int findEyes_RightToLeft(Image *image) {
	// Red Lines Right <- Left

	int imageWidth = (*image).width;
	int imageHeight = (*image).height;

	int changeCount = 0;
	int arrayWidth = imageWidth * ROW_STRIDE;
	int arrayImageindex = (arrayWidth * imageHeight);
	for (int heightIndex = imageHeight; heightIndex > 0; heightIndex--) {
		for (int widthIndex = arrayWidth; widthIndex > 0; widthIndex = widthIndex - ROW_STRIDE) {

			int red   = (int) (*image).data[arrayImageindex + 0];
			int green = (int) (*image).data[arrayImageindex + 1];
			int blue  = (int) (*image).data[arrayImageindex + 2];

			if (widthIndex < (arrayWidth - ROW_STRIDE)) {

				int redRight   = (int) (*image).data[arrayImageindex + 3];
				int greenRight = (int) (*image).data[arrayImageindex + 4];
				int blueRight  = (int) (*image).data[arrayImageindex + 5];

				if ((redRight == 255 && greenRight == 0 && blueRight == 0) && (red == 255 && green == 255 && blue == 255)) {
					red = 255;
					green = 0;
					blue = 0;
					changeCount++;
				}

			} else {
				red = 255;
				green = 0;
				blue = 0;
			}

			(*image).data[arrayImageindex + 0]  = (char) red;
			(*image).data[arrayImageindex + 1]  = (char) green;
			(*image).data[arrayImageindex + 2]  = (char) blue;

			arrayImageindex = arrayImageindex - ROW_STRIDE;

		}
	}

	return changeCount;
}

/**
 * Fill colors from up to down.
 *
 * image - The image structure.
 */
int findEyes_UpToDown(Image *image) {

	int imageWidth = (*image).width;
	int imageHeight = (*image).height;

	// Make red if pixels is whight and top or bottom is red. - DOWN
	int changeCount = 0;
	int arrayWidth = imageWidth * ROW_STRIDE;
	int arrayImageindex = 0;
	for (int heightIndex = 0; heightIndex < imageHeight; heightIndex++) {
		for (int widthIndex = 0; widthIndex < arrayWidth; widthIndex = widthIndex + ROW_STRIDE) {

			int red   = (int) (*image).data[arrayImageindex + 0];
			int green = (int) (*image).data[arrayImageindex + 1];
			int blue  = (int) (*image).data[arrayImageindex + 2];

			if (heightIndex > 0) {

				int tempArray = arrayImageindex - arrayWidth;
				int redAbove   = (int) (*image).data[tempArray + 0];
				int greenAbove = (int) (*image).data[tempArray + 1];
				int blueAbove  = (int) (*image).data[tempArray + 2];

				if ((redAbove == 255 && greenAbove == 0 && blueAbove == 0) && (red == 255 && green == 255 && blue == 255)) {
					red = 255;
					green = 0;
					blue = 0;
					changeCount++;
				}

			}

			(*image).data[arrayImageindex + 0]  = (char) red;
			(*image).data[arrayImageindex + 1]  = (char) green;
			(*image).data[arrayImageindex + 2]  = (char) blue;

			arrayImageindex = arrayImageindex + ROW_STRIDE;

		}
	}

	return changeCount;
}

/**
 * Fill an image from down to up.
 *
 * image - The image structure.
 */
int findEyes_DownToUp(Image *image) {

	int imageWidth = (*image).width;
	int imageHeight = (*image).height;

	// Make red if pixels is whight and top or bottom is red. - UP
	int changeCount = 0;
	int arrayWidth = imageWidth * ROW_STRIDE;
	int arrayImageindex = (arrayWidth * imageHeight);
	for (int heightIndex = imageHeight; heightIndex > 0; heightIndex--) {
		for (int widthIndex = arrayWidth; widthIndex > 0; widthIndex = widthIndex - 3) {

			int red   = (int) (*image).data[arrayImageindex + 0];
			int green = (int) (*image).data[arrayImageindex + 1];
			int blue  = (int) (*image).data[arrayImageindex + 2];

			if (heightIndex < imageHeight) {

				int tempArray = arrayImageindex + arrayWidth;
				int redBelow   = (int) (*image).data[tempArray + 0];
				int greenBelow = (int) (*image).data[tempArray + 1];
				int blueBelow  = (int) (*image).data[tempArray + 2];

				if ((redBelow == 255 && greenBelow == 0 && blueBelow == 0) && (red == 255 && green == 255 && blue == 255)) {
					red = 255;
					green = 0;
					blue = 0;
					changeCount++;
				}

			}

			(*image).data[arrayImageindex + 0]  = (char) red;
			(*image).data[arrayImageindex + 1]  = (char) green;
			(*image).data[arrayImageindex + 2]  = (char) blue;

			arrayImageindex = arrayImageindex - ROW_STRIDE;

		}
	}

	return changeCount;
};

/**
 * Replace every pixel in a image with another.
 *
 * image - The image strucutre.
 * red
 * green
 * blue
 * replaceRed
 * replaceGreen
 * replaceBlue
 */
void convertColor(Image *image, int red, int green, int blue, int replaceRed, int replaceGreen, int replaceBlue) {

	int imageWidth = (*image).width;
	int imageHeight = (*image).height;

	int arrayImageSize = ((imageWidth * ROW_STRIDE) * imageHeight);
	for (int i = 0; i < arrayImageSize; i = i + 3) {

		int imageRed = (*image).data[i + 0];
		int imageGreen = (*image).data[i + 1];
		int imageBlue = (*image).data[i + 2];

		if (imageRed == red && imageGreen == green && imageBlue == blue) {
			(*image).data[i + 0]  = (char) replaceRed;
			(*image).data[i + 1]  = (char) replaceGreen;
			(*image).data[i + 2]  = (char) replaceBlue;
		}

	}
}

/**
 *
 * xIndex
 * yIndex
 * color
 * size
 */
Eye analyzeWhiteGapsToFindEyes(int xIndex[], int yIndex[], int color[], int size) {
	Eye eye;

	int yLineGoupingCount = 1;
	for (int index = 0; index < (size - 1); index++) {
		if (yIndex[index] == yIndex[index + 1]) {
			//printf("Lines that contain white: %i, count: %i:\n", yIndex[index], yLineGoupingCount);
			yLineGoupingCount++;
		} else {
			printf("DONE - Lines that contain white: %i, count: %i:\n", yIndex[index], yLineGoupingCount);
			yLineGoupingCount = 1;
		}
	}


	return eye;
}

/**
 *
 * image - The image structure.
 */
void eyeLocation(Image *image) {

	int imageWidth = (*image).width;
	int imageHeight = (*image).height;

	int countPoss = 0;
	int xPoss[imageHeight];
	int yPoss[imageHeight];

	int linePoss[imageHeight];
	int linePossPos = 0;

	int horizontalYLine[1000];
	int verticalXLine[1000];
	int colorXLine[1000];
	int linePosition = 0;

	// Make red if pixels is white and top or bottom is red. - DOWN
	int changeCount = 0;
	int arrayWidth = imageWidth * ROW_STRIDE;
	int arrayImageindex = 0;
	int heightCounter = 0;

	for(int heightIndex = 0; heightIndex < imageHeight; heightIndex++) {

		int white = 0;
		int whiteCount = 0;

		for(int widthIndex = 0; widthIndex < arrayWidth; widthIndex = widthIndex + 3) {

			int red   = (int) (*image).data[arrayImageindex + 0];
			int green = (int) (*image).data[arrayImageindex + 1];
			int blue  = (int) (*image).data[arrayImageindex + 2];

			// Analyze the number of white gaps on a line.
			if (red == 255 && green == 255 && blue == 255 && white == 0) {
				white = 1;
				whiteCount++;
				//printf("White: %i, ", widthIndex);

				// Mark the start of white pixels.
				if (linePosition < 1000) {
					horizontalYLine[linePosition] = heightIndex;
					verticalXLine[linePosition] = widthIndex;
					colorXLine[linePosition] = 0;
					linePosition++;
				}

			} else if (red == 0 && green == 0 && blue == 0 && white == 1) {
				white = 0;

				// Mark the start of Black pixels.
				if (linePosition < 1000) {
					horizontalYLine[linePosition] = heightIndex;
					verticalXLine[linePosition] = widthIndex;
					colorXLine[linePosition]  = 1;
					linePosition++;
				}
				//printf("Black: %i, ", widthIndex);
			}

			arrayImageindex = arrayImageindex + 3;

		}
	}

	Eye eye = analyzeWhiteGapsToFindEyes(verticalXLine, horizontalYLine, colorXLine, linePosition);

}

/**
 * Fine the eyes on an image.
 *
 * image - A image structure.
 */
void findEyes(Image *image) {

	printf("Appling Filter.\n");
	applyFilter(filterBlack, image);

	int totalChange = 1;
	int threshHold = 10;
	int totalLoops = 0;
	int lr = 0;
	int rl = 0;
	int ud = 0;
	int du = 0;

	while(totalChange > 0 && totalLoops < threshHold) {
		lr = findEyes_LeftToRight(image);
		rl = findEyes_RightToLeft(image);
		ud = findEyes_UpToDown(image);
		du = findEyes_DownToUp(image);
		totalChange = lr + rl + ud + du;
		totalLoops++;
		printf("Total Pixel Processed: %i\n", totalChange);
	}

	if (totalLoops == threshHold) {
		printf("ERROR - Error processing image.\n");
		printf("ERROR - lr: %i, rl: %i, ud: %i, du: %i\n", lr, rl, ud, du);
	}

	convertColor(image, 255, 0, 0, 0, 0, 0);

	eyeLocation(image);

}

/**
 * Fill all white spaces with red, if the pixel to the left is also red.
 * Red Lines Left -> Right
 *
 * image - The image structure.
 */
int fill_LeftToRight(Image *image) {

	int imageWidth = (*image).width;
	int imageHeight = (*image).height;

	int changeCount = 0;

	int arrayWidth = imageWidth * ROW_STRIDE;
	int arrayImageindex = 0;

	Color color;

	for (int heightIndex = 0; heightIndex < imageHeight; heightIndex++) {
		for (int widthIndex = 0; (widthIndex + 6) < arrayWidth; widthIndex = widthIndex + ROW_STRIDE) {

			getColor(&color, image->data, arrayImageindex);

			if (isColor(&color, COLOR_WHITE)) {
			//if (color.red < 50 && color.green < 50 && color.blue < 50) {
				color.red = 255;
				color.green = 0;
				color.blue = 0;
			}

			(*image).data[arrayImageindex + 0]  = (char) color.red;
			(*image).data[arrayImageindex + 1]  = (char) color.green;
			(*image).data[arrayImageindex + 2]  = (char) color.blue;

			arrayImageindex = arrayImageindex + ROW_STRIDE;

		}
	}

	return changeCount;
}


void findEyes2(Image *image) {

	printf("Filling up the top background\n");

	if(isColorRGB(0, 0, 255, COLOR_BLUE) == 1) {
		printf("BLUE\n");
	} else {
		printf("NOT BLUE\n");
	}

	fill_LeftToRight(image);

}