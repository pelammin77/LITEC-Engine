#include "LayerStack.h"
#include "Logger.h"

static void LayerStack_ShiftRight(LayerStack* stack, unsigned int startIndex)
{
    if (stack == NULL) return;

    if (stack->count >= LAYERSTACK_MAX_LAYERS) {
        return;
    }

    for (unsigned int i = stack->count; i > startIndex; --i) {
        stack->layers[i] = stack->layers[i - 1];
    }
}

static void LayerStack_ShiftLeft(LayerStack* stack, unsigned int startIndex)
{
    if (stack == NULL) return;

    if (stack->count == 0) return;

    for (unsigned int i = startIndex; i < stack->count - 1; ++i) {
        stack->layers[i] = stack->layers[i + 1];
    }

    stack->layers[stack->count - 1] = NULL;
}

void LayerStack_Init(LayerStack* stack)
{
    if (stack == NULL) {
        print_warning("LayerStack_Init called with NULL stack");
        return;
    }

    for (unsigned int i = 0; i < LAYERSTACK_MAX_LAYERS; ++i) {
        stack->layers[i] = NULL;
    }

    stack->count = 0;
    stack->layerInsertIndex = 0;

    print_info("LayerStack initialized");
}

void LayerStack_Clear(LayerStack* stack)
{
    if (stack == NULL) {
        print_warning("LayerStack_Clear called with NULL stack");
        return;
    }

    for (unsigned int i = 0; i < stack->count; ++i) {
        stack->layers[i] = NULL;
    }

    stack->count = 0;
    stack->layerInsertIndex = 0;

    print_info("LayerStack cleared");
}

int LayerStack_PushLayer(LayerStack* stack, Layer* layer)
{
    if (stack == NULL) {
        print_warning("LayerStack_PushLayer called with NULL stack");
        return 0;
    }

    if (layer == NULL) {
        print_warning("LayerStack_PushLayer called with NULL layer");
        return 0;
    }

    if (stack->count >= LAYERSTACK_MAX_LAYERS) {
        print_error("LayerStack is full, cannot push layer: %s", layer->name);
        return 0;
    }

    LayerStack_ShiftRight(stack, stack->layerInsertIndex);
    stack->layers[stack->layerInsertIndex] = layer;

    stack->count++;
    stack->layerInsertIndex++;

    print_info("Layer pushed: %s", layer->name);
    return 1;
}

int LayerStack_PushOverlay(LayerStack* stack, Layer* overlay)
{
    if (stack == NULL) {
        print_warning("LayerStack_PushOverlay called with NULL stack");
        return 0;
    }

    if (overlay == NULL) {
        print_warning("LayerStack_PushOverlay called with NULL overlay");
        return 0;
    }

    if (stack->count >= LAYERSTACK_MAX_LAYERS) {
        print_error("LayerStack is full, cannot push overlay: %s", overlay->name);
        return 0;
    }

    stack->layers[stack->count] = overlay;
    stack->count++;

    print_info("Overlay pushed: %s", overlay->name);
    return 1;
}

Layer* LayerStack_PopLayer(LayerStack* stack)
{
    if (stack == NULL) {
        print_warning("LayerStack_PopLayer called with NULL stack");
        return NULL;
    }

    if (stack->layerInsertIndex == 0) {
        print_warning("No normal layers to pop");
        return NULL;
    }

    unsigned int index = stack->layerInsertIndex - 1;
    Layer* removedLayer = stack->layers[index];

    LayerStack_ShiftLeft(stack, index);
    stack->count--;
    stack->layerInsertIndex--;

    if (removedLayer != NULL) {
        print_info("Layer popped: %s", removedLayer->name);
    }

    return removedLayer;
}

Layer* LayerStack_PopOverlay(LayerStack* stack)
{
    if (stack == NULL) {
        print_warning("LayerStack_PopOverlay called with NULL stack");
        return NULL;
    }

    if (stack->count == stack->layerInsertIndex) {
        print_warning("No overlays to pop");
        return NULL;
    }

    unsigned int index = stack->count - 1;
    Layer* removedOverlay = stack->layers[index];

    stack->layers[index] = NULL;
    stack->count--;

    if (removedOverlay != NULL) {
        print_info("Overlay popped: %s", removedOverlay->name);
    }

    return removedOverlay;
}

int LayerStack_RemoveLayer(LayerStack* stack, Layer* layer)
{
    if (stack == NULL) {
        print_warning("LayerStack_RemoveLayer called with NULL stack");
        return 0;
    }

    if (layer == NULL) {
        print_warning("LayerStack_RemoveLayer called with NULL layer");
        return 0;
    }

    for (unsigned int i = 0; i < stack->layerInsertIndex; ++i) {
        if (stack->layers[i] == layer) {
            LayerStack_ShiftLeft(stack, i);
            stack->count--;
            stack->layerInsertIndex--;

            print_info("Layer removed: %s", layer->name);
            return 1;
        }
    }

    print_warning("Layer not found in normal layers: %s", layer->name);
    return 0;
}

int LayerStack_RemoveOverlay(LayerStack* stack, Layer* overlay)
{
    if (stack == NULL) {
        print_warning("LayerStack_RemoveOverlay called with NULL stack");
        return 0;
    }

    if (overlay == NULL) {
        print_warning("LayerStack_RemoveOverlay called with NULL overlay");
        return 0;
    }

    for (unsigned int i = stack->layerInsertIndex; i < stack->count; ++i) {
        if (stack->layers[i] == overlay) {
            LayerStack_ShiftLeft(stack, i);
            stack->count--;

            print_info("Overlay removed: %s", overlay->name);
            return 1;
        }
    }

    print_warning("Overlay not found: %s", overlay->name);
    return 0;
}

Layer* LayerStack_GetLayer(const LayerStack* stack, unsigned int index)
{
    if (stack == NULL) {
        print_warning("LayerStack_GetLayer called with NULL stack");
        return NULL;
    }

    if (index >= stack->count) {
        print_warning("LayerStack_GetLayer index out of range");
        return NULL;
    }

    return stack->layers[index];
}

unsigned int LayerStack_GetCount(const LayerStack* stack)
{
    if (stack == NULL) {
        print_warning("LayerStack_GetCount called with NULL stack");
        return 0;
    }

    return stack->count;
}