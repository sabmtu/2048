#include <visualizer/game_2048_app.h>

namespace game_2048 {

Game2048App::Game2048App()
    : board_(glm::vec2(kMargin, kMargin), kBoardDimension,
             kWindowSize - 2 * kMargin){
    ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);

}

void Game2048App::draw() {
    ci::Color8u background_color(230, 230, 220);  // light yellow
    ci::gl::clear(background_color);
    board_.Draw();
}

void Game2048App::keyDown(ci::app::KeyEvent event) {
    AppBase::keyDown(event);
}


}
