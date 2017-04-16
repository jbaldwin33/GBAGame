#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAG(x, y) abs(sqrt(((x)*(x)) + ((y)*(y))))

typedef struct Vector {
	int x;
	int y;
	int mag;
} vector;

typedef struct Agent {
	int xpos;
	int ypos;
	int direc;
	int maxSpeed;
	int maxRotation;
} agent;










void normalize(vector* vec) {
	vec->x = vec->x / vec->mag;
	vec->y = vec->y / vec->mag;
	return vec;
}

void addVectors(vector* vec1, vector* vec2) {
	vector newVec = malloc(sizeof(struct Vector));
	newVec->x = vec1->x + vec2->x;
	newVec->y = vec1->y + vec2->y;
}

void vecMultScalar(int x, vector* vec) {
	vec->x = vec->x * x;
	vec->y = vec->y * y;
}

int getNewOrientation(int direction, vector* velocity) {
	if (velocity->mag != 0) {
		return atan(velocity->x / velocity->y);
	} else {
		return direction;
	}
}
