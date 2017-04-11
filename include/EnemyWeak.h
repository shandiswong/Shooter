#ifndef ENEMYWEAK_H
#define ENEMYWEAK_H

#include <ngl/Obj.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <string>
#include <ngl/Transformation.h>

#include <iostream>
#include <memory>
#include "Enemy.h"
#include "Type.h"

class EnemyWeak : public Enemy
{
public:
    EnemyWeak(std::shared_ptr<EnemySpawn>_spawnParent, ngl::Vec3 _pos, ngl::Vec3 _dir, const std::string &_shaderName);
    EnemyWeak(){std::cout<< "ENEMY WEAK DEFAULT CREATED!!@!£T^@!T@"<<std::endl;}
    ~EnemyWeak();

    TYPES getNameType() const override;
    void draw() override;
    void update() override;
    void setObjTex() override;

private:
    TYPES m_enemyNameType = TYPES::WEAK_ENEMY;
    ngl::Transformation m_transform;

    float m_rotX; // position now
    float m_rotUpdateX; //increment rotation value

    float m_rotZ;
    float m_rotUpdateZ;



};
#endif // ENEMYWEAK_H
