#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

struct Config {
    int windowX = 1920;
    int windowY = 1440;
    bool isFullscreen = false;
    int renderDistance = 16;
    int fov = 90;
};

#endif // CONFIG_H_INCLUDED
