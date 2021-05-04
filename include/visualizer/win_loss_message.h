#pragma once

#include <vector>
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include <core/game_engine.h>

namespace game_2048 {
using std::vector;

class WinLossMessage {
public:
    WinLossMessage(const glm::vec2& top_left_corner, double size);

    void Draw();
    void FindStateOfGame(GameEngine::GameState state);
    //void keyDown(ci::app::KeyEvent event) override;


private:
    std::string game_end_message_;

    glm::vec2 top_left_corner_;
    double board_size_;
    //GameEngine::GameState current_state_;


};

}

