//JESUS HUERTA AGUILAR - FACULTAD DE CIENCIAS DE LA COMPUTACION BUAP

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <cmath>  //para operar con las funciones trigonometricas

GLfloat sizep;
int i,j;
float angulo = 0,rad = 0;

void init(void){
    //Establece el color de la ventana de visualizacion
    //Los tres primeros parametros corresponden al RGB
    //El cuarto parametro corresponde al valor alfa, que permite el efecto de transparencias
    //0: objeto totalmente transparente; 1: objeto totalmente opaco
    glClearColor(0.0, 0.0, 0.0, 1.0); //FONDO NEGRO
    //establece los parametros de proyeccion ortogonal
    //Se visualizara una proyeccion bidimensional de dimensiones 200 x 150
    //(0,0): esquina inferior izquierda: punto de referencia de esta ventana
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200,200,-200,200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Bresenham(int x0, int y0, int x1, int y1){
    int x, y, dx, dy, p, incE, incNE, stepx, stepy;
    dx = (x1 - x0);
    dy = (y1 - y0);
    /* determinar que punto usar para empezar, cual para terminar */
    if (dy < 0) {
        dy = -dy; stepy = -1;
      }
    else
      stepy = 1;
    if (dx < 0) {
        dx = -dx; stepx = -1;
      }
    else
      stepx = 1;
    x = x0;
    y = y0;

    glBegin(GL_POINTS);
        glVertex2i(x0,y0);
    glEnd();
     /* se cicla hasta llegar al extremo de la línea */
      if(dx>dy){
        p = 2*dy - dx;
        incE = 2*dy;
        incNE = 2*(dy-dx);
        while (x != x1){
          x = x + stepx;
          if (p < 0){
            p = p + incE;
          }
          else {
            y = y + stepy;
            p = p + incNE;
          }
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        }
      }
      else{
        p = 2*dx - dy;
        incE = 2*dx;
        incNE = 2*(dx-dy);
        while (y != y1){
          y = y + stepy;
          if (p < 0){
            p = p + incE;
          }
          else {
            x = x + stepx;
            p = p + incNE;
          }
        glBegin(GL_POINTS);
            glVertex2i(x,y);
        glEnd();
        }
      }
 }

void dibujaGrafica(){
    glClear(GL_COLOR_BUFFER_BIT);  //borra la ventana de visualizacion
    //glColor3f(0.0, 0.0, 0.0);      //establece que lo que se dibuja sera rojo
    GLfloat rpolar,angulo,diff;
    GLint xt,yt,x0,y0,x1,y1,first,bandera;
    //MUESTRA GRAFICA
    bandera = 0;
    first = 1;
    glPointSize(1);
    diff = 360/120;
    for (i=0;i<120;i++){
        rpolar = 6*cos(4*rad);  //donde a = longitud del petalo y n = 4 (r = a*cos(n*theta))
        xt = rpolar*cos(rad)*(25);
        yt = rpolar*sin(rad)*(25);

        glColor3f(0.255, 0, 0.700);

        //IMPRESION DE RECTAS
        if(first == 1){//PRIMER PUNTO
            x0 = xt;
            y0 = xt;
            x1 = xt;
            y1 = xt;
            first = 0;
        }
        else{//DEMAS PUNTOS
            x0 = x1;
            y0 = y1;

            x1 = xt;
            y1 = yt;
            if(i > 1){
                Bresenham(x0,y0,x1,y1);
            }
        }
        angulo = angulo + diff;
        rad = angulo*(M_PI/180);
    }
    //se obliga a procesar todas las instrucciones de openGL tan rapidamente como sea posible
    glFlush();
}

int main(int argc, char** argv){
    //se inicializa la pantalla grafica
    glutInit(&argc, argv);
    //establece el modo de visualizacion
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    //Establece la posicion de la esquina superior izquierda del grafico en la pantalla
    glutInitWindowPosition(100,100);
    //se establece el ancho y la altura de la ventana de visualizacion
    glutInitWindowSize(400,400);
    //se crea la ventana de visualizacion
    glutCreateWindow("Curva Rosa (Bresenham)");
    //se ejecuta la funcion de inicializacion de parametros
    init();
    //se envian los graficos a pantalla
    glutDisplayFunc(dibujaGrafica);
    glutMainLoop();

    return 0;
}
