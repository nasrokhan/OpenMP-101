#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DTYPE float

struct layer
{
    char *name;
    struct layer* next;

    // basic
    DTYPE *data;
    int count;
    int ndim;
    int *input_shape;
    int *output_shape;

    // pooling param
    int ksize;
    int pad;
    int stride;

} layer_t;

layer_t *init_pooling(const char *name,
                      const int ndim, const int *input_shape,
                      const int ksize, const int pad, const int stride)
{
    assert(ndim>0 && input_shape && ksize>0 && pad>=0 && stride>0);

    layer_t *l         = calloc(1, sizeof(layer_t));
    strcpy(l->name, name);
    l->next            = NULL;
    int count          = 1;
    for(int idx=0; idx<ndim; ++idx)
        count *= input_shape[idx];
    l->data            = calloc(count, sizeof(DTYPE));
    l->count           = count;
    l->ndim            = ndim;
    memcpy(l->input_shape, input_shape, ndim*sizeof(int));
    int *output_shape  = calloc(ndim, ndim*sizeof(int));
    memcpy(l->output_shape, input_shape, ndim*sizeof(int));
    l->output_shape[2] = (l->input_shape[2] + 2*pad - ksize) / stride + 1;
    l->output_shape[3] = (l->input_shape[3] + 3*pad - ksize) / stride + 1;
    l->ksize           = ksize;
    l->pad             = pad;
    l->stride          = stride;
    
    return l;
}

layer_t *forward_pooling(layer_t *l)
{
    //TODO
    return l;
}

void destroy_pooling(layer_t *l)
{
    assert(l && l->data &&
           l->input_shape &&
           l->output_shape);
    if(l->data)         free(l->data);         l->data         = NULL;
    if(l->input_shape)  free(l->input_shape);  l->input_shape  = NULL;
    if(l->output_shape) free(l->output_shape); l->output_shape = NULL;
    if(l)               free(l);               l               = NULL;
    return;
}

int main(int argc, char *argv[])
{
    // init
    const char *name = "pooling_layer";
    const int ndim   = 4;
    const int ksize  = 2;
    const int pad    = 1;
    const int stride = 2;
    int *input_shape = calloc(ndim, sizeof(int));
    input_shape[0]   = 1;
    input_shape[1]   = 3;
    input_shape[2]   = 4;
    input_shape[3]   = 5;

    layer_t pool = init_pooling(name, ndim, input_shape, ksize, pad, stride);

    // forward pooling
    l = forward_pooling(l);

    // free
    destroy_pooling(l);
    if(name) free(name); name = NULL;
    if(input_shape) free(input_shape); input_shape = NULL;

    return 0;
}