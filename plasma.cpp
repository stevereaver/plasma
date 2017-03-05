#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    float value;
    float value1;
    float value2;
    // Setup something similar to Amiga display mode
    const int WIN_SZ_W = 320;
    const int WIN_SZ_H = 256;
    const int ORIGIN_X = WIN_SZ_W/2;
    const int ORIGIN_Y = WIN_SZ_H;
    float distance;
    float time;
    const float PI = 3.141;
    const float TAU = 2*PI;
    int norm_value;

    sf::RenderWindow window(sf::VideoMode(WIN_SZ_W, WIN_SZ_H), "Plasma!");

    //Create and image the same size as the window
    sf::Image image;
    sf::Color color;
    color.a=0;
    image.create(WIN_SZ_W,WIN_SZ_H,color);
    //draw stuff into image
    for (int y=0;y<WIN_SZ_H;y++){
          for (int x=0;x<WIN_SZ_W;x++) {
            //Do a simple horizontal sinus
            value1 = (sin(x/40.74));
            //use pythagorus to find the distance to the origin point
            distance = sqrt(((ORIGIN_X-x)*(ORIGIN_X-x))+((ORIGIN_Y-y)*(ORIGIN_Y-y)));
            //Sinus the distance from the origin
            value2 = (sin(distance/40.74));
            // Add the two together and normalize to 256
            value = ((value1 + value2)*64)+128;
            //cout << value << "\n";
            image.setPixel(x, y, {value,value,value});
          }
    }
    //Make sprite out of the image
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Modify the plasma over time
        if (time>TAU*100) time = 1;
        time=time+0.07;
        for (int y=0;y<WIN_SZ_H;y++){
          for (int x=0;x<WIN_SZ_W;x++) {
            //Do a simple horizontal sinus
            //value1 = (sin(x/40.74+time));
            value1 = sin((x*sin(time/2)+y*cos(time/3))/40.74+time*2);
            //use pythagorus to find the distance to the origin point
            distance = sqrt(((ORIGIN_X-x)*(ORIGIN_X-x))+((ORIGIN_Y-y)*(ORIGIN_Y-y)))+1;
            //Sinus the distance from the origin
            value2 = (sin(distance/40.74))+time;
            // Add the two together and normalize to 256
            value = value1 + value2;
            norm_value = ((value1 + value2)*64)+128;

            //cout << value << "\n";
            //color.r=128+sin(value)+128;
            //color.g=128+cos(value)*128;
            //color.b=128+sin(value)*128;
            //image.setPixel(x, y, {128+sin(value*PI)+128, 128+sin(value*PI+TAU/3)*128, 128+sin(value*PI+4*PI/3)*128});
            image.setPixel(x, y, {128+sin(value*PI)*127,128+cos(value*PI)*127,0});
          }
        }
        texture.update(image);


        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
