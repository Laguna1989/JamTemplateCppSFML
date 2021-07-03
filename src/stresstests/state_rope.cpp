﻿#include "state_rope.hpp"
#include "drawable_helpers.hpp"
#include "game_interface.hpp"
#include "math_helper.hpp"
#include "shape.hpp"

RopeMass::RopeMass(jt::Vector2 pos, float m)
    : position { pos }
    , velocity { 0.0f, 0.0f }
    , acceleration { 0.0f, 0.0f }
    , mass { m }
    , fixed { false }
{
}

jt::Vector2 StateRope::getRopeMassPosition(int i) const
{
    return m_ropeStartingPoint + jt::Vector2 { 1.5f * i, 1.0f };
}

std::shared_ptr<RopeMass> StateRope::createRopeMassPointer(int i) const
{
    jt::Vector2 pos = getRopeMassPosition(i);
    auto r = std::make_shared<RopeMass>(pos, 1.0f);
    bool const isFirstRopeMass = i == 0;
    if (isFirstRopeMass) {
        r->fixed = true;
    }
    bool isLastRopeMass = i == 99;
    if (isLastRopeMass) {
        r->mass = 25.0f;
    }
    return r;
}

void StateRope::createSingleRopeMass(int i) { m_rope_elements.push_back(createRopeMassPointer(i)); }

void StateRope::createAllRopeMasses()
{
    for (int i = 0; i != 100; ++i) {
        createSingleRopeMass(i);
    }
}

void StateRope::doInternalCreate() { createAllRopeMasses(); }

void StateRope::resetAccelerations()
{
    for (auto& r : m_rope_elements) {
        r->acceleration = { 0.0f, 2.0f * r->mass };
    }
}

void StateRope::integrationStep(float elapsed)
{
    float const realElapsed = elapsed;
    for (auto& r : m_rope_elements) {
        if (!r->fixed) {
            r->velocity += realElapsed * r->acceleration;
            r->position += realElapsed * r->velocity;
        }
    }
}

void StateRope::calculateRopeForces()
{
    for (auto i = 0; i != m_rope_elements.size() - 1; ++i) {
        std::size_t idx1 = i;
        std::size_t idx2 = i + 1;

        auto r1 = m_rope_elements.at(idx1);
        auto r2 = m_rope_elements.at(idx2);

        auto springVector = r1->position - r2->position;
        float r = jt::MathHelper::length(springVector);

        if (r == 0) {
            continue;
        }
        jt::Vector2 force = -1.0f * (springVector / r) * (r - 1.75f) * m_springConstant;

        force += -10.0f * (r1->velocity - r2->velocity) * 0.9f;

        r1->acceleration += force / r1->mass;
        r2->acceleration -= force / r2->mass;
    }
}

void StateRope::doInternalUpdate(float elapsed)
{
    for (int i = 0; i != 7; ++i) {
        int const subdivide = 4;
        for (int i = 0; i != subdivide; ++i) {
            float const realElapsed = elapsed / subdivide;
            resetAccelerations();

            calculateRopeForces();
            for (auto& r : m_rope_elements) {
                r->velocity = r->velocity * 0.99995f;
            }

            integrationStep(realElapsed);
        }
    }
}

void StateRope::doInternalDraw() const
{
    for (auto const& r : m_rope_elements) {

        auto const p = r->position;
        auto s = jt::dh::createRectShape({ 2 * sqrt(r->mass), 2 * sqrt(r->mass) });
        s->setPosition(p);
        s->update(0.1f);
        s->draw(getGame()->getRenderTarget());
    }
}
