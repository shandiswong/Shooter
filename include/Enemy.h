#ifndef ENEMY_H
#define ENEMY_H

#include <ngl/Obj.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <string.h>
#include <iostream>
#include <memory>
#include <ngl/Camera.h>
#include <ngl/Mat4.h>

#include "Enemy.h"
#include "Type.h"

class EnemySpawn; //predeclare

class Enemy
{
public:
    Enemy(std::shared_ptr<EnemySpawn>_spawnParent, ngl::Vec3 _pos, ngl::Vec3 _dir, const std::string &_shaderName);
    Enemy(){std::cout<< "ENEMY DEFAULT CREATED!!@!£T^@!T@"<<std::endl;}
    virtual ~Enemy();

    virtual TYPES getNameType() const = 0;
    virtual void draw()  =0;
    virtual void update() = 0;
    virtual void setObjTex() = 0;

protected:
    ngl::Vec3 m_pos;
    ngl::Vec3 m_dir;
    std::string m_shaderName;
    //THE V AND P
    std::shared_ptr<ngl::Camera> m_camProjection;
    ngl::Mat4 m_mouseView;
    //Obj and Tex information
    std::unique_ptr<ngl::Obj>m_enemyFiles;
    //Shared pointer (Must be shared to access SAME thing in NGLscene later)
    std::shared_ptr<EnemySpawn>m_spawnParent;
};


#endif // ENEMY_H
