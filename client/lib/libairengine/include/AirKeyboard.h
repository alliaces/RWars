#ifndef		AIRKEYBOARD_H_
# define	AIRKEYBOARD_H_

#include <SFML/Window.hpp>
#include <iostream>

class AirKeyboard
{
 public:
  AirKeyboard() {}
  ~AirKeyboard() {}
  static const std::string &initMap(int key)
  {
    static std::map<int, std::string> keys_ = {{0, "a"},
					       {1, "b"},
					       {2, "c"},
					       {3, "d"},
					       {4, "e"},
					       {5, "f"},
					       {6, "g"},
					       {7, "h"},
					       {8, "i"},
					       {9, "j"},
					       {10, "k"},
					       {11, "l"},
					       {12, "m"},
					       {13, "n"},
					       {14, "o"},
					       {15, "p"},
					       {16, "q"},
					       {17, "r"},
					       {18, "s"},
					       {19, "t"},
					       {20, "u"},
					       {21, "v"},
					       {22, "w"},
					       {23, "x"},
					       {24, "y"},
					       {25, "z"},
					       {26, "0"},
					       {27, "1"},
					       {28, "2"},
					       {29, "3"},
					       {30, "4"},
					       {31, "5"},
					       {32, "6"},
					       {33, "7"},
					       {34, "8"},
					       {35, "9"},
					       {36, " "},
					       {sf::Keyboard::Key::BackSpace, "\b"},
					       {sf::Keyboard::Key::Numpad0, "0"},
					       {sf::Keyboard::Key::Numpad1, "1"},
					       {sf::Keyboard::Key::Numpad2, "2"},
					       {sf::Keyboard::Key::Numpad3, "3"},
					       {sf::Keyboard::Key::Numpad4, "4"},
					       {sf::Keyboard::Key::Numpad5, "5"},
					       {sf::Keyboard::Key::Numpad6, "6"},
					       {sf::Keyboard::Key::Numpad7, "7"},
					       {sf::Keyboard::Key::Numpad8, "8"},
					       {sf::Keyboard::Key::Comma, ","},
					       {sf::Keyboard::Key::Numpad9, "9"},
					       {sf::Keyboard::Key::SemiColon, "."}};
    return (keys_[key]);
  }
};

#endif
