#include "MyScene.h"
#include "Mat4.h"
Camera *MyScene::cam;
Texture *MyScene::texture;
Shader *MyScene::normalshader;
Shader *MyScene::noiseshader;
Shader *MyScene::postshader;
FBO *MyScene::post1;
FBO *MyScene::post2;
int MyScene::prevtime;
int MyScene::screentexture1;
bool MyScene::tex;
int MyScene::screentexture2;
float screenHeight = 1080;
float screenWidth = 1920;

/*
TODO: Rotation matrix should convert from degrees to radians. Make camera convert from radians to degrees

*/

void MyScene::reshape(int _width, int _height) {
	// update global dimension variables
	// calculate new aspect ratio
	GLdouble aspect = static_cast<GLdouble>(screenWidth) / static_cast<GLdouble>(screenHeight);
	//glMatrixMode(GL_PROJECTION);    // switch from model/view to projection mode    
	//glLoadIdentity();               // reset matrix
	//gluPerspective(72.0, aspect, 0.1, 1000);      // perspective
	//																				//  glOrtho(-width/2.f, width/2.f, -height/2.f, height/2.f, 1.f, camrad*2.f);       // orthographic
	//glMatrixMode(GL_MODELVIEW);     // return matrix mode to modelling and viewing !IMPORTANT!

}

void MyScene::mouseexit(int state) {
	if (state = GLUT_LEFT) {
		Input::grabMouse(screenWidth / 2, screenHeight / 2);
	}
	Input::grabMouse(screenWidth / 2, screenHeight / 2);
}

void MyScene::setMousePos(int x, int y) {
	Input::setMousePos(x, y);
}

void MyScene::windowSetup() {
	Input::init();
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);  // enable 3D rendering and double buffering
	glutInitWindowSize(screenWidth, screenHeight);              // set window size
	glutCreateWindow("My Scene");                   // create and show window (named MyScene)
}

void MyScene::setup() {
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glutPassiveMotionFunc(setMousePos);
	glutWarpPointer(screenWidth / 2, screenHeight / 2);
	glutEntryFunc(mouseexit);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutKeyboardFunc(Input::keyPressed);
	glutKeyboardUpFunc(Input::keyReleased);
	texture = new Texture();
	initObjects();
	prevtime = glutGet(GLUT_ELAPSED_TIME);
}
int texid;
//TODO: delete the objects
void MyScene::initObjects() {
	tex = 0;
	cam = new Camera(0, 0, 0, screenWidth, screenHeight, 72, 0.1, 100);

	normalshader = Shader::load("./shaders/ScreenSpace.vs", "./shaders/CellularAutomata.fs");

	
	post1 = new FBO(cam->getWidth(), cam->getHeight());
	screentexture1 = post1->colorTextureAttachment(0);
	post1->depthBufferAttachment();

	post2 = new FBO(cam->getWidth(), cam->getHeight());
	screentexture2 = post2->colorTextureAttachment(0);
	post2->depthBufferAttachment();

	postshader = Shader::load("./shaders/post.vs", "./shaders/post.fs");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	post2->bind();
	noiseshader = Shader::load("./shaders/ScreenSpace.vs", "./shaders/Noise.fs");
	noiseshader->bind();
	Mesh::indexCall(4);

}

void timer(int ms) {
	glutPostRedisplay();
	glutTimerFunc(ms, timer, ms);
}

float i = 0;

//Main loop of glut
void MyScene::draw() {
	int currtime = glutGet(GLUT_ELAPSED_TIME);
	float dt = currtime - prevtime;
	dt /= 1000.0;
	prevtime = currtime;
	if (Input::getKeyState('q')) {
		close();
	}
	cam->update(dt);
	
	if (tex) {
		post2->bind();
	} else {
		post1->bind();
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
	normalshader->bind();
	glActiveTexture(GL_TEXTURE0);
	if (tex) {
		glBindTexture(GL_TEXTURE_2D, screentexture1);
	} else {
		glBindTexture(GL_TEXTURE_2D, screentexture2);
	}
	normalshader->uniformi("screentexture", 0);
	normalshader->uniformVec2("dimensions", screenWidth, screenHeight);

	Mesh::indexCall(4);


	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	FBO::bindWindow(cam->getWidth(), cam->getHeight());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // clear buffers
	postshader->bind();
	glActiveTexture(GL_TEXTURE0);
	if (tex) {
		glBindTexture(GL_TEXTURE_2D, screentexture2);
	} else {
		glBindTexture(GL_TEXTURE_2D, screentexture1);
	}
	postshader->uniformi("screentexture", 0);

	Mesh::indexCall(4);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	checkGLError();
	glutSwapBuffers();                                  // execute all commands, swap buffers
	Input::update();
	tex = !tex;

}




void MyScene::close() {
	exit(0);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);          // Initialise GL environment
	MyScene::windowSetup();                      // Call additional initialisation commands
	glewInit();
	MyScene::setup();
	glutDisplayFunc(MyScene::draw);          // Register scene to render contents of draw() function
	MyScene::checkGLError();             // Check any OpenGL errors in initialisation
	glutReshapeFunc(MyScene::reshape);
	glutTimerFunc(16, timer, 16);
	glutMainLoop();                 // Begin rendering sequence
	return 0;
}

void MyScene::checkGLError() {
	int e = 0;                      // Error count
	GLenum error = glGetError();    // Get first glError
	while (GL_NO_ERROR != error)    // Loop until no errors found
	{
		e++;
		printf("GL Error %i: %s\n", e, gluErrorString(error)); // Display error string
		error = glGetError();                                  // Get next glError
	}
}