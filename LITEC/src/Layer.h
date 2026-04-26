// Layer.h 

#ifndef LAYER_H
#define LAYER_H

#include "Events/Event.h"   

#define NAME_MAX_LENGTH 20

typedef enum LayerType {
    LAYER_TYPE_NORMAL = 0,
    LAYER_TYPE_OVERLAY
} LayerType;

/* Forward declaration ei ole pakollinen jos Event.h on mukana,
   mutta tämäkin tapa olisi mahdollinen:
   typedef struct Event Event;
*/

typedef struct Layer Layer;

typedef void (*LayerOnAttachFn)(Layer* layer);
typedef void (*LayerOnDetachFn)(Layer* layer);
typedef void (*LayerOnUpdateFn)(Layer* layer, float deltaTime);
typedef void (*LayerOnEventFn)(Layer* layer, Event* event);

typedef struct Layer {
    char name[NAME_MAX_LENGTH];
    LayerType type;

    void* userData;

    LayerOnAttachFn OnAttach;
    LayerOnDetachFn OnDetach;
    LayerOnUpdateFn OnUpdate;
    LayerOnEventFn OnEvent;
} Layer;


/* Oletusfunktiot */
void Layer_DefaultOnAttach(Layer* layer);
void Layer_DefaultOnDetach(Layer* layer);
void Layer_DefaultOnUpdate(Layer* layer, float deltaTime);
void Layer_DefaultOnEvent(Layer* layer, Event* event);

/* Alustus */
void Layer_Init(Layer* layer, const char* name, LayerType type);

#endif