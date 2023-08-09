#include <stdlib.h>
#include <string.h>
#include "shape.h"

Shape *shape_new(Vec4 *normals, Vec4 *vertices, int nvertices, int *indices, int nindices) {
    Shape *self = malloc(sizeof *self);
    self->nvertices = nvertices / (int) sizeof *vertices * 8 * (int) sizeof *self->vertices;
    self->vertices = malloc(self->nvertices);
    for (int i = 0, j = 0; i < nvertices / (int) sizeof *vertices; i++, j += 8) {
        self->vertices[j] = vertices[i].x;
        self->vertices[j + 1] = vertices[i].y;
        self->vertices[j + 2] = vertices[i].z;
        self->vertices[j + 3] = vertices[i].w;
        self->vertices[j + 4] = normals[i].x;
        self->vertices[j + 5] = normals[i].y;
        self->vertices[j + 6] = normals[i].z;
        self->vertices[j + 7] = normals[i].w;
    }
    self->nindices = nindices;
    self->indices = malloc(nindices);
    memcpy(self->indices, indices, nindices);
    return self;
}

void shape_delete(Shape *self) {
    free(self->vertices);
    free(self->indices);
    free(self);
}

Shape *shape_cube(float edge) {
    Vec4 normals[] = {
            vec4(0, 0, 1),
            vec4(0, 0, 1),
            vec4(0, 0, 1),
            vec4(0, 0, 1),

            vec4(0, 0, -1),
            vec4(0, 0, -1),
            vec4(0, 0, -1),
            vec4(0, 0, -1),

            vec4(0, 1, 0),
            vec4(0, 1, 0),
            vec4(0, 1, 0),
            vec4(0, 1, 0),

            vec4(0, -1, 0),
            vec4(0, -1, 0),
            vec4(0, -1, 0),
            vec4(0, -1, 0),

            vec4(1, 0, 0),
            vec4(1, 0, 0),
            vec4(1, 0, 0),
            vec4(1, 0, 0),

            vec4(-1, 0, 0),
            vec4(-1, 0, 0),
            vec4(-1, 0, 0),
            vec4(-1, 0, 0),
    };
    Vec4 vertices[] = {
            vec4(-edge / 2, -edge / 2, edge / 2),
            vec4(-edge / 2, edge / 2, edge / 2),
            vec4(edge / 2, edge / 2, edge / 2),
            vec4(edge / 2, -edge / 2, edge / 2),

            vec4(-edge / 2, -edge / 2, -edge / 2),
            vec4(-edge / 2, edge / 2, -edge / 2),
            vec4(edge / 2, edge / 2, -edge / 2),
            vec4(edge / 2, -edge / 2, -edge / 2),

            vec4(-edge / 2, edge / 2, edge / 2),
            vec4(-edge / 2, edge / 2, -edge / 2),
            vec4(edge / 2, edge / 2, -edge / 2),
            vec4(edge / 2, edge / 2, edge / 2),

            vec4(-edge / 2, -edge / 2, edge / 2),
            vec4(-edge / 2, -edge / 2, -edge / 2),
            vec4(edge / 2, -edge / 2, -edge / 2),
            vec4(edge / 2, -edge / 2, edge / 2),

            vec4(edge / 2, -edge / 2, -edge / 2),
            vec4(edge / 2, edge / 2, -edge / 2),
            vec4(edge / 2, edge / 2, edge / 2),
            vec4(edge / 2, -edge / 2, edge / 2),

            vec4(-edge / 2, -edge / 2, -edge / 2),
            vec4(-edge / 2, edge / 2, -edge / 2),
            vec4(-edge / 2, edge / 2, edge / 2),
            vec4(-edge / 2, -edge / 2, edge / 2)
    };
    int indices[] = {
            0, 1, 2,
            0, 3, 2,

            4, 5, 6,
            4, 7, 6,

            8, 9, 10,
            8, 11, 10,

            12, 13, 14,
            12, 15, 14,

            16, 17, 18,
            16, 19, 18,

            20, 21, 22,
            20, 23, 22
    };
    return shape_new(normals, vertices, sizeof vertices, indices, sizeof indices);
}
