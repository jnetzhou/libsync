#include <stdio.h>
#include <stdlib.h>
#include "sync.h"

int main(int argc, char *argv[])
{
	char *src_filename = NULL;
	char *dest_filename = NULL;
	char chunk_filename[] = "./chunk_src";
	char delta_filename[] = "./delta_dest";
	int ret = 0, chunk_algo;

	if (argc < 4) {
		fprintf(stderr, "%s SOURCE DEST CHUNK_ALGO(0 = FSP | 1 = CDC | 2 = SBC)\n", argv[0]);
		exit(0);
	}

	src_filename = argv[1];
	dest_filename = argv[2];
	chunk_algo = atoi(argv[3]);

	ret = file_chunk(src_filename, chunk_filename, chunk_algo);
	if (ret == -1) {
		fprintf(stderr, "file chunk failed\n");
		exit(1);
	}

	ret = file_delta(dest_filename, chunk_filename, delta_filename, chunk_algo);
	if (ret == -1) {
		fprintf(stderr, "file delta failed\n");
		exit(0);
	}

	ret = file_sync(src_filename, delta_filename);
	if (ret == -1) {
		fprintf(stderr, "file sync failed\n");
		exit(0);
	}

	return 0;

}
