#include "load_assets.h"
#include "loader.h"
#include "types.h"

void load_assets() {
    /**
     * Loading background image texture
    */
    image_loader("assets/images/bg.png", bgId);
    image_loader("assets/images/ball.png", ballId);
    image_loader("assets/images/point.png", pointerId);
    image_loader("assets/images/hole.png", holeId);
    image_loader("assets/images/powermeter_fg.png", powermeterFId);
    image_loader("assets/images/powermeter_bg.png", powermeterBId);
    image_loader("assets/images/powermeter_overlay.png", powermeterOId);
    image_loader("assets/images/splashBg.png", splashScreenId);
    image_loader("assets/images/logo.png", logoId);

    /**
     * Loading font 
    */
    font_loader("assets/font/font.ttf", 32);

}