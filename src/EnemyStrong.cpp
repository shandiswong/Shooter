#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/Random.h>
#include <ngl/ShaderLib.h>
#include <cmath>
#include <ngl/Util.h>
#include <ngl/Transformation.h>
#include <ngl/Mat4.h>
#include <ngl/NGLStream.h>
#include <memory>
#include <ngl/Obj.h>

#include "EnemyStrong.h"
#include "EnemySpawn.h"
#include "Enemy.h"

EnemyStrong::EnemyStrong(std::shared_ptr<EnemySpawn> _spawnParent, ngl::Vec3 _pos, ngl::Vec3 _dir, const std::string &_shaderName)
    : Enemy(_spawnParent, _pos, _dir, _shaderName)
{
    std::cout<< " ******** EnemyStrong created........"<<std::endl;
    ngl::Random *rng=ngl::Random::instance();
    m_rotX=rng->randomNumber(360);
    m_rotZ=rng->randomNumber(360);
    m_rotUpdateX=rng->randomNumber(10);
    m_rotUpdateZ=rng->randomNumber(10);
    std::cout<<"_____ EnemyStrong class created" <<std::endl<<std::endl;
}


EnemyStrong::~EnemyStrong()
{
    std::cout<<"     EnemyStrong destroyed....." <<std::endl;
}



TYPES EnemyStrong::getNameType() const
{
    return m_enemyNameType;
}

void EnemyStrong::draw()
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)[m_shaderName]->use();
    ngl::Mat4 MVP;
    ngl::Transformation m_transformStrong;
    m_transformStrong.setPosition(m_pos);
    MVP = m_transformStrong.getMatrix() * m_spawnParent->getMouseView() * m_spawnParent->getCameraProjection()->getVPMatrix();
    shader->setShaderParamFromMat4("MVP", MVP);
    m_enemyFiles->draw();
}

void EnemyStrong::update()
{
    ngl::Random *rng=ngl::Random::instance();
    m_pos+=m_dir;
    m_pos = m_spawnParent->getPos();

    m_rotX+=m_rotUpdateX;
    m_rotZ+=m_rotUpdateZ;

    m_rotX=rng->randomNumber(360);
    m_rotUpdateX=rng->randomPositiveNumber(10);

    m_rotZ=rng->randomNumber(360);
    m_rotUpdateZ=rng->randomPositiveNumber(10);
}

void EnemyStrong::setObjTex() //use this for texture
{
    m_enemyFiles.reset(new ngl::Obj("models/monster.obj","textures/strongtex.jpg"));
    m_enemyFiles->createVAO();
}

