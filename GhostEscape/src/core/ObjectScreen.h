#pragma once
#include "Object.h"

class ObjectScreen : public Object
{
protected:
    glm::vec2 render_position = glm::vec2(0.0f, 0.0f);  //渲染屏幕位置
    

public:
    void init() override;
    virtual  glm::vec2 getRenderPosition() {return  render_position;}
    virtual  void setRenderPosition(const glm::vec2& pos) {render_position = pos;}
    virtual  glm::vec2 getPosition() const {return glm::vec2(0);}

};
