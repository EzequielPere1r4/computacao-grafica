#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "cata vento", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glewInit();

    float angulo = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 0.0f); 
        glRotatef(angulo, 0.0f, 0.0f, 1.0f);


        for (int i = 0; i < 4; i++) {
            glRotatef(90.0f, 0.0f, 0.0f, 1.0f); 
            glBegin(GL_TRIANGLES);
                glColor3f(1.0f, 0.3f, 0.5f); // cor da pétala
                glVertex2f(0.0f, 0.0f);       
                glVertex2f(0.2f, 0.5f);       
                glVertex2f(-0.2f, 0.5f);      
            glEnd();
        }

        // Miolo
        glColor3f(1.0f, 1.0f, 0.2f);
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(0.0f, 0.0f);
            for (int i = 0; i <= 20; i++) {
                float t = i * 2.0f * M_PI / 20;
                glVertex2f(cos(t) * 0.1f, sin(t) * 0.1f);
            }
        glEnd();

        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();

        angulo += 0.5f; 
        if (angulo > 360.0f) angulo -= 360.0f;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
