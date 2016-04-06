#include "Enemy.h"

Enemy::Enemy(int a)
{
	rect.setSize(sf::Vector2f(15, 37.5));
	rect.setFillColor(sf::Color::Red);
	hp = a;

}

void Enemy::updatePosition() {
	if (rect.getPosition().y <600) {
		rect.move(0, 3);
	}
	else {
		rect.setPosition(rand() % 390 - 10, 0);
	}

}
