#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <cmath>
#include <Thor/Graphics.hpp>
#include <Thor/Shapes.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Math.hpp>
#include "Particles.hpp"
#include "Enemy.hpp"
#include "Utils.hpp"

struct menuSystem
{
    sf::Text titleText, playText, quitText, scoreText;
};

int main()
{
    srand(time(NULL));
    sf::Clock gameClock, levelClock, scoreClock;
    unsigned int level {1}, levelCounter {0};
    float Score {0.f};
    scoreClock.restart();

    enemyAI enemyAISine =
    [](sf::Vector2f currentPosition, sf::Vector2f &startingPoint, sf::Vector2f &Destination, sf::Vector2f &linearPosition, float &angle, float deltaTime)
    {
        angle += 0.01 * deltaTime;
        sf::Vector2f direction = Destination - startingPoint;
        normalize(direction);
        float sinDeviation = sin(2 * angle) - 0.5;
        sf::Vector2f deviation(-direction.y, direction.x);
        deviation.x *= sinDeviation * 30.f;
        deviation.y *= sinDeviation * 30.f;
        linearPosition.x += direction.x * 300.f * deltaTime/1000.f;
        linearPosition.y += direction.y * 300.f * deltaTime/1000.f;
        return linearPosition + deviation;
    };

    enemyAI enemyAILine =
    [](sf::Vector2f currentPosition, sf::Vector2f &startingPoint, sf::Vector2f &Destination, sf::Vector2f &linearPosition, float &angle, float deltaTime)
    {
        sf::Vector2f direction = Destination - startingPoint;
        normalize(direction);
        linearPosition.x += direction.x * 300.f * deltaTime/1000.f;
        linearPosition.y += direction.y * 300.f * deltaTime/1000.f;
        return linearPosition;
    };


    sf::Font mainFont;
    mainFont.loadFromFile("resources/DejaVuSans.ttf");

    sf::Text textOverlay {"Current FPS: ", mainFont, 12};
    textOverlay.setPosition(5,5);

    sf::RenderWindow mainWindow {sf::VideoMode{800, 600}, "Triangle Super"};
    mainWindow.setMouseCursorVisible(false);

    sf::View mainView;
    mainView.reset(sf::FloatRect(0.f,0.f,static_cast<float>(mainWindow.getSize().x), static_cast<float>(mainWindow.getSize().y)));
    mainView.setViewport(sf::FloatRect {0.f, 0.f, 1.f, 1.f});

    Particles stars {sf::Color::White, 2, 4, sf::Vector2f{0.1,0.1}, sf::Vector2i{5, 10}, sf::Vector2f{mainWindow.getSize().x/2.f, mainWindow.getSize().y/2.f}, 400.f,
                     sf::Vector2f{0.1f, 0.1f}, 80.f, sf::Vector2f{0.f, 360.f}
                    };

    float playerSize {10.f};
    sf::CircleShape player {playerSize, 6};
    player.setFillColor(sf::Color {80,80,80,255});
    player.setOrigin(sf::Vector2f {playerSize,playerSize});

    std::vector<std::unique_ptr<Enemy>> Enemies;
    sf::Color enemyColor {sf::Color::White};

    sf::Music mainMusic;
    mainMusic.openFromFile("resources/TriangleSuper.ogg");
    mainMusic.setVolume(50.f);
    mainMusic.setLoop(true);
    mainMusic.play();

    int fpsLimit {200};

    bool gameStatus {true};

    menuSystem gameMenu;

    gameMenu.titleText.setFont(mainFont);
    gameMenu.titleText.setString("Triangle Super");
    gameMenu.titleText.setCharacterSize(72);
    gameMenu.titleText.setPosition(mainWindow.getSize().x/2 - gameMenu.titleText.getGlobalBounds().width/2.f,
                                   mainWindow.getSize().y/2 - gameMenu.titleText.getGlobalBounds().height/2.f);

    gameMenu.playText.setFont(mainFont);
    gameMenu.playText.setString("Play!");
    gameMenu.playText.setCharacterSize(30);
    gameMenu.playText.setPosition(mainWindow.getSize().x/3 - gameMenu.playText.getGlobalBounds().width/2.f,
                                  (mainWindow.getSize().y/3) *2 - gameMenu.playText.getGlobalBounds().height/2.f);

    gameMenu.quitText.setFont(mainFont);
    gameMenu.quitText.setString("Quit.");
    gameMenu.quitText.setCharacterSize(30);
    gameMenu.quitText.setPosition(mainWindow.getSize().x/3 *2 - gameMenu.quitText.getGlobalBounds().width/2.f,
                                  (mainWindow.getSize().y/3)*2-gameMenu.quitText.getGlobalBounds().height/2.f);

    gameMenu.scoreText.setFont(mainFont);
    gameMenu.scoreText.setCharacterSize(30);
    gameMenu.scoreText.setPosition(mainWindow.getSize().x/2 - gameMenu.scoreText.getGlobalBounds().width/2.f,
                                   (mainWindow.getSize().y/3)-gameMenu.scoreText.getGlobalBounds().height/2.f);


    while(mainWindow.isOpen())
    {
        sf::Event mainEvent;
        while(mainWindow.pollEvent(mainEvent))
        {
            switch(mainEvent.type)
            {
            case sf::Event::Closed:
                mainWindow.close();
                break;

            case sf::Event::Resized:
                mainView.setSize(sf::Vector2f(mainEvent.size.width, mainEvent.size.height));
                mainWindow.setView(mainView);
                break;

            case sf::Event::MouseMoved:
                if(mainEvent.mouseMove.x > 0 && mainEvent.mouseMove.y > 0 &&
                        static_cast<unsigned int>(mainEvent.mouseMove.x) < mainWindow.getSize().x &&
                        static_cast<unsigned int>(mainEvent.mouseMove.y) < mainWindow.getSize().y)
                    player.setPosition(mainEvent.mouseMove.x, mainEvent.mouseMove.y);
                break;

            case sf::Event::MouseButtonPressed:
                if(gameStatus)
                {
                    if(gameMenu.playText.getGlobalBounds().contains(transformVector<sf::Vector2i, sf::Vector2f>(sf::Mouse::getPosition(mainWindow))))
                    {
                        gameStatus = false;
                        Score = 0.f;
                        scoreClock.restart();
                        levelCounter = 0;
                        level = 1;
                        mainMusic.stop();
                        mainMusic.play();
                    }

                    else if(gameMenu.quitText.getGlobalBounds().contains(transformVector<sf::Vector2i, sf::Vector2f>(sf::Mouse::getPosition(mainWindow))))
                    {
                        mainMusic.stop();
                        mainWindow.close();
                    }
                }
                break;

            case sf::Event::KeyPressed:
                if(mainEvent.key.code == sf::Keyboard::Escape)
                {
                    if(gameStatus)
                        mainWindow.close();
                    else
                    {
                        gameStatus = true;
                        Enemies.clear();
                        levelCounter = 0;
                        level = 1;
                        Score = 0.f;
                    }
                }
				else if(mainEvent.key.code == sf::Keyboard::Space)
				{
				    sf::Image screenshotImage(mainWindow.capture());
					screenshotImage.saveToFile("screenshot.png");
				}
                break;

            default:
                break;

            }
        }
        if(gameStatus)
        {
            //Main Menu
            mainWindow.clear(sf::Color::Black);
            stars.Update();
            mainWindow.draw(stars.getSystem());
            mainWindow.draw(player);
            mainWindow.draw(gameMenu.titleText);
            mainWindow.draw(gameMenu.playText);
            mainWindow.draw(gameMenu.quitText);

            if(Score > 1.f)
            {
                std::string scoreString {std::to_string(Score)};
                scoreString = scoreString.substr(0, scoreString.find('.')+3);
                gameMenu.scoreText.setString("Score: " + scoreString);
                mainWindow.draw(gameMenu.scoreText);
                gameMenu.scoreText.setPosition(mainWindow.getSize().x/2 - gameMenu.scoreText.getGlobalBounds().width/2.f, (mainWindow.getSize().y/3)-gameMenu.scoreText.getGlobalBounds().height/2.f);
            }
            mainWindow.display();
        }

        else if(!gameStatus)
        {
            //Game
            if(levelClock.getElapsedTime().asMicroseconds()/1000.f > 1000.f/level)
            {
                int randomInt {getRandomInteger(-1,9)};
                levelClock.restart();
                auto AI = (randomInt >= 4 ? enemyAILine : enemyAISine);
                randomInt %= 4;
                sf::Vector2f target {static_cast<float>(getRandomInteger(0.f, static_cast<float>(mainWindow.getSize().x))), static_cast<float>(getRandomInteger(0.f, static_cast<float>(mainWindow.getSize().y)))};
                sf::Vector2f source = (randomInt < 2) ? ((randomInt == 0) ? sf::Vector2f {-20.f, static_cast<float>(getRandomInteger(0.f, static_cast<float>(mainWindow.getSize().y)))} :sf::Vector2f {static_cast<float>(mainWindow.getSize().x)+20.f, static_cast<float>(getRandomInteger(0.f, static_cast<float>(mainWindow.getSize().y)))}) :((randomInt == 3) ? sf::Vector2f {static_cast<float>(getRandomInteger(0, static_cast<float>(mainWindow.getSize().y))), -20.f} :
                sf::Vector2f {static_cast<float>(getRandomInteger(0.f, static_cast<float>(mainWindow.getSize().y))), static_cast<float>(mainWindow.getSize().x)+20.f});
                Enemies.emplace_back(new Enemy {sf::Color::White, source, target, AI});
                levelCounter++;
                if(levelCounter > level * 10)
                    level++;
            }

            mainWindow.setView(mainView);
            mainWindow.clear(sf::Color(0,0,0,255));

            incrementColor(enemyColor);

            for(unsigned int i = 0; i < Enemies.size(); ++i)
            {
                Enemies[i].get()->Update(gameClock.getElapsedTime().asMicroseconds()/1000.f);
                Enemies[i].get()->setColor(enemyColor);
                Enemies[i].get()->render(mainWindow);
                if(collides(Enemies[i].get()->getShape().getPosition(), player.getPosition()))
                {
                    gameStatus = true;
                    Enemies.clear();
                    levelCounter = 0;
                    Score = scoreClock.getElapsedTime().asMilliseconds()*level/1000.f;
                    level = 1;
                    break;
                }
                if(Enemies[i].get()->getShape().getPosition().x > mainWindow.getSize().x + 100 ||
                        Enemies[i].get()->getShape().getPosition().x < -100 ||
                        Enemies[i].get()->getShape().getPosition().y > mainWindow.getSize().y + 100 ||
                        Enemies[i].get()->getShape().getPosition().y < -100)
                {
                    Enemies.erase(Enemies.begin()+i);
                }
            }
            stars.Update();
            mainWindow.draw(stars.getSystem());
            std::string scoreString {std::to_string(scoreClock.getElapsedTime().asMilliseconds()*level/1000.f)};
            scoreString = scoreString.substr(0, scoreString.find('.')+3);

            textOverlay.setString(std::string {"Level: "} + std::to_string(level) +
                                  std::string {"\nScore: "}  + scoreString +
                                  std::string {"\nEntities: "} + std::to_string(Enemies.size()));
            mainWindow.draw(textOverlay);
            mainWindow.draw(player);
            mainWindow.display();

            sf::sleep(sf::milliseconds((1.f/fpsLimit)*1000.f - gameClock.getElapsedTime().asMicroseconds()/1000.f));
            gameClock.restart();
        }
    }
    return 0;
}
