//
//  Components.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "Components.hpp"

Component_FontRenderer::Component_FontRenderer(ALLEGRO_FONT * font, char text, ALLEGRO_COLOR color)
:font(font), color(color)
{
    this->text[0] = text;
}

void Component_Transform::SetParent(ECS::Entity *parent)
{
    this->parent = parent;
    if(parent != nullptr)
        parent->GetComponent<Component_Transform>()->AddChildren(this->entity);
    
}

std::vector<ECS::Entity *> Component_Transform::GetChildren()
{
    return this->childs;
}

void Component_Transform::AddChildren(ECS::Entity * child)
{
    for(auto&& e : childs)
    {
        if(e == child)
            return;
    }
    this->childs.push_back(child);
    child->GetComponent<Component_Transform>()->SetParent(this->GetEntity());
}

void Component_Transform::RemoveChildren(ECS::Entity * child)
{
    for(auto it = childs.begin(); it != childs.end();)
    {
        if(*it == child)
        {
            childs.erase(it);
            return;
        }
        else
            ++it;
    }
}

void Component_Transform::RemoveAllChildren()
{
    for(auto it = childs.begin(); it != childs.end();)
    {
        (*it)->GetComponent<Component_Transform>()->parent = nullptr;
        childs.erase(it);
        ++it;
    }
}

int Component_Transform::GetPositionID() { 
    return (posX + (posY * 500));
}


//====================================================

Component_Town::Component_Town(int position) {
    this->position = position;
    this->name = "TEST";
    this->uiString = name;
}

Component_Town::Component_Town(int position, std::string name) {
    this->position = position;
    this->name = name;
    this->uiString = name;
}
