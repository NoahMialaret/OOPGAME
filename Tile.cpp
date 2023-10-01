#include "Tile.h"

Tile::Tile(int type, float game_scale, float sprite_dim, sf::Vector2f pos, sf::Texture& sprite_sheet)
    :
    type(type)
{
    sprite.setTexture(sprite_sheet);

    sf::IntRect sub_rect(type * sprite_dim, 0, sprite_dim, sprite_dim);

    sprite.setTextureRect(sub_rect);
    sprite.setScale(sf::Vector2f(game_scale, game_scale));
    sprite.setPosition(pos);
}

void Tile::render(sf::RenderWindow *win) const {
    win->draw(sprite);
}

sf::Vector2f Tile::getPosition() const
{
    return sprite.getPosition();
}

int Tile::getType() const
{
    return type;
}
