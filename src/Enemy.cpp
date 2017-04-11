#include "Enemy.h"
#include "EnemySpawn.h"

#include <iostream>
#include <ngl/Camera.h>
#include <ngl/Random.h>

Enemy::Enemy(std::shared_ptr<EnemySpawn> _spawnParent, ngl::Vec3 _pos, ngl::Vec3 _dir, const std::string &_shaderName)
{
    std::cout<<"__________ Enemy class created" <<std::endl<<std::endl;

    m_spawnParent = std::shared_ptr<EnemySpawn>(new EnemySpawn);
    m_spawnParent = _spawnParent;
    m_enemyFiles.reset(new ngl::Obj);
    m_pos = _pos;
    m_dir = _dir;
    m_shaderName = _shaderName;
    std::cout<<"Enemy SHARED CREATED..." <<std::endl;
}


Enemy::~Enemy()
{
    std::cout<<"                    Enemy destroyed....." <<std::endl;
}

