#ifndef COLLIDABLE_H
#define COLLIDABLE_H

class Component;
class Collidable
{
public:
    virtual ~Collidable() = default;

    virtual void onCollision(const Component &other) = 0;
};

#endif // COLLIDABLE_H
