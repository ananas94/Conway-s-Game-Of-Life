#ifndef CGL_USERINPUT_H
#define CGL_USERINPUT_H

void mouseMotion(int x, int y);
void mouseClick(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void funcKeys(int key, int x, int y);
void init_user_input();
#endif