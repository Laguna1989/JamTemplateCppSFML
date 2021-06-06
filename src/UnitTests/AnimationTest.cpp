﻿#include "Animation.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(AnimationTest, AnimationCanBeDefaultConstructed)
{
    jt::Animation a;
    SUCCEED();
}

TEST(AnimationTest, AddAnimationWithOneFrame)
{
    jt::Animation a;
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
}

TEST(AnimationTest, AddAnimationWithMultipleFrame)
{
    jt::Animation a;
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0, 1, 2, 3 }, 1.0f);
}

TEST(AnimationTest, OverwriteAnimation)
{
    jt::Animation a;
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0, 1, 2, 3 }, 1.0f);
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
}
TEST(AnimationTest, AddAnimationWithEmptyNameRaisesInvalidArgumentException)
{
    jt::Animation a;
    EXPECT_THROW(
        a.add("assets/coin.png", "", { 16, 16 }, { 0, 1, 2, 3 }, 1.0f), std::invalid_argument);
}

TEST(AnimationTest, PlayInvalidAnimation)
{
    jt::Animation a;
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle2");
    a.update(0.0f);
    a.draw(nullptr);
}

TEST(AnimationTest, AddAnimationWithNegativeTimeRaisesInvalidArgumentException)
{
    jt::Animation a;
    EXPECT_THROW(
        a.add("assets/coin.png", "test", { 16, 16 }, { 0, 1, 2, 3 }, -0.5f), std::invalid_argument);
}

TEST(AnimationTest, ScaleSetsScale)
{
    jt::Animation a {};
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.setScale(jt::Vector2 { 100.0f, 100.0f });
    auto const result = a.getScale();
    EXPECT_FLOAT_EQ(result.x(), 100.0f);
    EXPECT_FLOAT_EQ(result.y(), 100.0f);
}

TEST(AnimationTest, SetPosition)
{
    jt::Animation a {};
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.setPosition(jt::Vector2 { 100.0f, 100.0f });
    auto const result = a.getPosition();
    EXPECT_FLOAT_EQ(result.x(), 100.0f);
    EXPECT_FLOAT_EQ(result.y(), 100.0f);
}

TEST(AnimationTest, SetOriginSetsOrigin)
{
    jt::Animation a {};
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.setOrigin(jt::Vector2 { 100.0f, 100.0f });
    auto const result = a.getOrigin();
    EXPECT_FLOAT_EQ(result.x(), 100.0f);
    EXPECT_FLOAT_EQ(result.y(), 100.0f);
}

TEST(AnimationTest, CanBeDrawnWithNullptrRenderTarget)
{
    jt::Animation a {};
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.update(0.1f);
    a.draw(nullptr);

    SUCCEED();
}

TEST(AnimationTest, SetFrontColor)
{
    jt::Animation a {};
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.setColor(jt::colors::Red);
    ASSERT_EQ(a.getColor(), jt::colors::Red);
}

TEST(AnimationTest, RotateHasNoEffect)
{
    jt::Animation a {};
    auto const angle = 22.0f;
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.setRotation(angle);
    EXPECT_FLOAT_EQ(a.getRotation(), angle);
}

TEST(AnimationTest, AnimationCanBeFlashed)
{
    jt::Animation a {};
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.flash(1.0f);
    SUCCEED();
}

TEST(AnimationTest, GetFlashColor)
{
    jt::Animation a {};
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.flash(1.0f, jt::colors::White);

    EXPECT_EQ(a.getFlashColor(), jt::colors::White);
}

TEST(AnimationTest, SetShadowGroup)
{
    jt::Animation a {};
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.setShadow(jt::colors::Black, { 3.0f, 3.0f });

    EXPECT_TRUE(a.getShadowActive());
    EXPECT_EQ(a.getShadowColor(), jt::colors::Black);
    EXPECT_EQ(a.getShadowOffset().x(), 3.0f);
    EXPECT_EQ(a.getShadowOffset().y(), 3.0f);
}

TEST(AnimationTest, SetShadowIndividual)
{
    jt::Animation a {};
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    a.play("idle");
    a.setShadowActive(true);
    a.setShadowColor(jt::colors::Black);
    a.setShadowOffset({ 3.0f, 3.0f });

    EXPECT_TRUE(a.getShadowActive());
    EXPECT_EQ(a.getShadowColor(), jt::colors::Black);
    EXPECT_EQ(a.getShadowOffset().x(), 3.0f);
    EXPECT_EQ(a.getShadowOffset().y(), 3.0f);
}
