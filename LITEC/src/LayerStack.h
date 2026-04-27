#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include "Layer.h"

#define LAYERSTACK_MAX_LAYERS 32

typedef struct LayerStack {
    Layer* layers[LAYERSTACK_MAX_LAYERS];
    unsigned int count;
    unsigned int layerInsertIndex;
} LayerStack;

/* Elinkaari */
void LayerStack_Init(LayerStack* stack);
void LayerStack_Clear(LayerStack* stack);

/* Lisääminen */
int LayerStack_PushLayer(LayerStack* stack, Layer* layer);
int LayerStack_PushOverlay(LayerStack* stack, Layer* overlay);

/* Poistaminen */
Layer* LayerStack_PopLayer(LayerStack* stack);
Layer* LayerStack_PopOverlay(LayerStack* stack);
int LayerStack_RemoveLayer(LayerStack* stack, Layer* layer);
int LayerStack_RemoveOverlay(LayerStack* stack, Layer* overlay);

/* Apu */
Layer* LayerStack_GetLayer(const LayerStack* stack, unsigned int index);
unsigned int LayerStack_GetCount(const LayerStack* stack);

#endif