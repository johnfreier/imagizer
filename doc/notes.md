Imagizer
===============================================================================
This is an attempt to create some sort of image reconstruction porject.  It
started off as a way to identify if a JPEG image is a picture of a cat.  I have
 updated the project to attempt to find the eyes of a cat and place a mustache
on the cat.

In the future it might be nice to create this as a service online and let
others upload their images and see if the program can identify the eyes and
place the mustace in the correct location.

Files
-------------------------------------------------------------------------------


Refrence Links
-------------------------------------------------------------------------------

https://stackoverflow.com/questions/39008893/read-in-jpeg-resize-it-and-save-it-to-disk

https://stackoverflow.com/questions/8148443/change-specific-pixel-in-jpeglib

https://github.com/LuaDist/libjpeg/blob/master/example.c

http://dlib.net/dlib/external/libjpeg/jdsample.cpp.html

Example of reading metadata
https://github.com/cloudflare/jpegtran/blob/master/djpeg.c

Document about JPEGlib
https://www4.cs.fau.de/Services/Doc/graphics/doc/jpeg/libjpeg.html

Read JPEG metadata information.
-------------------------------------------------------------------------------
I wanted to read metadata information if the JPEG had any.

To read marker data, you have to inject the function call, kind of like a
lambda.  I had to place this before the 'jpeg_read_header' function.

	jpeg_set_marker_processor(&cinfo, JPEG_COM, **FUNCION**);

This is the function to read the data.
**FUNCTION**
	boolean **FUNCTION** (j_decompress_ptr cinfo) {
		...
	}

// Example I used could be updated but ran out of time.
boolean print_text_marker (j_decompress_ptr cinfo) {
	struct jpeg_source_mgr * datasrc = cinfo->src;
	datasrc->bytes_in_buffer--;
	printf("TEst\n\n");
	unsigned int t = GETJOCTET(*datasrc->next_input_byte++);
	printf("Char: \\%03o", t);
	return TRUE;
}

Here is an full example I used to understand it.
	jpeg_set_marker_processor(&cinfo, JPEG_COM, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0, print_text_marker);
	jpeg_set_marker_processor(&cinfo, JPEG_APP0+1, print_text_marker);
	//-jpeg_set_marker_processor(&cinfo, JPEG_APP0+2, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+3, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+4, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+5, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+6, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+7, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+8, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+9, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+10, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+11, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+12, print_text_marker);
	//-jpeg_set_marker_processor(&cinfo, JPEG_APP0+13, print_text_marker);
	//jpeg_set_marker_processor(&cinfo, JPEG_APP0+14, print_text_marker);


Example of reading data.
https://github.com/cloudflare/jpegtran/blob/master/djpeg.c

Writing the META data
-------------------------------------------------------------------------------
I'm not sure if I got this working or not, could not see if from other
applications.

Here was a simple compiled sample code I put together.

	unsigned char t[4] = "JOHN";
	const unsigned char *tp = t;
	cinfo.write_Adobe_marker = 1;
	jpeg_write_marker(&cinfo, JPEG_APP0 + 14, tp, 4);