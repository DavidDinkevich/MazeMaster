#include <SFML/Graphics.hpp>
#include "engine.hpp"

using namespace std;
using namespace sf;

int main() {
//    Engine e(sf::Vector2f(8 * 110, 6 * 110), 60);
//    e.run();
    // LOAD FONT
    Font defaultFont;
    if (!defaultFont.loadFromFile("resources/arial.ttf")) {
        cout << "ERROR\n";
    }

    MainWindow mainWindow(60, defaultFont);
    mainWindow.run();


    return 0;
}
