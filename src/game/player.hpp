#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game/animations/sprites_animation.hpp"
#include "game/drawable.hpp"
#include "utils/directions.hpp"

namespace game {

class Player final : public Drawable
{
  public:

    Player(const sf::Vector2f& size);

    void setPosition(const sf::Vector2f& position);
    void setSize(float x, float y);

    const sf::Vector2f& getPosition() const;

    /*! Enable player moving to a direction */
    void setMovingTo(Direction direction);

    /*! Disable player movement to a direction */
    void stopMoving();

    /*! Update player relative to last update */
    void update(const sf::Time& elapsed_time);

    float getHorizontalSpeed() const { return _horizontal_speed; }

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    sf::View _view;

    /*! Animation player moves to the right */
    animation::SpritesAnimation _animation_move_right;

    /*! Animation player moves to the left */
    animation::SpritesAnimation _animation_move_left;

    /*! Current active animation */
    animation::SpritesAnimation* _current_animation {nullptr};

    /*! Helper vector which holds all player's animations */
    std::vector<animation::Animation*> _animations;

    /*! Current player direction */
    Direction _direction { Direction::Right };

    /*! Doesn the player currently moving ? */
    bool _is_moving {false};

    /*! Current horizontal movement speed (pixels/millisec) */
    float _horizontal_speed {0.f};

    /*! Maximum move speed (pixels/millisec) */
    static constexpr float _max_speed {1.f};

    /*! Movement acceleration */
    static constexpr float _acceleration {1.5};

    /*! Movement deceleration */
    static constexpr float _deceleration {2};
};

} // namespace game

#endif // PLAYER_HPP
