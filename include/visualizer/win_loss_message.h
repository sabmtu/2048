#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include <core/game_engine.h>

namespace game_2048 {
using std::vector;

class WinLossMessage {

public:
    /**
     * Constructor initializes variables to draw message.
     * @param top_left_corner 2d vector representing top left corner of the board message
     * @param size double representing size of the board in screen pixels
     */
    WinLossMessage(const glm::vec2& top_left_corner, double size);

    /**
     * Draws the shapes to appear when player wins or loses.
     */
    void Draw();

    /**
     * Sets the message that will appear based on whether or not the player won or lost.
     * @param state GameState representing the current game engine's state of the game
     */
    void FindStateOfGame(GameEngine::GameState state);
    //void keyDown(ci::app::KeyEvent event) override;

private:
    //The message that appears when player wins or loses
    std::string game_end_message_;

    //Specs to draw a rectangle the size of the board
    glm::vec2 top_left_corner_;
    double board_size_;

};

}

