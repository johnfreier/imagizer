/******************************************************************************
 * File:	imageColor.h
 *
 * Description: This is used for color handling.  There are function to help
 * translate, RGB to colors and name.
 *
 *****************************************************************************/
#ifndef IMAGE_COLOR
#define IMAGE_COLOR

#define COLOR_BLACK "BLACK"
#define COLOR_BLUE  "BLUE"
#define COLOR_WHITE "WHITE"

 // Color structure - Is the bases of Red, Green, Blue as one struct.
typedef struct {
	int red;
	int green;
	int blue;
} Color;

// Check to see if RGB match a color. The color parameter should be one of the defined colors above.
int isColorRGB(int red, int green, int blue, const char *color);

// Check to see if a color matches a static defined color.
int isColor(Color *color, const char *testColor);

// Convert the array of colors in to a Color structure.
void getColor(Color *color, unsigned char *data, int index);

#endif