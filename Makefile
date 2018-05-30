CC=gcc
FILES=src/imagizer.c src/imageColor.c src/imageDebug.c src/imageFilters.c src/imageProcessor.c src/recognitionEyes.c
OUT_EXE=run
REVISION=c99

build:
	$(CC) -std=$(REVISION) -ljpeg -o $(OUT_EXE) $(FILES)

debug:
	$(CC) -std=$(REVISION) -ljpeg -o $(OUT_EXE) $(FILES) -DDEBUG

clean:
	rm -f *.o run

rebuild: clean build
