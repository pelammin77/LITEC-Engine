// Layer.h 

#ifndef LAYER_H
#define LAYER_H

#define NAME_MAX_LENGTH 20  

typedef enum LayerType {
    LAYER_TYPE_NORMAL = 0,
    LAYER_TYPE_OVERLAY

} LayerType;

typedef struct { 
    char name[NAME_MAX_LENGTH];
    LayerType type;
} Layer;


#endif
