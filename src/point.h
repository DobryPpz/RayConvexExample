#ifndef POINT_H_
#define POINT_H_
#include <list.h>
#include <raylib.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Point{
    int x;
    int y;
}Point;

double points_angle(Point *p1, Point *p2);
int point_dir(Point *p1, Point *p2, Point *p3);
int sort_points(List *points);
List *convex_hull(List *points);
void draw_convex(List *convex);
Point *new_point(int x, int y);
void add_point(List *points, Point *point);
void connect_points(Point *p1, Point *p2);
void draw_point(Point *point);
void draw_all(List *points);
void clear_points(List *points);

#endif