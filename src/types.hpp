//
//  Rect.hpp
//  AntiquityTrader
//
//  Created by Guillaume Collin on 23/12/2018.
//  Copyright © 2018 Sledge. All rights reserved.
//

#ifndef types_hpp
#define types_hpp

struct Vector2 {
    int x = 0, y = 0;
    
    Vector2* operator += (const Vector2& sum)   { this->x += sum.x; this->y += sum.y; return this; }
    Vector2  operator +  (const Vector2& sum)   { return Vector2 { this->x + sum.x, this->y + sum.y }; }
};

struct Rect {
    int x = 0, y = 0;
    int width = 0, height = 0;

};

#endif /* Rect_hpp */
