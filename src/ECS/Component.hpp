//
//  Component.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 17/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

namespace ECS
{
class Entity;

class Component {
    friend class Entity;
  public:
        Component() = default;
        virtual ~Component() = 0;
};
inline Component::~Component() = default;

// Used by entities to refer to components with an unique id
struct ComponentID
{
  public:
    template <class T>
    static const int Get() {
        static int id = count++;
        return id;
    }
  private:
    static int count;
};
}
#endif /* Component_hpp */
