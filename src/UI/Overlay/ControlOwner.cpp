#include "ControlOwner.h"

ControlOwner::ControlOwner() : m_depthPrioritizedChildren{} {
}

void ControlOwner::update(float delta) {
    cacheControls();
    for(auto& control: m_cachedControls) {
        control->update(delta);
    }
}

bool ControlOwner::onEvent(sf::Event &e) {
    cacheControls();
    for(auto& control: m_cachedControls) {
        if(e.type == sf::Event::Resized && control->onEvent(e));
        else if(control->onEvent(e))
            return true;
    }
    return false;
}

void ControlOwner::draw(sf::RenderWindow &window) {
    cacheControls();
    for(auto& control: m_cachedControls) {
        control->draw(window);
    }
}

void ControlOwner::setDirty() {
    m_dirty = true;
}

void ControlOwner::cacheControls() {
    if(!m_dirty)
        return;

    m_cachedControls.clear();

    std::sort(m_depthPrioritizedChildren.begin(), m_depthPrioritizedChildren.end(),
            [](const auto& lhs, const auto& rhs){
                return lhs.first < rhs.first;
    });

    for(auto& [key, object]: m_depthPrioritizedChildren) {
        m_cachedControls.emplace_back(object.get());
    }

    m_dirty = false;
}

void ControlOwner::addChild(int depth, GameObject *go) {
    m_depthPrioritizedChildren.emplace_back(depth, std::unique_ptr<GameObject>());
    auto& [key, value] = m_depthPrioritizedChildren.back();
    value.reset(go);
    m_cachedMinDepth = std::min(depth, getMinDepth());
    m_cachedMaxDepth = std::max(depth, getMaxDepth());
    setDirty();
}

void ControlOwner::prependChild(GameObject *go) {
    addChild(getMinDepth() - 1, go);
}

void ControlOwner::appendChild(GameObject *go) {
    addChild(getMaxDepth() + 1, go);
}

const size_t ControlOwner::getNumChildren() const {
    return m_cachedControls.size();
}

int ControlOwner::getMinDepth() const {
    return m_cachedMinDepth;
}

int ControlOwner::getMaxDepth() const {
    return m_cachedMaxDepth;
}

void ControlOwner::onResize(sf::Event &resizeEvent) {
    GameObject::onResize(resizeEvent);
}
