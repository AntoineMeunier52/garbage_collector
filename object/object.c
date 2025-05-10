#include <stdlib.h>
#include "snekobject.h"

snek_object_t *new_snek_string(char *value) {
	snek_object_t *obj = malloc(sizeof(snek_object_t));
	if (obj == NULL) {
		return NULL;
	}

	int len_str = strlen(value) + 1;
	char *new_str = malloc(sizeof(char) * len_str);
	if (new_str == NULL) {
		free(obj);
		return NULL;
	}

	strcpy(new_str, value);

	obj->kind = STRING;
	obj->data.v_string = new_str;
	return obj;
}

snek_object_t *new_snek_float(float value) {
	snek_object_t *obj = malloc(sizeof(snek_object_t));
	if (obj == NULL) {
		return NULL;
	}

	obj->kind = FLOAT;
	obj->data.v_float = value;
	return obj;
}

snek_object_t *new_snek_integer(int value) {
	snek_object_t *obj = malloc(sizeof(snek_object_t));
	if (obj == NULL) {
		return NULL:
	}

	obj->kind = INTEGER;
	obj-data.v_int = value;
	return obj;
}
