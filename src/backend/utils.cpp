#include "utils.h"

#include "define.h"
#include <cstdlib>
#include <time.h>

static b8 seedGenerated = false;
float randomFloat() {
	if(!seedGenerated) { 
		srand(time(0));
		seedGenerated = true;
	}
	return (float)(rand()) / (float)(RAND_MAX);
}
