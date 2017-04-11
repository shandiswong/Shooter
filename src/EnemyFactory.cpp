#include "EnemyFactory.h"
#include "Enemy.h"
#include "EnemyStrong.h"
#include "EnemyWeak.h"
#include "EnemySpawn.h"
#include "Type.h"
#include <iostream>
#include <ngl/NGLStream.h>
#include <memory>

std::unique_ptr<Enemy>EnemyFactory::m_uEnemy;
TYPES EnemyFactory::m_nameType;

class EnemySpawn;

EnemyFactory::EnemyFactory()
{   
    std::cout<<"********************EnemyFactory class created" <<std::endl<<std::endl;
}

EnemyFactory::~EnemyFactory()
{
    std::cout<< "                    Destory EnemyFactory....." <<std::endl<<std::endl;
}

std::unique_ptr<Enemy> EnemyFactory::createEnemyUnique(TYPES _nameType, ngl::Vec3 _pos, ngl::Vec3 _dir, const std::string &_shaderName, std::shared_ptr<EnemySpawn> _spawnParent)
{
    std::cout<<"test check createEnemyUnique() is called!"<<std::endl;
    m_nameType = _nameType;

    if(_nameType == TYPES::STRONG_ENEMY)
    {
        std::cout<<"Test check createEnemyUnique() is called:::::::::: STRONG"<<std::endl;
        return std::unique_ptr<Enemy>(new EnemyStrong(_spawnParent, _pos, _dir, _shaderName));
    }
    else if(_nameType == TYPES::WEAK_ENEMY)
    {
        std::cout<<"Test check createEnemyUnique() is called:::::::::: WEAK"<<std::endl;
        return std::unique_ptr<Enemy>(new EnemyWeak(_spawnParent, _pos, _dir, _shaderName));
    }
    else return nullptr;
}

TYPES EnemyFactory::getEnemyType()
{
    return m_nameType;
}

void EnemyFactory::getObjTex()
{
    m_uEnemyData.reset(new EnemyStrong);
    m_uEnemyData.reset(new EnemyWeak);

    if(m_uEnemyData->getNameType() == TYPES::STRONG_ENEMY)
    {
        m_uEnemyData->setObjTex();
    }
    else if(m_uEnemyData->getNameType() == TYPES::WEAK_ENEMY)
    {

        m_uEnemyData->setObjTex();
    }
}

void EnemyFactory::draw()
{
    m_uEnemyData->draw();
}
