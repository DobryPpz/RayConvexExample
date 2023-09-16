#include <point.h>

double points_angle(Point *p1, Point *p2){
    return (atan2(p2->y-p1->y,p2->x-p1->x));
}
int point_dir(Point *p1, Point *p2, Point *p3){
    return (p1->x*p2->y+p1->y*p3->x+p2->x*p3->y)-(p2->y*p3->x+p1->x*p3->y+p1->y*p2->x);
}
int sort_points(List *points){
    Point **point_arr = NULL;
    Point *temp = NULL;
    Point *pivot = NULL;
    int size = points->size;
    int gap;
    double angle_a;
    double angle_b;
    bool swapped;
    if((point_arr=(Point**)calloc(sizeof(Point*),points->size))==NULL){
        perror("malloc error\n");
        return -1;
    }
    for(int i=0;i<size;i++){
        list_rem_next(points,NULL,(void**)&point_arr[i]);
    }
    for(int i=1;i<size;i++){
        if(point_arr[i]->y < point_arr[0]->y){
            temp = point_arr[0];
            point_arr[0] = point_arr[i];
            point_arr[i] = temp;
        }
        else if(point_arr[i]->y == point_arr[0]->y && point_arr[i]->x < point_arr[0]->x){
            temp = point_arr[0];
            point_arr[0] = point_arr[i];
            point_arr[i] = temp;
        }
    }
    pivot = point_arr[0];
    gap = size;
    swapped = true;
    while(gap>1 || swapped){
        gap = gap*10/13;
        if(gap==0){
            gap = 1;
        }
        swapped = false;
        for(int i=1;i+gap<size;i++){
            angle_a = points_angle(pivot,point_arr[i]);
            angle_b = points_angle(pivot,point_arr[i+gap]);
            if(angle_b < angle_a){
                temp = point_arr[i];
                point_arr[i] = point_arr[i+gap];
                point_arr[i+gap] = temp;
                swapped = true;
            }
        }
    }
    for(int i=0;i<size;i++){
        list_ins_next(points,points->tail,point_arr[i]);
    }
    free(point_arr);
    return 0;
}
List *convex_hull(List *points){
    if(points->size<3){
        return NULL;
    }
    List *stack = NULL;
    Point *c = NULL;
    Point *temp = NULL;
    ListElmt *traverser = NULL;
    if((stack=(List*)malloc(sizeof(List)))==NULL){
        perror("malloc error\n");
        return NULL;
    }
    list_init(stack,NULL);
    for(traverser=points->head;traverser!=NULL;traverser=traverser->next){
        c = (Point*)traverser->data;
        while(stack->size>1 && point_dir((Point*)stack->head->next->data,(Point*)stack->head->data,c)<=0){
            list_rem_next(stack,NULL,(void**)&temp);
        }
        list_ins_next(stack,NULL,c);
    }
    return stack;
}
void draw_convex(List *convex){
    Point *start = (Point*)convex->head->data;
    Point *from = start;
    Point *to = NULL;
    ListElmt *traverser = NULL;
    for(traverser=convex->head->next;traverser!=NULL;traverser=traverser->next){
        to = (Point*)traverser->data;
        connect_points(from,to);
        from = to;
    }
    connect_points(start,to);
}
Point *new_point(int x, int y){
    Point *p = NULL;
    if((p=(Point*)malloc(sizeof(Point)))==NULL){
        perror("malloc error\n");
        return NULL;
    }
    p->x = x;
    p->y = y;
    return p;
}
void add_point(List *points, Point *point){
    list_ins_next(points,points->tail,point);
}
void connect_points(Point *p1, Point *p2){
    DrawLineEx((Vector2){p1->x,p1->y},(Vector2){p2->x,p2->y},2,SKYBLUE);
}
void draw_point(Point *point){
    DrawCircle(point->x,point->y,4,SKYBLUE);
}
void draw_all(List *points){
    ListElmt *traverser = NULL;
    Point *p = NULL;
    for(traverser=points->head;traverser!=NULL;traverser=traverser->next){
        p = (Point*)traverser->data;
        draw_point(p);
    }
}
void clear_points(List *points){
    list_destroy(points);
}