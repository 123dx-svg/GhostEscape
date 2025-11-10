#pragma once

//#define DEBUG_MODE//调试宏

enum class ObjectType
{
    NONE,
    OBJECT_SCREEN,
    OBJECT_WORLD,
    ENEMY
};
//锚点
enum class Anchor {
    NONE,
    TOP_LEFT,
    TOP_RIGHT,
    TOP_CENTER,
    CENTER_LEFT,
    CENTER_RIGHT,
    CENTER,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    BOTTOM_CENTER
};
