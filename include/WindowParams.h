#ifndef WINDOWPARAMS_H_
#define WINDOWPARAMS_H_

struct WinParams
{
    //Store the X and Y rotation mouse value
    int spinXFace = 0;
    int spinYFace = 0;

    //Check if mouse button is pressed when dragging
    bool rotate = false;
    bool translate = false;

    //The previous value for X and Y mouse value
    int origX = 0;
    int origY = 0;

    //The previous X and Y mouse value for Position changes
    int origXPos = 0;
    int origYPos = 0;


    //Window Width and Height
    int width = 1024;
    int height = 720;

};


    //the increment for x/y translation with mouse movement
    constexpr float INCREMENT = 0.01f;

    // the increment for the wheel zoom
    constexpr float ZOOM = 0.1f;

#endif
