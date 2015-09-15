#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "game/animation.hpp"
#include "game/drawable.hpp"

namespace game {

class Player final : public Drawable
{
  public:

    Player();

    void setPosition(const sf::Vector2f& position);
    void setSize(float x, float y);

    const sf::Vector2f& getPosition() const { return _current_animation->getPosition(); }

  protected:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    /*! Animation player moves to the right */
    Animation _animation_move_right;

    /*! Animation player moves to the left */
    Animation _animation_move_left;

    /*! Current active animation */
    Animation* _current_animation {nullptr};

    /*! Helper vector which holds all player's animations */
    std::vector<Animation*> _animations;
};

typedef std::shared_ptr<Player> PlayerPtr;

} // namespace game

#endif // PLAYER_HPP
