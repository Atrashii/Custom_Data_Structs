#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool resize(int **ptr, size_t size) {
	int *tmp = *ptr;

	*ptr = (int*)realloc(*ptr, 2 * size * sizeof(int));

	if(*ptr == NULL) {
		*ptr = tmp;
		fprintf(stderr, "Failed to allocate memory\n");
		return false;
	}
	printf("Resizing ...\n");
	return true;
}

int main(void) {
	int input;
	size_t size = 5;
	int counter = 0;

	int *ptr = (int*)malloc(size*sizeof(int));

	if(ptr == NULL) {
		fprintf(stderr, "Initial memory allocation failed!\n");
		return -1;
	}
	
	while(true) {
		printf("Enter a number: \n");
		scanf("%d", &input);
		if(input == -1000) {
			break;
		}
		ptr[counter] = input;
		counter++;
		if(counter == size) {
			size *= 2;
			if(!resize(&ptr, size)) {
				fprintf(stderr, "could not resize the array");
				free(ptr);
				exit(-1);
			}
		}
	}
	for(int i = 0; i < counter; i++) {
		printf("%d ", ptr[i]);
	}
	printf("\n");

	free(ptr);
	return 0;
}
