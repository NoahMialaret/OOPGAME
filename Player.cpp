#include "Player.h"

Player::Player(const char *tex_name, float game_scale, sf::Vector2f pos)
    :
    Entity(tex_name, game_scale, pos)
{}

void Player::update(const sf::RenderWindow *win, bool jump_button, bool left_button, bool right_button) {

    if (!jump_button) {
		jump_hold = false;
	}

	// Continues adding jump height if the jump button is held
	if (jump_button && can_increase_jump_velocity && velocity.y > -10.0f) {
		velocity.y -= 2.0f;
	} 
	else {
		can_increase_jump_velocity = false;
	}

	// Initial jump velocity
	if (!jump_hold && jump_button && is_grounded) {
		velocity.y = -4.0f;
		is_grounded = false;
		can_increase_jump_velocity = true;
		jump_hold = true;
	}

	// Effect of gravity on the player
	velocity.y += 0.7f;

	// Horizontal velocity calculation, varies depending on whether the player is gorunded or not
	if (right_button != left_button) { // i.e. if only one of them is pressed
		float speed_modifier = 0.8f - !is_grounded * 0.1f;

		velocity.x += right_button * speed_modifier - left_button * speed_modifier;
		
		velocity.x = std::clamp(velocity.x, -7.0f, 7.0f);
	}
	else { // if both or neither buttons are pressed
		if (velocity.x > 0.0f) {
			velocity.x -= is_grounded ? 0.4f : 0.07f;
			if (velocity.x < 0.0f) {
				velocity.x = 0.0f;
			}
		}
		else if (velocity.x < 0.0f) {
			velocity.x += is_grounded ? 0.4f : 0.07f;
			if (velocity.x > 0.0f) {
				velocity.x = 0.0f;
			}
		}
	}

	sprite.move(velocity);

	if (sprite.getPosition().y > (float)win->getSize().y - sprite.getScale().y * sprite.getTextureRect().height) {
		is_grounded = true;
		velocity.y = 0.0f;
	}
	if (sprite.getPosition().x < 0.0f || sprite.getPosition().x > (float)win->getSize().x - sprite.getScale().x * sprite.getTextureRect().width) {
		velocity.x = 0.0f;
	}

	sf::Vector2f pos(0.0f, 0.0f);
	pos.x = std::clamp(sprite.getPosition().x, 0.0f, (float)win->getSize().x - sprite.getScale().x * sprite.getTextureRect().width);
	pos.y = std::clamp(sprite.getPosition().y, 0.0f, (float)win->getSize().y - sprite.getScale().y * sprite.getTextureRect().height);
	sprite.setPosition(pos);
}

void Player::setVelocity(sf::Vector2f new_vel) {
	if (new_vel.y > velocity.y)
	{
		can_increase_jump_velocity = false;
	}
	velocity = new_vel;
}
