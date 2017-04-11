#include <QMouseEvent>
#include <QGuiApplication>
#include <QFont>
#include "NGLScene.h"
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Transformation.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <memory>
#include <iostream>
#include <ngl/NGLStream.h>
#include <ngl/Random.h>


#include "EnemySpawn.h"


  NGLScene::NGLScene()
  {

    //std::unique_ptr<NGLScene>m_scene(new NGLScene);

    std::cout<<std::endl<<std::endl;
    std::cout<<"______________________________ NGLSCENE class created ______________________" <<std::endl<<std::endl;
    setTitle("Obj Demo");
    m_objFileName =  std::string ("models/monster.obj");
    m_textureFileName= std::string ("textures/monster_body.jpg");

    m_enemyPos.set(0,0,0);
    m_enemyDir.set(0,0,0);

    ngl::Mat4 mouse;
    m_cam = std::shared_ptr<ngl::Camera>(new ngl::Camera);

  }


  NGLScene::~NGLScene()
  {
    std::cout<<std::endl<<std::endl;
    std::cout<<"........................... NGLScene Destory ...........................  " <<std::endl;
  }

  void NGLScene::resizeGL( int _w, int _h )
  {
    m_cam->setShape( 45.0f, static_cast<float>( _w ) / _h, 0.05f, 350.0f );
    m_win.width  = static_cast<int>( _w * devicePixelRatio() );
    m_win.height = static_cast<int>( _h * devicePixelRatio() );
  }

  void NGLScene::timerEvent(QTimerEvent *_event)
  {
      m_uEnemySpawn->update();
      update();
  }


  void NGLScene::initializeGL()
  {
    // we must call this first before any other GL commands to load and link the
    // gl commands from the lib, if this is not done program will crash
    ngl::NGLInit::instance();

    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
    // enable depth testing for drawing
    glEnable(GL_DEPTH_TEST);
    // enable multisampling for smoother drawing
    glEnable(GL_MULTISAMPLE);


    //==================================== CAMERA ====================================

    // Now we will create a basic Camera from the graphics library
    // This is a static camera so it only needs to be set once
    // First create Values for the camera position
    ngl::Vec3 from(0,10,8);//                                                      //
    ngl::Vec3 to(0,0,0);  //   This is to determine where the camera is facing    //
    ngl::Vec3 up(0,1,0);  //                                                      //
    m_cam->set(from,to,up);
    // set the shape using FOV 45 Aspect Ratio based on Width and Height
    // The final two are near and far clipping planes of 0.5 and 10
    m_cam->setShape(45.0f,720.0f/576.0f,0.05f,350.0f);
    //================================================================================




    //==================================== SHADER ====================================

    //=========(1):   Create a singleton pattern of an instance to say "IT'S SET-UP SHADER TIME!"
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();

    //=========(2):   Create the program hypershade
    // (*ALONE*)
    shader->createShaderProgram("TextureShader");

    //-----------------------------------------------------------------------------
    //=========(3):   What shader to use? Lambert/Blinn? But it's VERTEX OR FRAGMENT in glsl
    // (*ALONE*)
    shader->attachShader("TextureVertex",ngl::ShaderType::VERTEX);
    shader->attachShader("TextureFragment",ngl::ShaderType::FRAGMENT);

    //=========(4):   Import the file to shader, just like choosing the diffuse file
    // (*ALONE*)
    shader->loadShaderSource("TextureVertex","shaders/TextureVertex.glsl");
    shader->loadShaderSource("TextureFragment","shaders/TextureFragment.glsl");

    //=========(5):   Now compile/glue the shader to the source file
    //(*TOGETHER*) shader + source file = finalshader
    shader->compileShader("TextureVertex");
    shader->compileShader("TextureFragment");

    //-----------------------------------------------------------------------------
    //=========(6):   Add that final shader to the hypershade program!
    //(*TOGETHER*) hypershadeprogram += finalshader
    shader->attachShaderToProgram("TextureShader","TextureVertex");
    shader->attachShaderToProgram("TextureShader","TextureFragment");
    //-----------------------------------------------------------------------------
    //=========(7):   Assign shader to object!!
    shader->linkProgramObject("TextureShader");
    //=========(8):   Use the program. Tells program "I want to activate you now, USE!!"
    (*shader)["TextureShader"]->use();
    //===============================================================================




    //===================================== VIEWPORT ================================
    // as re-size is not explicitly called we need to do this.
    glViewport(0,0,width(),height());
    //===============================================================================

    //===================================== TEXT ========================================
    m_text.reset(new ngl::Text(QFont("Arial",16)));
    m_text->setScreenSize(width(),height());
    m_text->setColour(1,1,1);
    //===============================================================================

    m_enemyPos.set(0,0,0);
    m_enemyDir.set(0,0,0);

    m_uEnemySpawn.reset(new EnemySpawn(m_enemyPos, m_enemyDir, 15, m_cam)); //from here I must know what enemy is being spawn so then I can set the texture to the appropiate!
    m_uEnemySpawn->getObjTex(); // from inside enemy class ..... BUNDLE A
    //m_uEnemySpawn->initFiles(); //set the texture now ............ BUNDLE B

    startTimer(40);
  }


  void NGLScene::paintGL()
  {
    // clear the screen and depth buffer
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     ngl::Random *rng = ngl::Random::instance();
     rng->setSeed(20);


     //============================= POSITION ROTATION ===============================

     //   P.S  all this will be loaded to the loadMatricesToShader() then to frag shader


     //(1):     Detects where the mouse cursor is at upon first click and release.
     ngl::Mat4 rotX;
     ngl::Mat4 rotY;
     rotX.rotateX(m_win.spinXFace);  // create the rotation matrices for X
     rotY.rotateY(m_win.spinYFace);  // create the rotation matrices for Y

     //(2):     Multiply the rotations , ok Rotation done
     m_mouseGlobalTX = rotY * rotX;

     //(3):     Add the translations,  fill the translation of xyz on the matrix4x4

     m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x ;
     m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y ;
     m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z ;

    //============================= START DRAWING =====================================

     //(1.):   Create a singleton ShaderLib
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    //ngl::VAOPrimitives *prim = ngl::VAOPrimitives::instance();

    //(2):     Use the shader program
    (*shader)["TextureShader"]->use();

    //(3):     Load in all the position of transform and rotation
    m_transform.reset();

    //(4):     DRAW: Get the V and P then draw
    //m_uEnemySpawn->computeFinalMVP(m_mouseGlobalTX, m_cam);   //works together... BUNDLE B
    //m_uEnemySpawn->drawTest(); //DRAW now                     //works together.... BUNDLE B
    m_uEnemySpawn->draw(); //DRAW now .........BUNDLE A
//line 197 is the problem...Segmentation fault there!
    //===================================================================================


    // Draw text
    m_text->renderText(10,18,"The thingy");
    update();
  }

  //----------------------------------------------------------------------------------------------------------------------

  void NGLScene::keyPressEvent(QKeyEvent *_event)
  {
    // this method is called every time the main window recives a key event.
    // we then switch on the key value and set the camera in the GLWindow
    switch (_event->key())
    {
    // escape key to quite
    case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
    // turn on wirframe rendering
    case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
    // turn off wire frame
    case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
    // show full screen
    case Qt::Key_F : showFullScreen(); break;
    // show windowed
    case Qt::Key_Space :
          m_win.spinXFace=0;
          m_win.spinYFace=0;
          m_modelPos.set(ngl::Vec3::zero());
    break;
    default : break;
    }
    // finally update the GLWindow and re-draw
    update();
  }
