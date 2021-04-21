#include <visualizer/game_2048_app.h>

namespace game_2048 {

Game2048App::Game2048App()
    : game_engine_(glm::vec2(kMargin, kMargin), kBoardDimension,
                 kWindowSize - 2 * kMargin) {
    ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
    board_display_(game_engine_.GetBoard());
}

void Game2048App::draw() {
    ci::Color8u background_color(230, 230, 220);  // light yellow
    ci::gl::clear(background_color);
    board_display_.Draw();
}

void Game2048App::keyDown(ci::app::KeyEvent event) {
    switch (event.getCode()) {
        case ci::app::KeyEvent::KEY_LEFT:
            game_engine_.MoveTiles(Direction::UP);
            break;
        case ci::app::KeyEvent::KEY_RIGHT:
            game_engine_.MoveTiles(Direction::RIGHT);
            break;
        case ci::app::KeyEvent::KEY_UP:
            game_engine_.MoveTiles(Direction::UP);
            break;
        case ci::app::KeyEvent::KEY_DOWN:
            game_engine_.MoveTiles(Direction::DOWN);
            break;
    }

}

}
