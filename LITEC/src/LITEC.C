#include <stdio.h>
#include "LITEC.h"
#include "Logger.h"

static int running = 1;

void LITEC_Init() {
    init_logger();
    print_info("LITEC engine is starting. Welcome!\n");
}

int LITEC_Running() {
    return running;
}

void LITEC_HandleInput() {
    // T�h�n tulee my�hemmin sy�tteiden k�sittelykoodi.
}

void LITEC_Update() {
    // T�h�n tulee my�hemmin pelin p�ivityskoodi.
}

void LITEC_Render() {
    // T�h�n tulee my�hemmin piirtokoodi.
}

void LITEC_Shutdown() {
    print_info("LITEC engine is shutting down. Goodbye!\n");
    running = 0;
    close_logger();
}
