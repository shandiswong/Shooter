#ifndef ENEMYSPAWN_H
#define ENEMYSPAWN_H

#include <iostream>
#include <vector>
#include <typeinfo>
#include <memory>
#include <ngl/Camera.h>
#include <ngl/Random.h>
#include <ngl/Obj.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <string>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>

#include "Enemy.h"
#include "Type.h"
#include "EnemyFactory.h"


class EnemyFactory;

class EnemySpawn
{
public:
    EnemySpawn();
    virtual ~EnemySpawn();
    EnemySpawn(ngl::Vec3 _pos, ngl::Vec3 _dir, unsigned int _numOfEnemies, std::shared_ptr<ngl::Camera> _camProjection);

    //GETTERS
    inline unsigned int getNumEnemies()const ;
    //Load texture and file. CreateVAO
    void initFiles();
    void getObjTex();
    //Calculate MVP
    void computeFinalMVP(ngl::Mat4 &_mouseView, std::shared_ptr<ngl::Camera> _camProjection);
    void draw();
    void drawTest();

    void update();
    void clearEnemies();
    void removeEnemy();
    void addEnemy(TYPES _nameType);



    //GET:  FUNCTIONS: Camera PROJECTION and Mouse VIEW (should be in enemy actually..)
    std::shared_ptr<ngl::Camera>getCameraProjection();
    ngl::Mat4 getMouseView();


    //GET : Positions
    ngl::Vec3 getPos();
    //SET
    inline void setPos(const ngl::Vec3 &_pos);
    float m_rotX;
    float m_rotY;
    float m_rotZ;

private:

    ngl::Transformation m_transformWeak;
    ngl::Transformation m_transformStrong;
    unsigned int m_numOfEnemies;
    int m_chooseEnemy;
    std::string whichenemy;

    //Unique to Vector: Pointers stored in vector container
    std::vector < std::unique_ptr<Enemy> > m_enemies;
    //Unique
    std::unique_ptr<EnemyFactory>m_factoryUnique;


    // MVP calculation (MUST HAVE)
    std::shared_ptr<ngl::Camera>m_camProjection;
    ngl::Mat4 m_mouseView;


    //Enemy informations
    ngl::Vec3 m_pos;
    ngl::Vec3 m_dir;
    //Obj and Tex informations
    std::string m_objFile;
    std::string m_texFile;
    std::unique_ptr<ngl::Obj>m_files;
    std::unique_ptr<ngl::Obj>m_theData;

};

#endif // ENEMYSPAWN_H
