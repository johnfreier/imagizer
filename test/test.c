#include <stdio.h>
#include <string.h>
#include <jpeglib.h>
#include <setjmp.h>
#include <stdlib.h>

unsigned char *raw_image = NULL;

JSAMPLE * image_buffer;
JSAMPARRAY buffer;
int image_height;
int image_width;
JSAMPARRAY pImage;

unsigned char *p_arrayImage;


const char COLOR_0 = 0x00;
const char COLOR_255 = 0xFF;

METHODDEF(void)
my_error_exit (j_common_ptr cinfo) {
	/* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
	my_error_ptr myerr = (my_error_ptr) cinfo->err;

	/* Always display the message. */
	/* We could postpone this until after returning, if we chose. */
	(*cinfo->err->output_message) (cinfo);

	/* Return control to the setjmp point */
	longjmp(myerr->setjmp_buffer, 1);
}

void
put_scanline_someplace (JSAMPLE* ba, int row_stride) {

	static int height;
	int i;
	unsigned char test[image_width * 3];

	if (height == 200) {
		for (i=0; i < row_stride; i = i + 3) {
			printf("%d,%d,%d:%d\n", ba[i], ba[i+1], ba[i+2], i);
			test[i] = ba[i];
			test[i + 1] = ba[i + 1];
			test[i + 2] = ba[i + 2];
		}
	}

	printf ("width: %3d height: %3d\n", row_stride, height++);
}

GLOBAL(int)
read_JPEG_file (char * filename)
{

	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;

	FILE * infile;

	int row_stride;

	//JSAMPARRAY buffer;

	if ((infile = fopen(filename, "rb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		return 0;
	}

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;

	/* Establish the setjmp return context for my_error_exit to use. */
	if (setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		return 0;
	}

	jpeg_create_decompress(&cinfo);

	jpeg_stdio_src(&cinfo, infile);

	(void) jpeg_read_header(&cinfo, TRUE);

	(void) jpeg_start_decompress(&cinfo);

	image_width = cinfo.output_width;
	image_height = cinfo.output_height;

	row_stride = cinfo.output_width * cinfo.output_components;
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

	unsigned char data[image_height][image_width * 3];
	int ROWS = image_width * 3;

	unsigned char temp[image_height * image_width];
	p_arrayImage = temp;

	int dataHeight = 0;
	int totalDataPlace = 0;
	while (cinfo.output_scanline < cinfo.output_height) {
		int t = jpeg_read_scanlines(&cinfo, buffer, 1);

		for (int i=0; i < row_stride; i++) {
			data[dataHeight][i] = (unsigned char) buffer[0][i];
			temp[totalDataPlace] = (unsigned char) buffer[0][i];
			totalDataPlace++;
		}

		dataHeight++;

		put_scanline_someplace(buffer[0], row_stride);
	}

	printf("P6\n%i %i 255\n", cinfo.output_width, cinfo.output_height);
	printf("Number of colors: %d", cinfo.out_color_components);

	(void) jpeg_finish_decompress(&cinfo);

	printf("P6\n%i %i 255\n", cinfo.output_width, cinfo.output_height);
	printf("Number of colors: %d\n", cinfo.actual_number_of_colors);

	jpeg_destroy_decompress(&cinfo);

	fclose(infile);

	return 0;

}

void filterColor(int *red, int *green, int *blue) {
	//printf("BRed:%i,", *red);
	if (*red + 55 <= 255) {
		*red = *red + 55;
		//printf("MRed:%i,", *red);
	}
}

GLOBAL(int)
write_JPEG_file (char * filename) {

	int quality = 100;
	JSAMPLE * image_buffer;

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	FILE * outfile;
	JSAMPROW row_pointer[1];
	int row_stride;

	// SETUP
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	// OPEN FILE
	if ((outfile = fopen(filename, "wb")) == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		return 0;
	}
	jpeg_stdio_dest(&cinfo, outfile);

	cinfo.image_width = image_width;
	cinfo.image_height = image_height;
	cinfo.input_components = 3;
	cinfo.in_color_space = JCS_RGB;

	jpeg_set_defaults(&cinfo);

	jpeg_set_quality(&cinfo, quality, TRUE);

	jpeg_start_compress(&cinfo, TRUE);

	row_stride = image_width * 3;
	unsigned char rowPrint[row_stride];
	int arrayImageindex = 0;
	printf("About to write to file\n");
	while (cinfo.next_scanline < cinfo.image_height) {

		for (int i = 0; i < row_stride; i = i + 3) {

			int red   = (int) p_arrayImage[arrayImageindex + 0];
			int green = (int) p_arrayImage[arrayImageindex + 1];
			int blue  = (int) p_arrayImage[arrayImageindex + 2];

			rowPrint[i] = p_arrayImage[arrayImageindex];
			rowPrint[i + 1] = p_arrayImage[arrayImageindex + 1];
			rowPrint[i + 2] = p_arrayImage[arrayImageindex + 2];

			arrayImageindex = arrayImageindex + 3;

		}

		row_pointer[0] = (JSAMPROW) &rowPrint;

		(void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}

	jpeg_finish_compress(&cinfo);

	fclose(outfile);

	jpeg_destroy_compress(&cinfo);

	return 0;

}

int main(int argc, char **argv)
{
	read_JPEG_file("/Users/jfreier/Projects/temp/opgl/cat.jpg");

	write_JPEG_file("/Users/jfreier/Projects/temp/opgl/cat2.jpg");

	printf("Image width: %d\n", image_width);
	printf("Image height: %d\n", image_height);

	return 1;

}

