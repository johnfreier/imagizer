#include <stdio.h>

#include "imageColor.h"

#ifndef IMAGE_DEBUG
#define IMAGE_DEBUG

// __FILE__ = File name
// __LINE__ = Line number
// __func__ = Function name
// __VA_ARGS__ = Function arguments

#ifdef DEBUG
	#define dprint(message) { printf("%d:DEBUG:" message, __LINE__); }
	#define dprintf(message, ...) { printf("%d:DEBUG:" message, __LINE__, __VA_ARGS__); }
#else
	#define dprint(message) { }
	#define dprintf(message, ...) { }
#endif

// Print something or other...
void debugPrintPixelColor(int x, int y, unsigned char **p_arrayImage, int *imageWidth, int *imageHeight);

// Debug print out the colors.
void debugPrintColorRGB(int red, int green, int blue);

// Debug print out the color structure.
void debugPrintColor(Color *color);

#endif