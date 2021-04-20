
#include <visualizer/game_2048_app.h>

using game_2048::Game2048App;

void prepareSettings(Game2048App::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(Game2048App, ci::app::RendererGl, prepareSettings);