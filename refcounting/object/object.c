#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "snekobject.h"

void refcount_dec(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }

  obj->refcount--;
  if (obj->refcount == 0) {
    refcount_free(obj);
  }
  return;
}

void refcount_free(snek_object_t *obj) {
  switch (obj->kind) {
    case INTEGER:
    case FLOAT:
      break;
    case STRING:
      free(obj->data.v_string);
      break;
    default:
      exit(1);
  }

  free(obj);
}

void refcount_inc(snek_object_t *obj) {
  if (obj == NULL) {
    return;
  }

  obj->refcount++;
  return;
}

snek_object_t *_new_snek_object() {
  snek_object_t *obj = calloc(1, sizeof(snek_object_t));
  if (obj == NULL) {
    return NULL;
  }

  obj->refcount = 1;
  return obj;
}

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
  if (a == NULL || b == NULL) {
    return NULL;
  }
  switch (a->kind) {
    case INTEGER:
      if (b->kind == INTEGER) {
        return new_snek_integer(a->data.v_int + b->data.v_int);
      } else if (b->kind == FLOAT) {
        return new_snek_float(a->data.v_int + b->data.v_float);
      } else {
        return NULL;
      }
      
    case FLOAT:
      if (b->kind == INTEGER) {
        return new_snek_float(a->data.v_float + b->data.v_int);
      } else if (b->kind == FLOAT) {
        return new_snek_float(a->data.v_float + b->data.v_float);
      } else {
        return NULL;
      }
    case STRING:
      if (b->kind != STRING) {
        return NULL;
      }

      int len = strlen(a->data.v_string) + strlen(b->data.v_string) + 1;
      char *tmp = calloc(len, sizeof(char));
      strcat(tmp, a->data.v_string);
      strcat(tmp, b->data.v_string);
      snek_object_t *new_str = new_snek_string(tmp);
      free(tmp);
      return new_str;
    case VECTOR3:
      if (b->kind != VECTOR3) {
        return NULL;
      }

      return new_snek_vector3(
        snek_add(a->data.v_vector3.x, b->data.v_vector3.x),
        snek_add(a->data.v_vector3.y, b->data.v_vector3.y),
        snek_add(a->data.v_vector3.z, b->data.v_vector3.z)
      );
    case ARRAY:
      if (b->kind != ARRAY) {
        return NULL;
      }

      snek_object_t *array = new_snek_array(a->data.v_array.size + b->data.v_array.size);
      int i = 0;
      int j = 0;
      while (i < a->data.v_array.size) {
        snek_array_set(array, j, snek_array_get(a, i));
        i++;
        j++;
      }
      i = 0;
      while (i < b->data.v_array.size) {
        snek_array_set(array, j, snek_array_get(b, i));
        i++;
        j++;
      }
      return array;
    default:
      return NULL;
  }
}

int snek_length(snek_object_t *obj) {
  if (obj == NULL) {
    return -1;
  }

  switch (obj->kind) {
    case INTEGER:
    case FLOAT:
      return 1;
    case STRING:
      return strlen(obj->data.v_string);
    case VECTOR3:
      return 3;
    case ARRAY:
      return obj->data.v_array.size;
    default:
      return -1;
  }
}

bool snek_array_set(snek_object_t *obj, size_t index, snek_object_t *value) {
  if (obj == NULL || value == NULL) {
    return NULL;
  }

  if (obj->kind != ARRAY) {
    return false;
  }

  if (index < 0 || index >= obj->data.v_array.size) {
    return false;
  }

  obj->data.v_array.elements[index] = value;
  return true;
}

snek_object_t *snek_array_get(snek_object_t *obj, size_t index) {
  if (obj == NULL) {
    return NULL;
  }

  if (obj->kind != ARRAY) {
    return NULL;
  }

  if (index < 0 || index >= obj->data.v_array.size) {
    return false;
  }

  return obj->data.v_array.elements[index];
}

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
