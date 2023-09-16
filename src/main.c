#include <raylib.h>
#include <point.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    const int WinWidth = 640;
    const int WinHeight = 480;
    List *points = NULL;
    List *conv = NULL;
    int x;
    int y;
    if((points=(List*)malloc(sizeof(List)))==NULL){
        perror("malloc error in main\n");
        exit(1);
    }
    list_init(points,free);
    Point *p = NULL;
    InitWindow(WinWidth,WinHeight,"convex hull");
    ClearBackground(BLACK);
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();

        if(IsKeyReleased(KEY_SPACE)){
            ClearBackground(BLACK);
            if(conv!=NULL){
                list_destroy(conv);
                free(conv);
                conv = NULL;
            }
            sort_points(points);
            conv = convex_hull(points);
            draw_all(points);
            if(conv!=NULL){
                draw_convex(conv);
            }
        }
        if(IsKeyReleased(KEY_R)){
            if(conv!=NULL){
                list_destroy(conv);
                free(conv);
                conv = NULL;
            }
            list_destroy(points);
            ClearBackground(BLACK);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            x = GetMouseX();
            y = GetMouseY();
            if((p=(Point*)malloc(sizeof(Point)))==NULL){
                perror("could not create point\n");
                exit(1);
            }
            p->x = x;
            p->y = y;
            list_ins_next(points,NULL,p);
            draw_point(p);
            printf("number of points: %d\n",points->size);
        }

        EndDrawing();
    }
    if(conv!=NULL){
        list_destroy(conv);
        free(conv);
        conv = NULL;
    }
    list_destroy(points);
    free(points);
    CloseWindow();
    return 0;
}