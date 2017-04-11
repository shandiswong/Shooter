#include <iostream>
#include <ngl/NGLStream.h>
#include <memory>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/Random.h>
#include <ngl/Obj.h>
#include <cmath>

#include "Enemy.h"
#include "EnemySpawn.h"
#include "EnemyWeak.h"
#include "Enemy.h"

EnemyWeak::EnemyWeak(std::shared_ptr<EnemySpawn> _spawnParent, ngl::Vec3 _pos, ngl::Vec3 _dir, const std::string &_shaderName)
    :Enemy(_spawnParent, _pos, _dir, _shaderName)
{
    std::cout<< " ******** EnemyWeak created........"<<std::endl;
    ngl::Random *rng=ngl::Random::instance();
    m_rotX=rng->randomNumber(360);
    m_rotZ=rng->randomNumber(360);
    m_rotUpdateX=rng->randomNumber(10);
    m_rotUpdateZ=rng->randomNumber(10);
    std::cout<<"_____ EnemyWeak class created" <<std::endl<<std::endl;
}

EnemyWeak::~EnemyWeak()
{
    std::cout<<"     EnemyWeak destroyed....." << std::endl;
}

TYPES EnemyWeak::getNameType() const
{
    return m_enemyNameType;
}

void EnemyWeak::update()
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

void EnemyWeak::setObjTex()
{
    m_enemyFiles.reset(new ngl::Obj("models/monster.obj","textures/strongtex.jpg"));
    m_enemyFiles->createVAO();
}

void EnemyWeak::draw()
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)[m_shaderName]->use();
    ngl::Transformation m_transformWeak;
    m_transformWeak.setPosition(m_pos);
    m_transformWeak.setRotation(m_rotX, 0, m_rotZ);
    ngl::Mat4 MVP = m_transformWeak.getMatrix() * m_spawnParent->getMouseView() * m_spawnParent->getCameraProjection()->getVPMatrix();
    shader->setShaderParamFromMat4("MVP", MVP);
    m_enemyFiles->draw();
}














