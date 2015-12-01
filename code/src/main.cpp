#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Ant{
public:
  Ant(sf::Vector2u mapsize);
  sf::RectangleShape body;
  sf::Vector2f direction;
};

class Food{
public:
  Food(sf::Vector2u mapsize);
  sf::RectangleShape body;
};

Food::Food(sf::Vector2u mapsize){
  body.setSize(sf::Vector2f(7,7));
  body.setFillColor(sf::Color(0,255,0,170));
  body.setPosition(rand() % mapsize.x, rand() % mapsize.y);
};

Ant::Ant(sf::Vector2u mapsize){
  direction.x = 1; direction.y = 1;
  body.setSize(sf::Vector2f(5, 5));
  body.setPosition(rand() % mapsize.x/2 + mapsize.x/4, rand() % mapsize.y/2 + mapsize.y/4);
}

//Custom functions
std::vector<Ant> generateAnts(int number, sf::Vector2u mapsize);
std::vector<Food> generateFood(int number, sf::Vector2u mapsize);
void changeDirection(std::vector<Ant> ants);

///////////////////////////////////////////////////
/////////////////MAIN ////////////////////////////
/////////////////////////////////////////////////
int main()
{
    srand (time(NULL)); //seed for random numbers
    sf::Clock clock;
    sf::Time time_move;
    sf::Time time_change_direction;
    sf::RenderWindow window(sf::VideoMode(500, 500), "Ant collaboratibe behaviour");

    //generate 10 ants spreaded randomly in the map
    std::vector<Ant> ants = generateAnts(10, window.getSize());
    //generate 6 foods spreaded randomly
    std::vector<Food> foods = generateFood(6, window.getSize());

    //main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //change direction every 300 milliseconds
        if((clock.getElapsedTime() - time_change_direction).asMilliseconds() > 300){
          for(int i=0; i < ants.size(); i++){
            ants[i].direction.x = rand() % 3 -1; //random number between -1, 0 and 1
            ants[i].direction.y = rand() % 3 -1;
          }
          time_change_direction = clock.getElapsedTime();
        }

        // MOVE every 20 milliseconds
        if((clock.getElapsedTime() - time_move).asMilliseconds() > 20){
          for(int i=0; i < ants.size(); i++){
            ants[i].body.move(ants[i].direction.x,ants[i].direction.y);
          }
          time_move = clock.getElapsedTime();
        }

        window.clear();
        for(int i=0; i < ants.size(); i++){
          window.draw(ants[i].body);
        }
        for(int i=0; i < foods.size(); i++){
          window.draw(foods[i].body);
        }
        window.display();
    }

    return 0;
}

void changeDirection(std::vector<Ant> ants){

}

std::vector<Ant> generateAnts(int number, sf::Vector2u mapsize){
  std::vector<Ant> ants;
  for(int i=0; i <number; i++){
    Ant ant(mapsize);
    ants.push_back(ant);
  }
  return ants;
}

std::vector<Food> generateFood(int number, sf::Vector2u mapsize){
  std::vector<Food> foods;
  for(int i=0; i <number; i++){
    Food food(mapsize);
    foods.push_back(food);
  }
  return foods;
}
