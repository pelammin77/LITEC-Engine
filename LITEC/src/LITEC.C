#include <stdio.h>
#include "LITEC.h"

static int running = 1;

void LITEC_Init() {
    printf("LITEC engine is starting. Welcome!\n");
}

int LITEC_Running() {
    return running;
}

void LITEC_HandleInput() {
    // Tähän tulee myöhemmin syötteiden käsittelykoodi.
}

void LITEC_Update() {
    // Tähän tulee myöhemmin pelin päivityskoodi.
}

void LITEC_Render() {
    // Tähän tulee myöhemmin piirtokoodi.
}

void LITEC_Shutdown() {
    printf("LITEC engine is shutting down. Goodbye!\n");
    running = 0;
}
