#ifndef GAME_HUD_HPP
#define GAME_HUD_HPP

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>

#include "game/drawable.hpp"
#include "game/animations/zoom_text_animation.hpp"

namespace game {

class HUD final : public Drawable
{
  public:

    HUD(const sf::Vector2u& size);

    void setTime(float time);
    void setScore(unsigned int score);

    const sf::Vector2f& getPosition() const { return _position; }

    bool isInStartAnimation() const { return _countdown_animation ? true : false; }

    void update(const sf::Time& elapsed_time);

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    void setCountdownText(short value);
    void updateCountdown(const sf::Time& elapsed_time);
    void startCountdownAnimation();

  private:

    sf::Vector2f _position {0,0};
    sf::Vector2u _size;
    sf::Text _text_score;
    sf::Text _text_elapsed_time;

    std::shared_ptr<sf::Text> _text_countdown;
    std::unique_ptr<animation::ZoomTextAnimation> _countdown_animation;

    sf::Sound _beep_sound;

    static constexpr short _secs_before_start {3};
};

}

#endif // GAME_HUD_HPP
