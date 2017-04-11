#ifndef ENEMYSTRONG_H
#define ENEMYSTRONG_H

#include <ngl/Obj.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <iostream>
#include <memory>
#include <ngl/Transformation.h>

#include "Enemy.h"
#include "Type.h"

class EnemyStrong: public Enemy
{
public:
    EnemyStrong(){std::cout<< "ENEMY STRONG DEFAULT CREATED!!@!£T^@!T@"<<std::endl;}
    EnemyStrong(std::shared_ptr<EnemySpawn>_spawnParent, ngl::Vec3 _pos, ngl::Vec3 _dir, const std::string &_shaderName);
    ~EnemyStrong();

    TYPES getNameType() const override;
    void draw() override;
    void update() override;
    void setObjTex() override;

private:
    TYPES m_enemyNameType = TYPES::STRONG_ENEMY;
    ngl::Transformation m_transform;
    float m_rotX;
    float m_rotUpdateX;
    float m_rotZ;
    float m_rotUpdateZ;
};


#endif // ENEMYSTRONG_H
