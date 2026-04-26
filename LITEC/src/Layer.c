#include "Layer.h"
#include <string.h>
#include <stdio.h>

/* Jos sinulla on oma loggeri, käytä sitä mieluummin */
void Layer_DefaultOnAttach(Layer* layer)
{
    if (layer == NULL) return;

    printf("Layer attached: %s\n", layer->name);
}

void Layer_DefaultOnDetach(Layer* layer)
{
    if (layer == NULL) return;

    printf("Layer detached: %s\n", layer->name);
}

void Layer_DefaultOnUpdate(Layer* layer, float deltaTime)
{
    if (layer == NULL) return;

    /* Oletuksena ei tehdä mitään */
    (void)deltaTime;
}

void Layer_DefaultOnEvent(Layer* layer, Event* event)
{
    if (layer == NULL || event == NULL) return;

    /* Oletuksena ei tehdä mitään */
    (void)event;
}

void Layer_Init(Layer* layer, const char* name, LayerType type)
{
    if (layer == NULL) return;

    memset(layer->name, 0, sizeof(layer->name));

    if (name != NULL) {
        strncpy(layer->name, name, NAME_MAX_LENGTH - 1);
        layer->name[NAME_MAX_LENGTH - 1] = '\0';
    }

    layer->type = type;
    layer->userData = NULL;

    layer->OnAttach = Layer_DefaultOnAttach;
    layer->OnDetach = Layer_DefaultOnDetach;
    layer->OnUpdate = Layer_DefaultOnUpdate;
    layer->OnEvent = Layer_DefaultOnEvent;
}