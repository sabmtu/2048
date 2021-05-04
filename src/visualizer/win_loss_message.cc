#include <visualizer/win_loss_message.h>

namespace game_2048 {

WinLossMessage::WinLossMessage(const glm::vec2 &top_left_corner, double size) {
    top_left_corner_ = top_left_corner;
    board_size_ = size;
}

void WinLossMessage::Draw() {
    glm::vec2 top_left = top_left_corner_;
    glm::vec2 bottom_right = top_left_corner_ + glm::vec2(board_size_, board_size_);

    //Creates and draws rectangle from given positions + margin to outline board
    ci::Rectf board_outline(top_left, bottom_right);
    ci::gl::color(ci::Color("white"));
    ci::gl::drawSolidRect(board_outline);

    ci::gl::drawStringCentered(game_end_message_,
                               top_left_corner_ + glm::vec2(board_size_ / 2, board_size_ / 2.5),
                               "gray", ci::Font("Times New roman", 50));
}

void WinLossMessage::FindStateOfGame(GameEngine::GameState state) {
    if (state == GameEngine::GameState::WON) {
        game_end_message_ = "You win!";

    } else if (state == GameEngine::GameState::LOST) {
        game_end_message_ = "Game Over!";
    }
}

/*
void WinLossMessage::keyDown(ci::app::KeyEvent event) {
    switch (event.getCode()) {

    }
}*/


}
