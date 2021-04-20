#pragma once
#include "cinder/gl/gl.h"

namespace game_2048 {

class Tile {

public:
    Tile();
    Tile(glm::vec2 position, size_t num, ci::Color color);
    glm::vec2 position_;

    const ci::Color& GetColor() const;
    size_t GetNumber() const;
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();

private:
    double kMoveSpeed = 2;
    //glm::vec2 velocity_;
    size_t number_;
    ci::Color color_;

};

}
