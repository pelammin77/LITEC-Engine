#include <LITEC.h>

int main() {
    // Alusta LITEC-kirjasto
    LITEC_Init();

    // Pelisilmukka
    while (LITEC_Running()) {
        LITEC_HandleInput();
        LITEC_Update();
        LITEC_Render();
    }

    // Siivoa jäljet
    LITEC_Shutdown();

    return 0;
}