#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Vector {
    float x;
    float y;
};

struct Camera {
    Vector pos;
    Vector view_pos;
    float ang;
    float near_p;
    float far_p;
};

struct Line {
   Vector start;
   Vector end;
};

struct Frustum_lines {
    Line front, back, left, right;
};

struct Vector calc_frustum_lines(const struct Camera* camera) {
    double view_pos_x2 = camera->view_pos.x * camera->view_pos.x;
    double view_pos_y2 = camera->view_pos.y * camera->view_pos.y;

    struct Vector e_par;
    e_par.x = camera->view_pos.x / sqrtf(view_pos_x2 + view_pos_y2);
    e_par.y = camera->view_pos.y / sqrtf(view_pos_x2 + view_pos_y2);

    // —читаем координаты е_перпендикул€рного
    struct Vector e_per;
    e_per.x = e_par.y;
    e_per.y = -e_par.x;

    // —читаем точки трапеции
    float ang_rad = camera->ang * 3.1415926535 / 180.0; //перевод из градусов в радианы

    struct Vector a;
    a.x = camera->near_p * e_par.x + tanf(ang_rad / 2) * camera->near_p * e_per.x + camera->view_pos.x;
    a.y = camera->near_p * e_par.y + tanf(ang_rad / 2) * camera->near_p * e_per.y + camera->view_pos.y;

    struct Vector d;
    d.x = camera->near_p * e_par.x - tanf(ang_rad / 2) * camera->near_p * e_per.x + camera->view_pos.x;
    d.y = camera->near_p * e_par.y - tanf(ang_rad / 2) * camera->near_p * e_per.y + camera->view_pos.y;

    struct Vector b;
    b.x = camera->far_p * e_par.x + tanf(ang_rad / 2) * camera->far_p * e_per.x + camera->view_pos.x;
    b.y = camera->far_p * e_par.y + tanf(ang_rad / 2) * camera->far_p * e_per.y + camera->view_pos.y;

    struct Vector c;
    c.x = camera->far_p * e_par.x - tanf(ang_rad / 2) * camera->far_p * e_per.x + camera->view_pos.x;
    c.y = camera->far_p * e_par.y - tanf(ang_rad / 2) * camera->far_p * e_per.y + camera->view_pos.y;

    printf("Vector a: (%f, %f)\n", a.x, a.y);
    printf("Vector b: (%f, %f)\n", b.x, b.y);
    printf("Vector c: (%f, %f)\n", c.x, c.y);
    printf("Vector d: (%f, %f)\n", d.x, d.y);
   

    return a, b, c, d;
}

int main() {
    // ѕользовательский ввод параметров
    struct Camera camera;
    printf("Enter camera position (x y): ");
    scanf_s("%f %f", &camera.pos.x, &camera.pos.y);

    printf("Enter camera view direction (x y): ");
    scanf_s("%f %f", &camera.view_pos.x, &camera.view_pos.y);

    printf("Enter camera angle (in degrees): ");
    scanf_s("%f", &camera.ang);

    printf("Enter near plane distance: ");
    scanf_s("%f", &camera.near_p);

    printf("Enter far plane distance: ");
    scanf_s("%f", &camera.far_p);

    struct Vector result = calc_frustum_lines(&camera);

    return 0;
}
