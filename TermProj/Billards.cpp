

#include <windows.h>
#include <math.h>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <filesystem>
#include "GL/glui.h"
#include "glm/glm/vec3.hpp"
#include "glm/glm/vec4.hpp"

#include "shader.h"
#include "model.h"
#include "camera.h"
#include "Billard.h"
#include "textureloader.h"
#define PI 3.14159265359
//#include "objectloader.h"
//#include "textureloader.h"

static int main_window, win_width = 800, win_height = 800;
float angle;
//to hold our table object
float* vertexArray;
float* normalArray;
float* uvArray;
int numVerts;

Model ourModel;
Shader modelShader, lightingShader;
//canera

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = win_width / 2.0f;
float lastY = win_height / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
/* light contribution */
GLfloat  ambientLight[] = { 0.3, 0.3, 0.3, 0.0 };
GLfloat  diffuseLight[] = { 0.7, 0.7, 0.7, 0.0 };
GLfloat  specularLight[] = { 1.0, 1.0, 1.0, 0.0 };

/* two examples of specular contributions */
GLfloat  shiny_surface[] = { 1.0, 1.0, 1.0, 0.0 };

GLuint textures[16];
Billard ball[16];
glm::mat4 ballPos[16];
void init(void)
{
    
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glClearColor(1.0, 1.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    //loading object
    //glewExperimental = GL_TRUE;
    textures[0] = LoadTexture("Ball14180.bmp");
    
}
void display()
{
    float currentFrame = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // input
    // -----
    //processInput(window);

    // render
    // ------
   //for(int i = 0; i <100000; i++)
    //{
    //glClearColor(1.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        modelShader.use();
        //lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        //lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
       // lightingShader.setVec3("lightPos", lightPos);
        //lightingShader.setVec3("viewPos", camera.Position);

        // view/projection transformations
        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)win_width / (float)win_height, 0.1f, 100.0f);
        //glm::mat4 view = camera.GetViewMatrix();
        //lightingShader.setMat4("projection", projection);
       // lightingShader.setMat4("view", view);

        // world transformation
       //glm::mat4 model = glm::mat4(1.0f);
        //lightingShader.setMat4("model", model);
        
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)win_width / (float)win_height, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(1.0f, 0.0, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
    
        model = glm::rotate(model, (float)(PI/2), glm::vec3(1, 0, 0));
        //model = glm::rotate(model, (float)i/2000, glm::vec3(1, 0, 0));
        modelShader.setMat4("model", model);
        ourModel.Draw(modelShader);
        
        glm::mat4 balls = glm::mat4(1.0f);
        for (int i = 0; i < 16; i++)
        {
            ballPos[i] = glm::mat4(1.0f);
            
            //printf("deltaTime %f\n", deltaTime/1000);
            ball[i].timestep(deltaTime/1000);
            ballPos[i] = glm::translate(ballPos[i], ball[i].position);
            modelShader.setMat4("model", ballPos[i]);
            //model = glm::translate(model, glm::vec3(0.0f, -1.75f, 100.0f));
            ball[i].draw(textures[0]);
        }
        
        
        

        glutSwapBuffers();
        glutPostRedisplay();
   //}

}
void reshape(int w, int h)
{
    win_width = w;
    win_height = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 5.0, 10.0);

    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    //glMatrixMode(GL_VIEWPORT);
    //glLoadIdentity();
    //glRotatef(90, 0.0, 1.0, 0.0);
    //glRotatef(180, 0.0, 0.0, 1.0);
    //glTranslatef(-1.0, 0.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
    //glRotatef(90, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    main_window = glutCreateWindow(argv[0]);
    
    init();
    //main_window = glutCreateWindow("gui");
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    modelShader = Shader("model_shader.vs", "model_shader.fs");
    //lightingShader = Shader("lighting_shader.vs", "lighting_shader.fs");
    //ourModel = Model(("resources/models/pooltbl.obj"));
    ourModel = Model(("resources/models/pooltbl.obj"));
    
    for (int i = 0; i < 16; i++) {
        ball[i].velocity.x = (float)i / 50;
        ball[i].velocity.y = (float)i / 50;
    }
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutMouseFunc(mouse);
    //glutKeyboardFunc(keyboard);



 
    glutMainLoop();
    return 0;
}
