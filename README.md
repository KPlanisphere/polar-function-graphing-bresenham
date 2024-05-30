# Polar Function Graphing (Bresenham Algorithm)

### Description
This project, completed as part of the coursework at the Benemérita Universidad Autónoma de Puebla, focuses on graphing a polar function using the Bresenham algorithm in the Code::Blocks IDE. The aim is to visualize a polar function, specifically a Rose Curve, while optimizing computational efficiency through the use of the Bresenham line algorithm.

### Overview
The Bresenham algorithm is a precise and efficient method for generating rasterized lines using only integer calculations. It can be adapted to display circles and other curves, making it suitable for plotting polar functions with reduced computational cost.

### Objectives
- Implement and visualize a polar function using the Bresenham algorithm in OpenGL.
- Apply learned concepts to optimize graph plotting by minimizing floating-point operations.
- Develop an understanding of the Bresenham algorithm and its applications in computer graphics.

### Key Features
- **Initialization**: Set up the OpenGL environment and window properties.
- **Bresenham Algorithm**: Calculate and plot points efficiently using integer calculations.
- **Graphing Function**: Convert polar coordinates to Cartesian coordinates and plot the Rose Curve.
- **Color Variation**: Implement a color scheme for visual distinction.

### Project Structure
The project includes the following main components:

#### Initialization
This function sets up the OpenGL environment, defining the color of the window and the projection parameters.

```cpp
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
```

#### Bresenham Algorithm

This function implements the Bresenham algorithm to efficiently determine the points to be plotted for a given line segment.

```cpp
void Bresenham(int x0, int y0, int x1, int y1) {
    int x, y, dx, dy, p, incE, incNE, stepx, stepy;
    dx = (x1 - x0);
    dy = (y1 - y0);
    if (dy < 0) {
        dy = -dy; stepy = -1;
    } else {
        stepy = 1;
    }
    if (dx < 0) {
        dx = -dx; stepx = -1;
    } else {
        stepx = 1;
    }
    x = x0;
    y = y0;
    glBegin(GL_POINTS);
    glVertex2i(x0, y0);
    glEnd();
    if (dx > dy) {
        p = 2 * dy - dx;
        incE = 2 * dy;
        incNE = 2 * (dy - dx);
        while (x != x1) {
            x = x + stepx;
            if (p < 0) {
                p = p + incE;
            } else {
                y = y + stepy;
                p = p + incNE;
            }
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }
    } else {
        p = 2 * dx - dy;
        incE = 2 * dx;
        incNE = 2 * (dx - dy);
        while (y != y1) {
            y = y + stepy;
            if (p < 0) {
                p = p + incE;
            } else {
                x = x + stepx;
                p = p + incNE;
            }
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }
    }
}
``` 

#### Graphing Function

This function draws the graph by converting polar coordinates to Cartesian coordinates and utilizes the Bresenham algorithm to plot lines between calculated points.

```cpp
void dibujaGrafica() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the display window

    GLfloat rpolar, angulo, diff;
    GLint xt, yt, x0, y0, x1, y1, first;
    first = 1;
    glPointSize(1);
    diff = 360 / 120;

    for (i = 0; i < 240; i++) {
        rpolar = 6 * cos(4 * rad);  // Rose Curve formula
        xt = rpolar * cos(rad) * 25;
        yt = rpolar * sin(rad) * 25;

        glColor3f(0.255, 0, 0.700);  // Set color

        if (first == 1) {  // First point
            x0 = xt;
            y0 = xt;
            x1 = xt;
            y1 = xt;
            first = 0;
        } else {  // Subsequent points
            x0 = x1;
            y0 = y1;
            x1 = xt;
            y1 = yt;
            if (i > 1) {
                Bresenham(x0, y0, x1, y1);
            }
        }
        angulo = angulo + diff;
        rad = angulo * (M_PI / 180);
    }
    glFlush();
}
```

#### Main Function

This function initializes the graphics window and starts the main loop.

```cpp
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Curva Rosa (Bresenham)");
    init();
    glutDisplayFunc(dibujaGrafica);
    glutMainLoop();

    return 0;
}
```

### Execution

The project initializes a graphical window and plots a Rose Curve using the Bresenham algorithm. This approach reduces computational costs by minimizing floating-point operations, resulting in an efficient and accurate graph plotting.

<p align= "center">
    <img src="https://github.com/KPlanisphere/binary-tree-operations/assets/60454942/f621bf61-811c-4d30-897f-2ad8147b401a" style="width: 70%; height: auto;">
</p>
