#include "Layer.h"
#include "Logger.h"
#include <string.h>

void Layer_DefaultOnAttach(Layer* layer)
{
    if (layer == NULL) return;

    print_info("Layer attached: %s", layer->name);
}

void Layer_DefaultOnDetach(Layer* layer)
{
    if (layer == NULL) return;

    print_info("Layer detached: %s", layer->name);
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
    if (layer == NULL) {
        print_warning("Layer_Init called with NULL layer");
        return;
    }

    memset(layer->name, 0, sizeof(layer->name));

    if (name != NULL) {
        strncpy(layer->name, name, NAME_MAX_LENGTH - 1);
        layer->name[NAME_MAX_LENGTH - 1] = '\0';
    }
    else {
        strncpy(layer->name, "UnnamedLayer", NAME_MAX_LENGTH - 1);
        layer->name[NAME_MAX_LENGTH - 1] = '\0';
    }

    layer->type = type;
    layer->userData = NULL;

    layer->OnAttach = Layer_DefaultOnAttach;
    layer->OnDetach = Layer_DefaultOnDetach;
    layer->OnUpdate = Layer_DefaultOnUpdate;
    layer->OnEvent = Layer_DefaultOnEvent;

    print_info("Layer initialized: %s", layer->name);
}