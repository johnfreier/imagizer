#include "imageProcessor.h"

#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

/**
 * Read in a JPEG file and store it in Image structure.
 *
 * filename - The JPEG file to open.
 * image - The image structure the image data will get stored in.
 */
int read_JPEG_file(char *filename, Image *image) {

	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	FILE *infile;

	if ((infile = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		return 0;
	}
	// Register error structure.
	cinfo.err = jpeg_std_error(&jerr);

	jpeg_create_decompress(&cinfo);

	jpeg_stdio_src(&cinfo, infile);

	jpeg_read_header(&cinfo, TRUE);

	jpeg_start_decompress(&cinfo);


	// Set class variables.
	(*image).width = cinfo.output_width;
	(*image).height = cinfo.output_height;

	// Set the rowStride, should be (red, green, blue) * width of the image.
	int rowStride = cinfo.output_width * cinfo.output_components;

	// Creating the line buffer, the last param is for the line height.
	// Set to 1 for when we read 1 line in at a time.
	JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, rowStride, 1);

	// Array that will hold the images data.
	int imageWidth = ((*image).width) * ROW_STRIDE;
	int imageHeight = ((*image).height);

	// Initialize the array for the imaage data.
	(*image).data = malloc(sizeof(char)*((imageWidth * imageHeight)+1));

	int totalDataPlace = 0;
	while (cinfo.output_scanline < cinfo.output_height) {

		jpeg_read_scanlines(&cinfo, buffer, 1);

		for (int i=0; i < rowStride; i++) {
			(*image).data[totalDataPlace] = (unsigned char) buffer[0][i];

			totalDataPlace++;
		}
	}

	jpeg_finish_decompress(&cinfo);

	jpeg_destroy_decompress(&cinfo);

	fclose(infile);

	return 0;

};

/**
 * Write the image data to a file.
 *
 * filename - The filename to where the image data should be written to.
 * image - The image structure to get the image data from to create the file.
 */
int write_JPEG_file(char *filename, Image *image) {

	int quality = 100;

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	FILE *outfile;
	JSAMPROW row_pointer[1];
	int rowStride;

	// Register the error structure.
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	// Open the file for writing.
	if ((outfile = fopen(filename, "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		return 0;
	}
	jpeg_stdio_dest(&cinfo, outfile);

	cinfo.image_width = (*image).width;
	cinfo.image_height = (*image).height;
	cinfo.input_components = ROW_STRIDE;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);

	jpeg_set_quality(&cinfo, quality, TRUE);

	jpeg_start_compress(&cinfo, TRUE);

	rowStride = cinfo.image_width * ROW_STRIDE;

	unsigned char *arrayImage = (*image).data;
	unsigned char rowPrint[rowStride];
	int arrayImageindex = 0;
	while (cinfo.next_scanline < cinfo.image_height) {

		for (int i = 0; i < rowStride; i = i + ROW_STRIDE) {

			rowPrint[i + 0] = arrayImage[arrayImageindex + 0];
			rowPrint[i + 1] = arrayImage[arrayImageindex + 1];
			rowPrint[i + 2] = arrayImage[arrayImageindex + 2];

			arrayImageindex = arrayImageindex + ROW_STRIDE;

		}

		row_pointer[0] = (JSAMPROW) &rowPrint;

		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);

	fclose(outfile);

	jpeg_destroy_compress(&cinfo);

	return 0;

};