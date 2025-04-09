// Copyright [2025] Mohammed Ayan/ Ansh Patel
#include <string>
#include <iostream>
#include <fstream>
#include <SFML/System.hpp>
#include "EDistance.hpp"

int main(int argc, char* argv[]) {
    sf::Clock clock;

    EDistance ed("", "");
    std::cin >> ed;

    int distance = ed.optDistance();
    std::string align = ed.alignment();
    sf::Time t = clock.getElapsedTime();

    std::cout << "Edit Distance: " << distance << "\n";
    std::cout << align;
    std::cout << "Execution time is " << t.asSeconds() << " seconds" << std::endl;

    return 0;
}
