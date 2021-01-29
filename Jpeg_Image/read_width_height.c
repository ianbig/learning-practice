#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct {
    unsigned char *md5;
    int width;
    int height;
    unsigned char *content;
    unsigned long file_size;
} JPEG_INFO_S;


// load entire jpeg into buf

// 0: normal
// -1: not valid file format
// -2: not normal situation
int get_jpeg_size(unsigned char *data, unsigned int data_size, int *width, int *height) {
	int i = 0;
	int block_size = 0;

	if(data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF && data[3] == 0xE0) {
		i += 4;
		if(data[i + 2] == 'J' && data[i + 3] == 'F' && data[i + 4] == 'I' && data[i + 5] == 'F' && data[i + 6] == 0x00) {
			block_size = 256 * data[i] + data[i + 1];
			i += block_size;
			while(i < data_size) {
				if(data[i] != 0xFF) {
					return -1;
				} 
				if(data[i + 1] == 0xC0) {
					*height = 256 * data[i + 5] + data[ i + 6];
					*width = 256 * data[i + 7] + data[i + 8];
					return 0;
				} else {
					block_size = 256 * data[i + 2] + data[i + 3];
					i += block_size + 2; //skip block header
				}
			}

		} else {
			fprintf(stderr, "Invalid JFIF\n");
			return -1;
		}
	} else {
		fprintf(stderr, "Invalid SOI Header\n");
		return -1;
	}
	return -2;
}

int read_jpeg(const char file_path[], ) {
	FILE *fptr = NULL;
	unsigned char *data_buf = NULL;
	char *hex_buf = NULL;
	struct stat file_buf;
	int height = 0, width = 0;

	JPEG_INFO_S ret;

	if((fptr = fopen(file_path, "r")) == NULL) {
		fprintf(stderr, "ERROR: unable to open %s\n", file_path);
		return ret;
	}

	// get file size
	stat(file_path, &file_buf);
	
	data_buf = (unsigned char*)malloc(sizeof(unsigned char) * (file_buf.st_size + 1));
	// hex_buf = (char*)malloc(sizeof(char) * (2 * file_buf.st_size + 1));

	fread(data_buf, sizeof(char), file_buf.st_size, fptr);
	data_buf[file_buf.st_size] = '\0';

	get_jpeg_size(data_buf, file_buf.st_size, &width, &height);
	// fprintf(stderr, "height: %d\nwidth: %d\n", height, width);
	ret.height = height;
	ret.width = width;
	ret.file_size = file_buf.st_size;
}

int main(int argc, char const *argv[])
{
	const char file_path[] = "/home/ian/image/image_9.jpeg";
	read_jpeg(file_path);
	return 0;
}