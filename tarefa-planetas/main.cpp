#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>   // para gluPerspective, gluLookAt e gluQuadric
#include <math.h>
#include <iostream>

static float year = 0.0f, day = 0.0f;   // Ângulos de rotação
static bool animar = false;             // Controla se a animação está ligada

// Função para desenhar esferas em wireframe (sem GLUT)
void drawWireSphere(float radius, int slices, int stacks) {
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);   // wireframe
    gluSphere(quad, radius, slices, stacks);
    gluDeleteQuadric(quad);
}

// Inicializa parâmetros de rendering
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

// Função callback chamada para fazer o desenho
void display(GLFWwindow* window) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // posiciona a câmera
    gluLookAt(0.0, 2.0, 8.0,   // posição da câmera
              0.0, 0.0, 0.0,   // ponto para onde olha
              0.0, 1.0, 0.0);  // vetor "up"

    // Desenha o Sol
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        drawWireSphere(0.5, 20, 16);   /* desenha o sol */
    glPopMatrix();

    // Desenha Planeta 1 (gira para esquerda - anti-horário)
    glPushMatrix();
        glRotatef(year, 0.0, 1.0, 0.0);
        glTranslatef(2.0, 0.0, 0.0); // Translada a partir do novo sistema de coordenadas resultante da Rotacao
        glColor3f(0.0, 0.0, 1.0);
        drawWireSphere(0.2, 10, 8);    /* desenha um planeta */
    glPopMatrix();

    // Desenha Planeta 2 (gira para direita - horário)
    glPushMatrix();
        glRotatef(-year, 0.0, 1.0, 0.0);
        glTranslatef(3.5, 0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        drawWireSphere(0.3, 10, 8);    /* desenha o planeta 2 */

        // Lua 1 (orbita no eixo X)
        glPushMatrix();
            glRotatef(day, 1.0, 0.0, 0.0);
            glTranslatef(0.7, 0.0, 0.0);
            glColor3f(0.7, 0.7, 0.7);
            drawWireSphere(0.1, 8, 6);  /* desenha lua 1 */
        glPopMatrix();

        // Lua 2 (orbita no eixo XY)
        glPushMatrix();
            glRotatef(day, 1.0, 1.0, 0.0);
            glTranslatef(1.0, 0.0, 0.0);
            glColor3f(0.8, 0.8, 0.8);
            drawWireSphere(0.1, 8, 6);  /* desenha lua 2 */
        glPopMatrix();

    glPopMatrix();

    glfwSwapBuffers(window);
}

// Função chamada sempre que a janela é redimensionada
void reshape(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

// Callback de teclado
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_Y:  // ativa/desativa animação
                animar = !animar;
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
        }
    }
}

int main() {
    // Inicializa o GLFW
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar GLFW\n";
        return -1;
    }

    // Cria a janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "Rotacao de Planetas", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Inicializa o GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Falha ao inicializar GLEW\n";
        return -1;
    }

    init();

    glfwSetKeyCallback(window, keyboard);

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        if (animar) {
            year += 0.2f; if (year > 360.0f) year -= 360.0f;
            day  += 2.0f; if (day  > 360.0f) day  -= 360.0f;
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        reshape(window, width, height);

        display(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
