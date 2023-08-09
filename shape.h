#ifndef QUARKENGINE_SHAPE_H
#define QUARKENGINE_SHAPE_H

#include "vec4.h"

typedef struct {
    float *vertices;
    int nvertices;
    int *indices;
    int nindices;
} Shape;

Shape *shape_new(Vec4 *normals, Vec4 *vertices, int nvertices, int *indices, int nindices);
void shape_delete(Shape *self);
Shape *shape_cube(float edge);

#endif
