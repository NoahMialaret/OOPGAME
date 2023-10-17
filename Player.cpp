#include "Player.h"

Player::Player(const char *tex_name, float game_scale)
    :
    Entity(tex_name, game_scale, sf::Vector2f(0.0f, 0.0f))
{}

void Player::update(bool jump_button, bool left_button, bool right_button, sf::Clock* clock) {
	
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
	if (!jump_hold && jump_button && is_grounded && can_control) {
		velocity.y = -4.0f;
		is_grounded = false;
		can_increase_jump_velocity = true;
		jump_hold = true;
	}

	// Effect of gravity on the player
	velocity.y += 0.7f;

	// Horizontal velocity calculation, varies depending on whether the player is gorunded or not
	if (right_button != left_button && can_control) { // i.e. if only one of them is pressed
		float speed_modifier = 0.8f - !is_grounded * 0.1f;

		velocity.x += right_button * speed_modifier - left_button * speed_modifier;
		
		velocity.x = std::clamp(velocity.x, -7.0f, 7.0f);
	}
	else { // if both or neither buttons are pressed
		if (velocity.x > 0.0f) {
			velocity.x -= is_grounded ? 0.65f : 0.1f;
			if (velocity.x < 0.0f) {
				velocity.x = 0.0f;
			}
		}
		else if (velocity.x < 0.0f) {
			velocity.x += is_grounded ? 0.65f : 0.1f;
			if (velocity.x > 0.0f) {
				velocity.x = 0.0f;
			}
		}
	}

	if (is_grounded) {
		saved_position = sprite.getPosition();
	}

	sprite.move(velocity);

	if (is_invincible && invincibilty_start_time + 2000 < clock->getElapsedTime().asMilliseconds()) {
		std::cout << "No longer invincible..." << std::endl;
		is_invincible = false;
	}
}

void Player::render(sf::RenderWindow *win) const {
    win->draw(sprite);
}

void Player::setVelocity(sf::Vector2f new_vel) {
	if (new_vel.y > velocity.y) {
		can_increase_jump_velocity = false;
	}
	velocity = new_vel;
}

void Player::reset() {
	velocity = sf::Vector2f(0.0f, 0.0f);
	sprite.setPosition(saved_position);
}

void Player::giveWeapon(Weapon* weapon) {
	weapons.push_back(weapon);

	std::cout << "Gave player a weapon (" << weapon->getName() << ")." << std::endl;
}

Weapon* Player::getWeapon(int index) {
	if (weapons.size() == 0) {
		std::cout << "Player has no weapons!" << std::endl;
		return nullptr;
	}

	if (index < 0 || index >= weapons.size()) {
		std::cout << "Trying to access non-existent weapon in Player::drawWeapon(), accessing first weapon." << std::endl;
		return weapons[0];
	}

	weapons[index]->setCentrePosition(sf::Vector2f(sprite.getPosition().x + sprite.getScale().x * (float)sprite.getTextureRect().width / 2,
		sprite.getPosition().y + sprite.getScale().y * (float)sprite.getTextureRect().height / 2));

	std::cout << "Weapon at " << index << " drawn! (" << weapons[index]->getName() << ")" << std::endl;
	return weapons[index];
}

std::vector<std::string> Player::getWeaponNames()
{
	std::vector<std::string> weapon_names;
	for (auto& w : weapons) {
		weapon_names.push_back(w->getName());
	}
    return weapon_names;
}

void Player::clean()
{
	for (int i = 0; i < weapons.size(); i++)
	{
		delete weapons[i];
	}

	std::cout << "Successfully cleaned Player!" << std::endl;
}

bool Player::isAttackActive() {
    return is_attack_active;
}

void Player::savePosition() {
	saved_position = sprite.getPosition();
}

const int *Player::getHealth() {
    return &health;
}

bool Player::takeDamage(int damage_amount, sf::Clock* clock) {

	if (is_invincible) {
		return false;
	}

	is_invincible = true;
	invincibilty_start_time = clock->getElapsedTime().asMilliseconds();

    health -= damage_amount;

	std::cout << "player took " << damage_amount << " damage, health: " << health << std::endl;

	if (health <= 0) {
		return true;
	}
	return false;
}

int* Player::getArrows() {
    return &arrows;
}

bool Player::isStill() {
    return velocity.x == 0.0f && velocity.y == 0.0f;
}

bool Player::isInvincible() const {
    return is_invincible;
}

void Player::setControl(bool control) {
	can_control = control;
}

bool Player::addCoins(int amount) {
	if (coins + amount < 0) {
		return false;
	}
	coins += amount;
	return true;

}

int *Player::getCoins() {
    return &coins;
}
