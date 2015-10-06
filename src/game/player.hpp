#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "game/drawable.hpp"
#include "game/sprite_sequence.hpp"
#include "utils/directions.hpp"

namespace game {

class Player final : public Drawable
{
  public:

    Player(const sf::Vector2f& size, const sf::Vector2f& position);

    void setPosition(const sf::Vector2f& position) override;
    void setSize(float x, float y) override;

    const sf::Vector2f& getPosition() const;
    sf::Vector2f getCenter() const;
    sf::Vector2f getSize() const;
    float getWidth() const { return getSize().x; }
    float getHeight() const { return getSize().y; }

    /*! Update player relative to last update */
    void update(const sf::Time& elapsed_time);

    void move(float x, float y);

    /*! Enable player moving to a direction */
    void setMovingTo(Direction direction);

    /*! Disable player movement to a direction */
    void stopMoving();

    /*! Stop player movements and reset inertia */
    void resetMovement();

    float getHorizontalSpeed() const { return _horizontal_speed; }

    bool hasSpeed() const { return _horizontal_speed != 0.f; }

    bool isMoving() const { return _moving_to_direction != Direction::None; }

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    bool isMaxSpeedReached() const;
    void updateSpeed(const sf::Time& elapsed_time);

  private:

    /*! Animation player moves to the right */
    SpriteSequence _sprites_move_right;

    /*! Animation player moves to the left */
    SpriteSequence _sprites_move_left;

    /*! Current active animation */
    SpriteSequence* _current_sprite_sequence {nullptr};

    /*! Current player body direction */
    Direction _body_direction { Direction::Right };

    /*! Current player movement direction */
    Direction _moving_to_direction { Direction::None };

    /*! Current horizontal movement speed (pixels/millisec) */
    float _horizontal_speed {0.f};

    /*! Maximum move speed (pixels/millisec) */
    static constexpr float _max_speed {0.3};

    /*! Acceleration per milliseconds
     *  \note _horizontal_speed is raised by _acceleration every millisecond
     */
    static constexpr float _acceleration {0.00025};

    /*! Deceleration per milliseconds
     *  \note _horizontal_speed is downed by _deceleration every millisecond
     */
    static constexpr float _deceleration {0.001};
};

} // namespace game

#endif // PLAYER_HPP
