// This file is part of LITEC, a lightweight game engine.
// Copyright (c) 2024-2025, Lightbend, Inc. and the LITEC contributors
// For the full copyright and license information, please view the LICENSE file
// that was distributed with this source code.
//
// GuiLayer.c

#include "GuiLayer.h"
#include "Logger.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>

#include "nuklear.h"


#define GUI_PADDING            6.0f
#define GUI_TOOLBAR_HEIGHT    40.0f
#define GUI_SCENE_WIDTH      260.0f
#define GUI_INSPECTOR_WIDTH  300.0f
#define GUI_CONSOLE_HEIGHT   180.0f


static int s_selectedEntity = 0;
static int s_showGrid = 1;
static int s_showStats = 1;

static float s_positionX = 0.0f;
static float s_positionY = 0.0f;
static float s_scaleX = 1.0f;
static float s_scaleY = 1.0f;
static float s_rotation = 0.0f;


static void GuiLayer_OnAttach(Layer* layer)
{
    if (layer == NULL)
    {
        return;
    }

    GuiLayer* guiLayer = (GuiLayer*)layer;

    if (guiLayer->window == NULL)
    {
        print_error("GuiLayer attach failed: GLFWwindow is NULL");
        return;
    }

    if (!NuklearBackend_Init(&guiLayer->backend, guiLayer->window))
    {
        print_error("GuiLayer attach failed: NuklearBackend initialization failed");
        return;
    }

    print_info("GuiLayer attached");
}


static void GuiLayer_OnDetach(Layer* layer)
{
    if (layer == NULL)
    {
        return;
    }

    GuiLayer* guiLayer = (GuiLayer*)layer;

    NuklearBackend_Shutdown(&guiLayer->backend);

    print_info("GuiLayer detached");
}


static const char* GuiLayer_GetSelectedEntityName(void)
{
    switch (s_selectedEntity)
    {
    case 0: return "Main Camera";
    case 1: return "Player";
    case 2: return "Enemy";
    case 3: return "Light";
    case 4: return "Tilemap";
    case 5: return "UI Root";
    default: return "Unknown";
    }
}


static void GuiLayer_DrawToolbar(struct nk_context* ctx, float x, float y, float w, float h)
{
    nk_flags flags =
        NK_WINDOW_BORDER |
        NK_WINDOW_NO_SCROLLBAR;

    if (nk_begin(ctx, "Toolbar", nk_rect(x, y, w, h), flags))
    {
        nk_layout_row_dynamic(ctx, 28, 8);

        if (nk_button_label(ctx, "New"))
        {
            print_info("Toolbar: New clicked");
        }

        if (nk_button_label(ctx, "Open"))
        {
            print_info("Toolbar: Open clicked");
        }

        if (nk_button_label(ctx, "Save"))
        {
            print_info("Toolbar: Save clicked");
        }

        if (nk_button_label(ctx, "Play"))
        {
            print_info("Toolbar: Play clicked");
        }

        if (nk_button_label(ctx, "Pause"))
        {
            print_info("Toolbar: Pause clicked");
        }

        if (nk_button_label(ctx, "Stop"))
        {
            print_info("Toolbar: Stop clicked");
        }

        nk_checkbox_label(ctx, "Grid", &s_showGrid);
        nk_checkbox_label(ctx, "Stats", &s_showStats);
    }

    nk_end(ctx);
}


static void GuiLayer_DrawSceneHierarchy(struct nk_context* ctx, float x, float y, float w, float h)
{
    nk_flags flags =
        NK_WINDOW_BORDER |
        NK_WINDOW_TITLE |
        NK_WINDOW_NO_SCROLLBAR;

    if (nk_begin(ctx, "Scene Hierarchy", nk_rect(x, y, w, h), flags))
    {
        nk_layout_row_dynamic(ctx, 24, 1);
        nk_label(ctx, "Current Scene: SandboxScene", NK_TEXT_LEFT);

        nk_layout_row_dynamic(ctx, 8, 1);
        nk_spacing(ctx, 1);

        float groupHeight = h - 80.0f;
        if (groupHeight < 60.0f)
        {
            groupHeight = 60.0f;
        }

        nk_layout_row_dynamic(ctx, groupHeight, 1);

        if (nk_group_begin(ctx, "SceneItems", NK_WINDOW_BORDER))
        {
            nk_layout_row_dynamic(ctx, 24, 1);

            if (nk_button_label(ctx, "Main Camera"))
            {
                s_selectedEntity = 0;
            }

            if (nk_button_label(ctx, "Player"))
            {
                s_selectedEntity = 1;
            }

            if (nk_button_label(ctx, "Enemy"))
            {
                s_selectedEntity = 2;
            }

            if (nk_button_label(ctx, "Light"))
            {
                s_selectedEntity = 3;
            }

            if (nk_button_label(ctx, "Tilemap"))
            {
                s_selectedEntity = 4;
            }

            if (nk_button_label(ctx, "UI Root"))
            {
                s_selectedEntity = 5;
            }

            nk_group_end(ctx);
        }
    }

    nk_end(ctx);
}


static void GuiLayer_DrawViewport(struct nk_context* ctx, float x, float y, float w, float h)
{
    nk_flags flags =
        NK_WINDOW_BORDER |
        NK_WINDOW_TITLE |
        NK_WINDOW_NO_SCROLLBAR;

    if (nk_begin(ctx, "Game / Scene Viewport", nk_rect(x, y, w, h), flags))
    {
        nk_layout_row_dynamic(ctx, 24, 1);
        nk_label(ctx, "Scene render target will be drawn here later.", NK_TEXT_CENTERED);

        nk_layout_row_dynamic(ctx, 24, 2);
        nk_label(ctx, "Mode:", NK_TEXT_LEFT);
        nk_label(ctx, "Editor", NK_TEXT_LEFT);

        nk_label(ctx, "Grid:", NK_TEXT_LEFT);
        nk_label(ctx, s_showGrid ? "On" : "Off", NK_TEXT_LEFT);

        nk_label(ctx, "Stats:", NK_TEXT_LEFT);
        nk_label(ctx, s_showStats ? "On" : "Off", NK_TEXT_LEFT);

        float viewportAreaHeight = h - 135.0f;
        if (viewportAreaHeight < 80.0f)
        {
            viewportAreaHeight = 80.0f;
        }

        nk_layout_row_dynamic(ctx, viewportAreaHeight, 1);

        if (nk_group_begin(ctx, "ViewportArea", NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))
        {
            nk_layout_row_dynamic(ctx, 28, 1);
            nk_spacing(ctx, 1);
            nk_label(ctx, "[ Rendered scene will appear here ]", NK_TEXT_CENTERED);
            nk_spacing(ctx, 1);

            nk_group_end(ctx);
        }
    }

    nk_end(ctx);
}


static void GuiLayer_DrawConsole(struct nk_context* ctx, float x, float y, float w, float h)
{
    nk_flags flags =
        NK_WINDOW_BORDER |
        NK_WINDOW_TITLE |
        NK_WINDOW_NO_SCROLLBAR;

    if (nk_begin(ctx, "Console", nk_rect(x, y, w, h), flags))
    {
        float consoleLogHeight = h - 70.0f;
        if (consoleLogHeight < 60.0f)
        {
            consoleLogHeight = 60.0f;
        }

        nk_layout_row_dynamic(ctx, consoleLogHeight, 1);

        if (nk_group_begin(ctx, "ConsoleLog", NK_WINDOW_BORDER))
        {
            nk_layout_row_dynamic(ctx, 20, 1);

            nk_label(ctx, "[INFO] Litec engine started", NK_TEXT_LEFT);
            nk_label(ctx, "[INFO] GuiLayer attached", NK_TEXT_LEFT);
            nk_label(ctx, "[INFO] Nuklear backend initialized", NK_TEXT_LEFT);
            nk_label(ctx, "[DEBUG] Waiting for renderer integration...", NK_TEXT_LEFT);

            nk_group_end(ctx);
        }

        nk_layout_row_dynamic(ctx, 26, 3);

        if (nk_button_label(ctx, "Clear"))
        {
            print_info("Console: Clear clicked");
        }

        if (nk_button_label(ctx, "Copy"))
        {
            print_info("Console: Copy clicked");
        }

        if (nk_button_label(ctx, "Filter"))
        {
            print_info("Console: Filter clicked");
        }
    }

    nk_end(ctx);
}


static void GuiLayer_DrawInspector(struct nk_context* ctx, float x, float y, float w, float h)
{
    nk_flags flags =
        NK_WINDOW_BORDER |
        NK_WINDOW_TITLE |
        NK_WINDOW_NO_SCROLLBAR;

    if (nk_begin(ctx, "Inspector", nk_rect(x, y, w, h), flags))
    {
        nk_layout_row_dynamic(ctx, 22, 1);
        nk_label(ctx, "Selected Entity:", NK_TEXT_LEFT);
        nk_label(ctx, GuiLayer_GetSelectedEntityName(), NK_TEXT_LEFT);

        nk_layout_row_dynamic(ctx, 8, 1);
        nk_spacing(ctx, 1);

        nk_layout_row_dynamic(ctx, 22, 1);
        nk_label(ctx, "Transform", NK_TEXT_LEFT);

        nk_layout_row_dynamic(ctx, 24, 1);
        nk_property_float(ctx, "#Pos X:", -10000.0f, &s_positionX, 10000.0f, 0.1f, 0.1f);
        nk_property_float(ctx, "#Pos Y:", -10000.0f, &s_positionY, 10000.0f, 0.1f, 0.1f);
        nk_property_float(ctx, "#Scale X:", 0.0f, &s_scaleX, 1000.0f, 0.1f, 0.1f);
        nk_property_float(ctx, "#Scale Y:", 0.0f, &s_scaleY, 1000.0f, 0.1f, 0.1f);
        nk_property_float(ctx, "#Rotation:", -360.0f, &s_rotation, 360.0f, 1.0f, 1.0f);

        nk_layout_row_dynamic(ctx, 8, 1);
        nk_spacing(ctx, 1);

        nk_layout_row_dynamic(ctx, 24, 1);
        nk_checkbox_label(ctx, "Show Grid", &s_showGrid);
        nk_checkbox_label(ctx, "Show Stats", &s_showStats);

        nk_layout_row_dynamic(ctx, 28, 2);

        if (nk_button_label(ctx, "Apply"))
        {
            print_info("Inspector: Apply clicked");
        }

        if (nk_button_label(ctx, "Reset"))
        {
            s_positionX = 0.0f;
            s_positionY = 0.0f;
            s_scaleX = 1.0f;
            s_scaleY = 1.0f;
            s_rotation = 0.0f;

            print_info("Inspector: Transform reset");
        }
    }

    nk_end(ctx);
}


static void GuiLayer_DrawEditorLayout(struct nk_context* ctx, int windowWidth, int windowHeight)
{
    if (ctx == NULL)
    {
        return;
    }

    float pad = GUI_PADDING;
    float toolbarH = GUI_TOOLBAR_HEIGHT;
    float sceneW = GUI_SCENE_WIDTH;
    float inspectorW = GUI_INSPECTOR_WIDTH;
    float consoleH = GUI_CONSOLE_HEIGHT;

    float fullW = (float)windowWidth;
    float fullH = (float)windowHeight;

    if (fullW < 800.0f)
    {
        fullW = 800.0f;
    }

    if (fullH < 500.0f)
    {
        fullH = 500.0f;
    }

    float toolbarX = pad;
    float toolbarY = pad;
    float toolbarW = fullW - (pad * 2.0f);

    float topY = toolbarY + toolbarH + pad;

    float sceneX = pad;
    float sceneY = topY;
    float sceneH = fullH - topY - consoleH - (pad * 2.0f);

    float viewportX = sceneX + sceneW + pad;
    float viewportY = topY;
    float viewportW = fullW - sceneW - (pad * 3.0f);
    float viewportH = sceneH;

    float consoleX = pad;
    float consoleY = fullH - consoleH - pad;
    float consoleW = fullW - inspectorW - (pad * 3.0f);

    float inspectorX = fullW - inspectorW - pad;
    float inspectorY = consoleY;
    float inspectorH = consoleH;

    if (sceneH < 120.0f)
    {
        sceneH = 120.0f;
        viewportH = sceneH;
    }

    if (viewportW < 220.0f)
    {
        viewportW = 220.0f;
    }

    GuiLayer_DrawToolbar(ctx, toolbarX, toolbarY, toolbarW, toolbarH);
    GuiLayer_DrawSceneHierarchy(ctx, sceneX, sceneY, sceneW, sceneH);
    GuiLayer_DrawViewport(ctx, viewportX, viewportY, viewportW, viewportH);
    GuiLayer_DrawConsole(ctx, consoleX, consoleY, consoleW, consoleH);
    GuiLayer_DrawInspector(ctx, inspectorX, inspectorY, inspectorW, inspectorH);
}


static void GuiLayer_OnUpdate(Layer* layer, float deltaTime)
{
    (void)deltaTime;

    if (layer == NULL)
    {
        return;
    }

    static int printed = 0;

    if (!printed)
    {
        print_info("GuiLayer update running");
        printed = 1;
    }

    GuiLayer* guiLayer = (GuiLayer*)layer;

    if (!guiLayer->backend.initialized)
    {
        return;
    }

    int windowWidth = 1280;
    int windowHeight = 720;

    if (guiLayer->window != NULL)
    {
        glfwGetWindowSize(guiLayer->window, &windowWidth, &windowHeight);
    }

    NuklearBackend_BeginFrame(&guiLayer->backend);

    struct nk_context* ctx = NuklearBackend_GetContext(&guiLayer->backend);

    if (ctx != NULL)
    {
        GuiLayer_DrawEditorLayout(ctx, windowWidth, windowHeight);
    }

    NuklearBackend_EndFrame(&guiLayer->backend);
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

        /*
            Tätä ei kannata vielä ottaa pysyvästi käyttöön ennen kuin
            Nuklearin input-logiikka on mukana.

            Myöhemmin:
                - jos GUI haluaa hiiren, event->handled = 1
                - jos ei halua, event kulkee seuraaville layereille
        */

        // event->handled = 1;
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


Layer* GuiLayer_Create(GLFWwindow* window)
{
    GuiLayer* guiLayer = (GuiLayer*)malloc(sizeof(GuiLayer));

    if (guiLayer == NULL)
    {
        print_error("Failed to create GuiLayer");
        return NULL;
    }

    Layer* layer = &guiLayer->base;

    guiLayer->window = window;

    guiLayer->backend.window = NULL;
    guiLayer->backend.ctx = NULL;
    guiLayer->backend.initialized = 0;

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

    GuiLayer* guiLayer = (GuiLayer*)layer;

    if (layer->OnDetach != NULL)
    {
        layer->OnDetach(layer);
    }

    print_info("GuiLayer destroyed");

    free(guiLayer);
}