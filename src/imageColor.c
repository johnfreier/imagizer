#include "imageColor.h"

#include <stdio.h>
#include <string.h>

// Boolean values of either true or false.
typedef enum {
	FALSE,
	TRUE
} boolean;

// A single color structure.
typedef struct {
	const char *color;
	int red;
	int green;
	int blue;
} sColor;

// A statuc array of colors.
static sColor colors[] = {
	{ COLOR_BLUE,  000, 000, 255 },
	{ COLOR_BLACK, 000, 000, 000 },
	{ COLOR_WHITE, 020, 020, 020 }
};

#define COLOR_SIZE (sizeof(colors)/sizeof(sColor))

/**
 * Check to see if a colors RGB value match a color.
 *
 * red
 * green
 * blue
 * testColor A string const color, "BLUE", "BLACK", "WHITE"...Use the defined colors in the header.
 */
int isColorRGB(int red, int green, int blue, const char *testColor) {

	boolean result = FALSE;

	for (int index = 0; index < COLOR_SIZE; index++) {
		sColor *color = colors + index;
		if (strcmp(color->color, testColor) == 0) {
			if (color->red == red && color->green == green && color->blue == blue) {
				result = TRUE;
			}
		}

	}

	return result;

}

/**
 * Check to see if a colors RGB value match a color.
 *
 * color
 * testColor A string const color, "BLUE", "BLACK", "WHITE"...Use the defined colors in the header.
 */
int isColor(Color *color, const char *testColor) {
	return isColorRGB(color->red, color->green, color->blue, testColor);
}

/**
 *Convert an array of colors following the standard row_stride of 0 = red, 1 = green, 2 = blue.
 *
 * color A pointer to the color that will have its values updated.
 * data A pointer to the location in the array of data.
 * index The location to read the color.
 */
void getColor(Color *color, unsigned char *data, int index) {

	color->red = data[index + 0];
	color->green = data[index + 1];
	color->blue = data[index + 2];

}