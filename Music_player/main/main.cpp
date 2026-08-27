#include "MusicApplicationFactory.h"
#include "MusicApplication.h"

int main() {
    MusicApplicationFactory factory;
    auto musicApp = factory.create();
    musicApp->handleMainMenu();
    return 0;
}
