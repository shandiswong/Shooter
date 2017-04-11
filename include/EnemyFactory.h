#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H
#include <memory>
#include <iostream>
#include <ngl/Camera.h>

#include "Type.h"
#include "Enemy.h"
#include "EnemyWeak.h"
#include "EnemyStrong.h"
#include "EnemyFactory.h"
#include "Type.h"

class EnemySpawn; //predeclare

class EnemyFactory
{
public:
    EnemyFactory();
    ~EnemyFactory();

    //Create the enemy by choosing
    static std::unique_ptr<Enemy>createEnemyUnique(TYPES _nameType, ngl::Vec3 _pos, ngl::Vec3 _dir, const std::string &_shaderName, std::shared_ptr<EnemySpawn> _spawnParent);
    //Get enemy type
    static TYPES getEnemyType();

    //Get the VP, to get mvp
    void computeMVPfactory(ngl::Mat4 &_mouseView, std::shared_ptr<ngl::Camera> _camProjection);
    //Get obj and texture
    void getObjTex();

    void draw(); //testing
private:
    static TYPES m_nameType;
    static std::unique_ptr<Enemy>m_uEnemy;
    std::unique_ptr<Enemy>m_uEnemyData;

};

#endif // ENEMYFACTORY_H
