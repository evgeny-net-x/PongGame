#include "../include/gameObject.h"

void GameObject::addChild(GameObject &child)
{
    m_children.push_back(&child);
}

GameObject *GameObject::findChild(std::string id)
{
    for(auto i = m_children.begin(); i != m_children.end(); ++i)
        if ((*i)->m_id == id)
            return *i;

    return nullptr;
}
