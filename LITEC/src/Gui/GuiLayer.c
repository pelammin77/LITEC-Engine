// GuiLayer.c

#include "GuiLayer.h"
#include "Logger.h"

#include <stdlib.h>


static void GuiLayer_OnAttach(Layer* layer)
{
    print_info("GuiLayer attached");
}


static void GuiLayer_OnDetach(Layer* layer)
{
    print_info("GuiLayer detached");
}


static void GuiLayer_OnUpdate(Layer* layer, float deltaTime)
{
    /*
        Tänne tulee myöhemmin GUI:n piirtäminen.

        Esimerkiksi:
        - Nuklear new frame
        - GUI-elementtien rakentaminen
        - Nuklear render
    */

    (void)layer;
    (void)deltaTime;
}


static void GuiLayer_OnEvent(Layer* layer, Event* event)
{
    (void)layer;

    if (event == NULL)
    {
        return;
    }

    if (event->type == EVENT_MOUSE_MOVED)
    {
        print_info("GuiLayer received mouse moved event");
		event->handled = 1; // Merkitään event käsitellyksi, jotta se ei kulje pidemmälle
    }
    else if (event->type == EVENT_KEY_PRESSED)
    {
        print_info("GuiLayer received key pressed event");
    }
    else
    {
        print_info("GuiLayer received event");
    }
}

Layer* GuiLayer_Create(void)
{
    Layer* layer = (Layer*)malloc(sizeof(Layer));

    if (layer == NULL)
    {
        print_error("Failed to create GuiLayer");
        return NULL;
    }

    Layer_Init(layer, "GuiLayer", LAYER_TYPE_OVERLAY);

    layer->OnAttach = GuiLayer_OnAttach;
    layer->OnDetach = GuiLayer_OnDetach;
    layer->OnUpdate = GuiLayer_OnUpdate;
    layer->OnEvent = GuiLayer_OnEvent;

    print_info("GuiLayer created");

    return layer;
}


void GuiLayer_Destroy(Layer* layer)
{
    if (layer == NULL)
    {
        return;
    }

    if (layer->OnDetach != NULL)
    {
        layer->OnDetach(layer);
    }

    print_info("GuiLayer destroyed");

    free(layer);
}