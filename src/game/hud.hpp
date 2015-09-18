#ifndef GAME_HUD_HPP
#define GAME_HUD_HPP

#include <SFML/Graphics.hpp>

#include "game/drawable.hpp"
#include "game/animations/zoom_text_animation.hpp"

namespace game {

class HUD final : public Drawable
{
  public:

    HUD(const sf::Vector2u& size);

    void setPosition(const sf::Vector2f& position);
    void setSize(float x, float y);

    void setTime(float time);
    void setScore(unsigned int score);

    const sf::Vector2f& getPosition() const { return _position; }

    void update(const sf::Time& elapsed_time);

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    void drawCountdown(sf::RenderTarget& target, sf::RenderStates states) const;

    /*! Update text positions relative to given position */
    void updateTextPositions();

    void updateCountdown(const sf::Time& elapsed_time);

  private:

    sf::Vector2f _position {0,0};
    sf::Vector2u _size;
    sf::Text _text_score;
    sf::Text _text_elapsed_time;

    std::vector<animation::ZoomTextAnimation> _countdown_animations;
    size_t _countdown_offset {0};
};

}

#endif // GAME_HUD_HPP
