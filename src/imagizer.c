#include <stdio.h>
#include <string.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <stdlib.h>

#include "imageColor.h"
#include "imageDebug.h"
#include "imageFilters.h"
#include "imageProcessor.h"
#include "recognitionEyes.h"

int main(int argc, char **argv) {

	dprint("!!!DEBUG MODE!!!\n");

	Image image;
	//Image mustache;

	printf("Reading Image.\n");
	read_JPEG_file("etc/images/cat1.jpg", &image);

	//printf("Reading Mustache.\n");
	//read_JPEG_file("etc/images/mustache.jpg", &mustache);

#ifdef DEBUG
	int testColor = (int) image.data[0];
	printf("Test Color: 173 == %i\n", testColor);
#endif

	printf("Appling Filter.\n");
	applyFilter(filterBlack, &image);

	//printf("Find Eyes.\n");
	findEyes(&image);

	//applyFilter(filterBlack, &mustache);

	//Color white;
	//white.red = 210;
	//white.green = 210;
	//white.blue = 210;
	//applyImage(&image, &mustache, 180, 125, white);

	//printf("Writing Image.\n");
	write_JPEG_file("etc/images/cat2.jpg", &image);


	printf("Image width: %d\n", image.width);
	printf("Image height: %d\n", image.height);

	free(image.data);
	//free(mustache.data);

	return 1;

}
