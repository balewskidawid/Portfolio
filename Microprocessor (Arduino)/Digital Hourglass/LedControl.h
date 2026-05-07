#ifndef LedControl_h
#define LedControl_h

#include <Adafruit_NeoPixel.h>

struct coord {
    int x;
    int y;
};

class LedControl {
private:
    Adafruit_NeoPixel& strip;
    int numDevices;
    uint32_t color;
    int rotation;

    coord transform(coord xy);
    coord flipHorizontally(coord xy);
    coord flipVertically(coord xy);
    coord rotate90(coord xy);
    coord rotate180(coord xy);
    coord rotate270(coord xy);

public:
    LedControl(int numPixels, Adafruit_NeoPixel& strip);

    void setRotation(int rot);
    void clearDisplay(int addr);
    void setIntensity(int intensity);
    void setXY(int addr, int x, int y, bool state);
    void setLed(int addr, int x, int y, bool state);
    void invertXY(int addr, int x, int y);
    bool getXY(int addr, int x, int y);
};

#endif  // LedControl_h
