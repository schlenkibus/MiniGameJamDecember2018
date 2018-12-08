#pragma once
#include "../../GameObject.h"
#include <unordered_map>
#include <memory>

class ControlOwner : public GameObject {
public:
    ControlOwner();
    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
    void draw(sf::RenderWindow& window) override;

    void appendChild(GameObject* go);
    void prependChild(GameObject* go);
    void addChild(int depth, GameObject* go);
    const size_t getNumChildren() const;

protected:
    void onResize(sf::Event& resizeEvent) override;

    int getMinDepth() const;
    int getMaxDepth() const;
    void setDirty();
    void cacheControls();

    bool m_dirty = true;
    int m_cachedMaxDepth;
    int m_cachedMinDepth;

    std::vector<std::pair<int, std::unique_ptr<GameObject>>> m_depthPrioritizedChildren;
    std::vector<GameObject*> m_cachedControls;
};