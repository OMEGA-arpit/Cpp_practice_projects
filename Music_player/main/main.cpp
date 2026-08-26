#include "MusicApplicationFactory.h"
#include "MusicApplication.h"

int main() {
    MusicApplicationFactory factory;
    MusicApplication* musicApp = factory.create();

    musicApp->handleMainMenu();

    delete musicApp;
    return 0;
}
