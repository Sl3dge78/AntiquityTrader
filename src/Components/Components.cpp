//
//  Components.cpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 20/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#include "Components.hpp"

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
