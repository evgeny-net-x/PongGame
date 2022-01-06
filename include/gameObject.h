#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <vector>

class GameObject
{
public:
    const std::string m_id;
    std::vector<GameObject *> m_children;

    GameObject(std::string id): m_id(id) {}

    void addChild(GameObject &child);
    GameObject *findChild(std::string id);

	virtual void draw(void) = 0;
	virtual void update(float deltaSec) = 0;
};

#endif
