#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    const int width  = 60;
    const int height = 30;

    const double cx = width / 2.0;
    const double cy = height / 2.0;
    const double radius = 12.0;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            // distance from center
            double dx = x - cx;
            double dy = y - cy;
            double dist = std::sqrt(dx * dx + dy * dy);

            // normalized intensity
            double intensity = 1.0 - (dist / radius);

            if (intensity > 0.8)
                std::cout << std::setw(2) << "@";
            else if (intensity > 0.6)
                std::cout << std::setw(2) << "#";
            else if (intensity > 0.4)
                std::cout << std::setw(2) << "*";
            else if (intensity > 0.2)
                std::cout << std::setw(2) << ".";
            else
                std::cout << std::setw(2) << " ";
        }
        std::cout << '\n';
    }

    return 0;
}