#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
    AirButton *button = new AirButton(new AirPicture("ressource/Sprite_logo.png"), new AirPicture("ressource/Ok-icon.png"),
    	Vector2u(100,100), Vector2u(50,50),
    	new AirFont("ressource/pricedown bl.ttf"));
    button->setText("yolo", sf::Color::Red, 15);
    this->check = new AirCheckBox(new AirPicture("ressource/Sprite_logo.png"), new AirPicture("ressource/Ok-icon.png"),
    	Vector2u(10,10), Vector2u(50,50));

    AirText *simpleText = new AirText(new AirFont("ressource/pricedown bl.ttf"),
        "plop",
        Vector2u(200, 200),
        sf::Color::Black,
        30);

    AirTextBox *textBox = new AirTextBox(new AirPicture("ressource/textbox.png"),
        Vector2u(300, 300),
        Vector2u(50, 50),
        new AirFont("ressource/pricedown bl.ttf"));

    simpleText->setTextString("plop2");
    simpleText->setColor(sf::Color::White);
    simpleText->setCharacterSize(50);
    textBox->setText("", sf::Color::Blue, 15);
	this->AddEntity(button);
    this->AddEntity(check);
    this->AddEntity(simpleText);
    this->AddEntity(textBox);
    button->onClickHandler(this);
    AirParticuleGenerator* part = new AirParticuleGenerator(Vector2f(0.0f, 1.0f),0.5, Vector2f(0.0f, -1.5), 0.1, sf::Color::Blue, 0, sf::Color(250,0,0,50), 0, 1, 3, 10000, 0, 20, Vector2u(500,500), 2);
    AirParticuleGenerator* part2 = new AirParticuleGenerator(Vector2f(0.0f, 1.0f),0.5, Vector2f(0.0f, -1.5), 0.1, sf::Color::Blue, 0, sf::Color(250,0,0,50), 0, 1, 3, 10000, 0, 20, Vector2u(450,500), 2);
    AirParticuleGenerator* part3 = new AirParticuleGenerator(Vector2f(0.0f, 1.0f),0.5, Vector2f(0.0f, -1.5), 0.1, sf::Color::Blue, 0, sf::Color(250,0,0,50), 0, 1, 3, 10000, 0, 20, Vector2u(400,500), 2);
AirParticuleGenerator* part4 = new AirParticuleGenerator(Vector2f(-1.3f, 0.0f),0.1, Vector2f(-1.3f, 0.0f), 0.1, sf::Color(255,255,255,255), 0, sf::Color(255,255,255,255), 0, 1, 3, 20000, 0, 10, Vector2u(1400,400), 400);
    this->AddParticules(part3);
    this->AddParticules(part);
    this->AddParticules(part2);
    this->AddParticules(part4);
}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::OnInit()
{

}

void MainMenu::OnRender()
{
}

void MainMenu::OnResize(Vector2u wsize)
{
  (void)wsize;
}

// tmp method
void MainMenu::OnClick(void *)
{
    std::cout << "isCheck -> " << check->getIsChecked() << std::endl;
}
