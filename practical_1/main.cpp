#include <SFML/Graphics.hpp>
// HELLO WORLD

/*int main(){
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen()){
      sf::Event event;
      while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
    }
    window.clear();
    window.draw(shape);
    window.display();
  }
  return 0;
}*/

// PONG

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] =
{
	Keyboard::A,	// Player 1 up
	Keyboard::Z,	// Player 1 down
	Keyboard::Up,	// Player 2 up
	Keyboard::Down	// Player 2 down
};
const Vector2f paddleSize(25.0f, 100.0f);
const float ballRadius = 10.0f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.0f;

CircleShape ball;
RectangleShape paddles[2];
Vector2f ballVelocity;
bool server = false;
Font font;
Text text;
int score1 = 0;
int score2 = 0;
bool AI = true;


void Load()
{
	// Load font
	font.loadFromFile("res/fonts/Roboto-Regular.ttf");
	// Set text element to use font
	text.setFont(font);
	// Set the character size to 24 pixels
	text.setCharacterSize(24);
	// Set string
	text.setString("0 : 0");
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);

	// Set size and origin of paddles
	for (auto &p : paddles)
	{
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.0f);
	}
	// Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	// Reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
	// Reset ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	// Ball velocity
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
}

void Reset()
{
	Load();
	// Update Score Text
	text.setString(to_string(score1) + " : " + to_string(score2));
	// Keep Score Text Centered
	text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);
}

void Update(RenderWindow &window) 
{
	// Reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	// Check and consume events
	Event event;
	while (window.pollEvent(event)) 
	{
		if (event.type == Event::Closed) 
		{
			window.close();
			return;
		}
	}

	// Quit Via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) 
	{
		window.close();
	}

	// Handle paddle movement
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0])) 
	{
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1])) 
	{
		direction++;
	}
	paddles[0].move(0, direction * paddleSpeed * dt);
	if (paddles[0].getPosition().y + paddleSize.y / 2 > gameHeight)
	{
		paddles[0].setPosition(paddles[0].getPosition().x, gameHeight - paddleSize.y / 2);
	}
	else if (paddles[0].getPosition().y - paddleSize.y / 2 < 0)
	{
		paddles[0].setPosition(paddles[0].getPosition().x, paddleSize.y / 2);
	}
	direction = 0.0f;
	// If there is no AI then the player 2 can take the control of the right paddle
	if (!AI)
	{
		if (Keyboard::isKeyPressed(controls[2]))
		{
			direction--;
		}
		if (Keyboard::isKeyPressed(controls[3]))
		{
			direction++;
		}
	}
	else
	{
		float AIdirection = (ball.getPosition().y - paddles[1].getPosition().y) / sqrt(pow(ball.getPosition().y, 2) + pow(paddles[1].getPosition().y, 2));
		if (AIdirection > 0)
		{
			direction++;
		}
		else
		{
			direction--;
		}
	}
	paddles[1].move(0, direction * paddleSpeed * dt);
	if (paddles[1].getPosition().y + paddleSize.y / 2 > gameHeight)
	{
		paddles[1].setPosition(paddles[1].getPosition().x, gameHeight - paddleSize.y / 2);
	}
	else if (paddles[1].getPosition().y - paddleSize.y / 2 < 0)
	{
		paddles[1].setPosition(paddles[1].getPosition().x, paddleSize.y / 2);
	}

	// Check ball collisions
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	//Left paddle
	if (//ball is inline or behind paddle
		bx < paddles[0].getPosition().x + paddleSize.x / 2 &&
		//AND ball is below top edge of paddle
		by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[0].getPosition().y + (paddleSize.y * 0.5))
	{
		//Bounce off left paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(0.1, 0);
	}
	// Right paddle
	else if (//ball is inline or behind paddle
		bx > paddles[1].getPosition().x - paddleSize.x / 2 &&
		//AND ball is below top edge of paddle
		by > paddles[1].getPosition().y - (paddleSize.y * 0.5) &&
		//AND ball is above bottom edge of paddle
		by < paddles[1].getPosition().y + (paddleSize.y * 0.5))
	{
		//Bounce off right paddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-0.2, 0);
	}
	// Bottom wall
	else if (by > gameHeight)
	{
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);
	}
	// Top wall
	else if (by < 0)
	{
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	// Right wall
	else if (bx > gameWidth)
	{
		score1++;
		Reset();
	}
	// Left wall
	else if (bx < 0)
	{
		score2++;
		Reset();
	}
	ball.move(ballVelocity * dt);
}

void Render(RenderWindow &window) 
{
	// Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}

int main() 
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
	Load();
	while (window.isOpen()) 
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}