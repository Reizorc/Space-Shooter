#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Space Shooter/Player.h"
#include "Space Shooter/Meteorite.h"
#include "Space Shooter/Missile.h"
#include "Space Shooter/Entity.h"
#include <vector>
#include "Space Shooter\Enemy.h"

using namespace std;

template <class Container>
typename Container::iterator to_mutable_iterator(Container& c, typename Container::const_iterator it)
{
	return c.begin() + (it - c.begin());
}

int main()
{
	int counter;
	int counter2;
	sf::Clock clockMissile;
	sf::Clock clockMeteorite;
	sf::Clock clockEnemy;

	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(400, 600), "SFML works!");
	window.setFramerateLimit(60);

	Player player;

	vector<Meteroite>::const_iterator iterMeteorite;
	vector<Meteroite> meteoriteArray;

	Meteroite meteorite1;

	vector<Enemy>::const_iterator iterEnemy;
	vector<Enemy> enemyArray;

	Enemy enemy1;

	vector<missile>::const_iterator iterMissile;
	vector<missile> missileArray;

	missile missile1;

	bool canShoot = true;
	float tempsMeteorite;
	float tempsRecharge;
	float tempsEnemy;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case(sf::Event::Closed):
				window.close();
				break;
			case(sf::Event::KeyPressed):
				switch (event.key.code) {
				case(sf::Keyboard::Escape):
					window.close();
					break;
				default:
					break;
				}
			}
		}
		window.clear();

		//Gestion du temps
		tempsMeteorite = clockMeteorite.getElapsedTime().asSeconds();
		tempsRecharge = clockMissile.getElapsedTime().asSeconds();
		tempsEnemy = clockEnemy.getElapsedTime().asSeconds();

		//COLLISION
		counter = 0;
		for (iterMissile = missileArray.begin(); iterMissile != missileArray.end(); iterMissile++) {
			counter2 = 0;
			for (iterMeteorite = meteoriteArray.begin(); iterMeteorite != meteoriteArray.end(); iterMeteorite++) {

				if (missileArray[counter].rect.getGlobalBounds().intersects(meteoriteArray[counter2].circ.getGlobalBounds())) {
					meteoriteArray[counter2].hp -= 5;
					missileArray[counter].isDestroyed = true;
				}

				if (meteoriteArray[counter2].hp <= 0) {
					meteoriteArray[counter2].isAlive = false;
				}
				counter2++;
			}
			counter++;
		}

		//COLLISION MISSILE/ENEMY
		counter = 0;
		for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++) {
			counter2 = 0;
			for (iterMissile = missileArray.begin(); iterMissile != missileArray.end(); iterMissile++){
				if (enemyArray[counter].rect.getGlobalBounds().intersects(missileArray[counter2].rect.getGlobalBounds())) {
					cout << "TOUCHE" << endl;
					enemyArray[counter].hp -= 5;
				}
			counter2++;
		}
			counter++;
		}

		//Supprimer météorites détruites
		counter = 0;
		for (iterMeteorite = meteoriteArray.begin(); iterMeteorite != meteoriteArray.end(); iterMeteorite++)
		{
			if (meteoriteArray[counter].isAlive == false)
			{
				cout << "Enemy has been obliterated! lawlz" << endl;
				iterMeteorite = meteoriteArray.erase(to_mutable_iterator(meteoriteArray, iterMeteorite));
				break;
			}

			counter++;
		}

		//Supprimer missiles
		counter = 0;
		for (iterMissile = missileArray.begin(); iterMissile != missileArray.end(); iterMissile++)
		{
			if (missileArray[counter].isDestroyed == true)
			{
				iterMissile = missileArray.erase(to_mutable_iterator(missileArray, iterMissile));
				cout << "MISSILE DESTROYED" << endl;
				break;
			}
			counter++;
		}

		//Créer missiles
		if (tempsRecharge >= 0.25) {
			clockMissile.restart();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				missile1.rect.setPosition(player.rect.getPosition().x + 10, 540);
				missileArray.push_back(missile1);
			}
		}


		//Dessiner missiles
		counter = 0;
		for (iterMissile = missileArray.begin(); iterMissile != missileArray.end(); iterMissile++) {
			missileArray[counter].updatePosition();
			window.draw(missileArray[counter].rect);
			counter++;
		}

		//Créer météorites
		if (tempsMeteorite >= 2) {
			meteorite1.circ.setPosition(rand() % 390 - 10, -20);
			meteoriteArray.push_back(meteorite1);
			cout << "Nombres de meteorites : " << meteoriteArray.size() << endl;
			clockMeteorite.restart();
		}
		//Dessiner météorites
		counter = 0;
		for (iterMeteorite = meteoriteArray.begin(); iterMeteorite != meteoriteArray.end(); iterMeteorite++) {
				meteoriteArray[counter].updatePosition();
				window.draw(meteoriteArray[counter].circ);
				counter++;
		}

		//Créer vaisseaux ennemis
		if (tempsEnemy >= 1) {
			enemy1.rect.setPosition(rand() % 390 - 10, -20);
			enemyArray.push_back(enemy1);
			cout <<"Nombres d'ennemis : "<< enemyArray.size() << endl;
			clockEnemy.restart();
		}

		//Dessiner vaisseaux ennemis
		counter = 0;
		for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++) {
			enemyArray[counter].updatePosition();
			window.draw(enemyArray[counter].rect);
			counter++;
		}

		player.movement(); //Player movement

		window.draw(player.rect);
		window.display();
	}

	return 0;
}
