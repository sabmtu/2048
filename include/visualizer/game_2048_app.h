#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "board_display.h"
#include <core/game_engine.h>

namespace game_2048 {


class Game2048App : public ci::app::App {
public:
    Game2048App();

    void draw() override;
    //void update() override;
    void keyDown(ci::app::KeyEvent event) override;

    const double kWindowSize = 675;
    const double kMargin = 150;
    const size_t kBoardDimension = 4;

private:
    GameEngine game_engine_;
    BoardDisplay board_display_;

};

}
