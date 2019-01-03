//
//  Map.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 21/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "Component_Map.hpp"

using namespace std;

/*
MapComponent::MapComponent(ALLEGRO_FONT * font, int width, int height)
{
    this->width = width;
    this->height = height;
    map = new TileType[width * height];
    for(int i = 0; i < width * height; i++)
    {
        map[i] = TileType::Water;
    }
    this->font = font;
}


MapComponent::MapComponent(ALLEGRO_FONT * font, string fileName): font(font)
{
    //Open the file
    fstream file;
    file.open(fileName, ios::in);
    if(!file.is_open())
        throw std::runtime_error("Error : Unable to open file :"+ fileName);
    
    string rows, lines;

    getline (file,rows);
    getline (file,lines);
    
    this->width = std::stoi(rows);
    this->height = std::stoi(lines);
    
    map = new TileType[this->width * this->height];
    int currentPos = 0;
    char ch;
    
    while (EOF != (ch = file.get()))
    {
        if(ch != '\n')
        {
            
            if(ch == '`')
                map[currentPos] = TileType::Water;
            else if(ch=='M')
                map[currentPos] = TileType::Land;
            else if (ch =='T')
            {
                map[currentPos] = TileType::Town;
                townSystem->AddTownAtPosition(currentPos);
            }
            else
                map[currentPos] = TileType::Coast;
            
            currentPos++;
        }
    }
    
    file.close();
}
*/
//Component_Map::Component_Map(){}




