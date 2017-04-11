#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include <QMouseEvent>
#include <QGuiApplication>

#include <ngl/Camera.h>
#include <ngl/Text.h>
#include <ngl/Transformation.h>
#include <QOpenGLWindow>
#include "WindowParams.h"

#include <memory>
#include <iostream>

#include <ngl/Obj.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>

#include "EnemyWeak.h"
#include "EnemyStrong.h"
#include "EnemyFactory.h"
#include "Enemy.h"
#include "EnemySpawn.h"

class NGLScene : public QOpenGLWindow
{
    public:
        std::unique_ptr<Enemy>m_enemytry;
        NGLScene();
        ~NGLScene();
        void initializeGL();
        void paintGL();
        void resizeGL(int _w, int _h);
        void timerEvent( QTimerEvent *_event ); //timer event trigered by startTimer
        ngl::Camera m_modelCam;
        std::shared_ptr<ngl::Camera>m_cam;
        ngl::Mat4 m_mouse;

    private:
        WinParams m_win;                    // Windows params such as mouse and rotations etc

        //Shared
        std::unique_ptr<ngl::AbstractVAO> m_vao;
        std::shared_ptr<EnemyFactory>m_enemyFactoryShared; // Factory
        std::shared_ptr<EnemySpawn>m_spawnEnemyShared;     // Enemy spawn

        //Unique
        std::unique_ptr<EnemyFactory>m_uEnemyFactory;       // Factory
        std::unique_ptr<EnemySpawn> m_uEnemySpawn;          // Enemy spawn
        std::unique_ptr<ngl::Obj> m_uFiles;                 // Texture files

        ngl::Vec3 m_enemyPos;
        ngl::Vec3 m_enemyDir;
        ngl::Vec3 m_pos;
        ngl::Mat4 m_mouseGlobalTX;          // Store the global mouse transforms
        ngl::Transformation m_transform;    // Transformation stack for the gl transformations etc

        ngl::Vec3 m_modelPos;               // Model position for mouse movement
        std::string m_objFileName;
        std::string m_textureFileName;
        std::unique_ptr<ngl::Text> m_text;  // Text for rendering

        float m_rotX;
        float m_rotY;
        float m_rotZ;


    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *_event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseMoveEvent (QMouseEvent * _event );
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is pressed
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mousePressEvent ( QMouseEvent *_event);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseReleaseEvent ( QMouseEvent *_event );

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse wheel is moved
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void wheelEvent( QWheelEvent *_event);




};



#endif
