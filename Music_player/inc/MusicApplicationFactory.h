#ifndef MUSIC_APPLICATION_FACTORY_H
#define MUSIC_APPLICATION_FACTORY_H

#include <memory>
#include "MusicApplication.h"

class MusicApplicationFactory {
public:
    std::unique_ptr<MusicApplication> create();
};

#endif
