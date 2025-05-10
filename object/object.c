#include <stdlib.h>
#include "snekobject.h"

snek_object_t *new_snek_array(size_t size) {
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  //calloc zero in all bytes allocated to the array
  snek_object_t **elem = calloc(size, sizeof(snek_object_t *));
  if (elem == NULL) {
    free(obj);
    return NULL;  
  }

  obj->kind = ARRAY;
  obj->data.v_array = (snek_array_t){.size = size, .elements = elem};
  return obj;
}

snek_object_t *new_snek_vector3(
    snek_object_t *x, snek_object_t *y, snek_object_t *z
) {
  if (x == NULL || y == NULL || z == NULL) {
    return NULL;
  }
  
  snek_object_t *obj = malloc(sizeof(snek_object_t));
  if (obj == NULL){
    return NULL;
  }

  obj->kind = VECTOR3;
  snek_vector_t vector = {x: x, y: y, z: z};
  obj->data.v_vector3 = vector;
  return obj;
}

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
	obj->data.v_string = new_str;:w
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
