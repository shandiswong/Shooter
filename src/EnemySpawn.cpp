#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <ngl/Camera.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/Random.h>

#include "EnemyFactory.h"
#include "EnemySpawn.h"
#include "EnemyWeak.h"
#include "Type.h"

class EnemyFactory;

EnemySpawn::EnemySpawn()
{
    m_factoryUnique.reset(new EnemyFactory);
    std::cout<<" EnemySpawn class is created THIS IS DEFAULT!"<<std::endl;
}

EnemySpawn::~EnemySpawn()
{
    std::cout<<"               DESTROY EnemySpawn class....."<<std::endl;
    //Clear the vector container
    m_enemies.clear();
}

EnemySpawn::EnemySpawn(ngl::Vec3 _pos, ngl::Vec3 _dir, unsigned int _numOfEnemies, std::shared_ptr<ngl::Camera>_camProjection)
{
    std::cout<<"******************************EnemySpawn class is created!"<<std::endl;

     //Randoms
    ngl::Random *rng=ngl::Random::instance();

    //CREATE A FACTORY, pick which enemies to spawn
    m_factoryUnique.reset(new EnemyFactory);

    //SETTERS
    m_pos = _pos;
    m_dir = _dir;
    m_camProjection = _camProjection;
    m_numOfEnemies = _numOfEnemies;
    m_enemies.resize(m_numOfEnemies); //Size of vector container to loop through later
    ngl::Vec3 dir;


    int enemySwitch;
    //Spawn enemies
    for(auto &enemy : m_enemies) //for each enemy in vector ENEMIES container...do something
    {      
        dir = rng->getRandomVec3();
        dir.normalize();
        enemySwitch = (int)rng->randomPositiveNumber(2);

        switch(enemySwitch)
        {
        case 0:
             enemy = m_factoryUnique->createEnemyUnique(TYPES::STRONG_ENEMY, _pos, _dir, "TextureShader", std::shared_ptr<EnemySpawn>(new EnemySpawn));
            whichenemy = "strong";
            break;

        case 1:
              enemy = m_factoryUnique->createEnemyUnique(TYPES::WEAK_ENEMY, _pos, _dir, "TextureShader", std::shared_ptr<EnemySpawn>(new EnemySpawn));
            whichenemy = "weak";
            break;
        }
    }
}


void EnemySpawn::computeFinalMVP(ngl::Mat4 &_mouseView, std::shared_ptr<ngl::Camera> _camProjection)
{
    m_camProjection = _camProjection;
    m_mouseView = _mouseView;
}

//STATIC FUNCTION
void EnemySpawn::initFiles() //This works but I want to use getObjTex()
{
    m_factoryUnique.reset(new EnemyFactory);

    if(m_factoryUnique->getEnemyType() == TYPES::STRONG_ENEMY)
    {
        std::cout<<"Strong enemy texture loaded!"<<std::endl;
        //Texture and create texture
        m_files.reset(new ngl::Obj("models/monster.obj","textures/strongtex.jpg"));
        m_files->createVAO();
    }
    else if(m_factoryUnique->getEnemyType() == TYPES::WEAK_ENEMY)
    {
        std::cout<<"Weak enemy texture loaded!"<<std::endl;
        //Texture and create texture
        m_files.reset(new ngl::Obj("models/weakmonster.obj","textures/weaktex.jpg"));
        m_files->createVAO();
    }
    else
    {
        std::cerr<<"Obj files and texture files did not load properly!!!!!!!!!!!!"<<std::endl;
    }
}

void EnemySpawn::getObjTex()
{
    m_factoryUnique.reset(new EnemyFactory);
    m_factoryUnique->getObjTex();
}

void EnemySpawn::draw()
{ 
    for(auto &e : m_enemies)
    {
        e->draw();
    }
}

void EnemySpawn::drawTest()
{
   ngl::ShaderLib *shader=ngl::ShaderLib::instance();
   ngl::Random *rng = ngl::Random::instance();
   rng->setSeed(20);

    if(m_factoryUnique->getEnemyType() == TYPES::STRONG_ENEMY)
    {

       //  for(int i=0; i<m_enemies.size(); i++) //vector is here
        //{
            std::cout<<"Strong enemy MVP sucess!"<<std::endl;
            (*shader)["TextureShader"]->use();
            m_rotX = rng->randomNumber(3);
            m_rotZ = rng->randomNumber(3);
            m_transformStrong.setPosition(ngl::Vec3(m_rotX, 0,  m_rotZ));
            ngl::Mat4 MVP = m_transformStrong.getMatrix() * m_mouseView * m_camProjection->getVPMatrix();
            shader->setShaderParamFromMat4("MVP", MVP);
            m_files->draw();
       // }
    }
    else if(m_factoryUnique->getEnemyType() == TYPES::WEAK_ENEMY)
    {
            std::cout<<"Weak enemy MVP sucess!"<<std::endl;
           // for(int i=0; i<m_enemies.size(); i++)
            //{
               (*shader)["TextureShader"]->use();
                m_rotX = rng->randomNumber(3);
                m_rotZ = rng->randomNumber(3);
                m_transformWeak.setPosition(ngl::Vec3(m_rotX, 0,  m_rotZ));
                ngl::Mat4 MVP = m_transformWeak.getMatrix() * m_mouseView * m_camProjection->getVPMatrix();
                shader->setShaderParamFromMat4("MVP", MVP);
                m_files->draw();
           // }
    }
    else
    {
        std::cerr<<"MVP not loaded!!!!!!!!!"<<std::endl;
    }
}

void EnemySpawn::update()
{
    for(auto &enemy : m_enemies)
    {
        enemy->update();
    }
}

void EnemySpawn::clearEnemies()
{
    m_enemies.clear();
    m_numOfEnemies = 0;
}

void EnemySpawn::removeEnemy()
{
    if(m_numOfEnemies > 0)
    {
        m_enemies.pop_back();
        --m_numOfEnemies;
    }
}

void EnemySpawn::addEnemy(TYPES _nameType)
{
    //Create factory
    m_factoryUnique.reset(new EnemyFactory);
    ngl::Random *rng=ngl::Random::instance(); //Random instance

    ngl::Vec3 _dir;
    _dir = rng->getRandomVec3();
    m_enemies.push_back(std::unique_ptr<Enemy>(m_factoryUnique->createEnemyUnique(_nameType, m_pos, _dir, "TextureShader", std::shared_ptr<EnemySpawn>())));

    ++m_numOfEnemies;
}

ngl::Mat4 EnemySpawn::getMouseView()
{
    return m_mouseView;
}

ngl::Vec3 EnemySpawn::getPos()
{
    return m_pos;
}


std::shared_ptr<ngl::Camera> EnemySpawn::getCameraProjection()
{
    return m_camProjection;
}


void EnemySpawn::setPos(const ngl::Vec3 &_pos)
{
    m_pos=_pos;
}

unsigned int EnemySpawn::getNumEnemies() const
{
    return m_numOfEnemies;
}
