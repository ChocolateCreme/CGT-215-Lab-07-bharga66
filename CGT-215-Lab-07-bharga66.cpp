#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(100, 100));
	ball.setRadius(20);
	ball.applyImpulse(Vector2f(0.1,0.1));
	world.AddPhysicsBody(ball);

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	// Ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	// Right wall
	PhysicsRectangle rightWall;
	rightWall.setSize(Vector2f(20, 600));
	rightWall.setCenter(Vector2f(790, 300));
	rightWall.setStatic(true);
	world.AddPhysicsBody(rightWall);

	// Left wall
	PhysicsRectangle leftWall;
	leftWall.setSize(Vector2f(20, 600));
	leftWall.setCenter(Vector2f(10, 300));
	leftWall.setStatic(true);
	world.AddPhysicsBody(leftWall);

	// Obstacle
	PhysicsRectangle obstacle;
	obstacle.setSize(Vector2f(100, 100));
	obstacle.setCenter(Vector2f(400, 300));
	obstacle.setStatic(true);
	world.AddPhysicsBody(obstacle);

	// These are the collision names
	int thudCount(1);
	int bangCount(1);

	// These four are for the thud sound; the walls, floor, and ceiling
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	// This one is for the bang sound; the obstacle in the middle
	obstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());

	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		if (bangCount > 3) {
			exit(0);
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(ceiling);
		window.draw(rightWall);
		window.draw(leftWall);
		window.draw(obstacle);
		window.display();
	}
}