#include "Player.hpp"
#include "StateGame.hpp"

void Player::shootPresent()
{
	Player::m_gameState.spawnPresent();
	m_shootTimer = GP::playerShotTimer();
	m_sprite.flash(0.25f);
}
