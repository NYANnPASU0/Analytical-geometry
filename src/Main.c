#include <stdio.h>
#include <math.h>
#include <float.h>
#include <windows.h>

typedef struct {
    double x, y, z;
} Point;


Point vector(Point from, Point to);
Point cross_product(Point a, Point b);
double dot_product(Point a, Point b);

void is_same_side(double A, double B, double C, double x1, double y1, double x2, double y2); //1
void intersection_vector(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy); //2
int is_point_inside_angle(Point A, Point B, Point C, Point D); //3
void is_same_space(double A, double B, double C, double D, double x1, double y1, double z1, double x2, double y2, double z2);//4

Point vector(Point from, Point to) {
    Point v;
    v.x = to.x - from.x;
    v.y = to.y - from.y;
    v.z = to.z - from.z;
    return v;
}

//векторное произведение
Point cross_product(Point a, Point b) {
    Point result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

//скалярное произведение
double dot_product(Point a, Point b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

//1
void is_same_side(double A, double B, double C, double x1, double y1, double x2, double y2)
{
    double check_1 = A * x1 + B * y1 + C;
    double check_2 = A * x2 + B * y2 + C;
    
    int on_line1 = 0;
    int on_line2 = 0;
    if (fabs(check_1) < DBL_EPSILON) on_line1 = 1;
    if (fabs(check_2) < DBL_EPSILON) on_line2 = 1;
    
    if (on_line1 && on_line2) 
    {
        printf("Точки A и B лежат на одной прямой");
    }
    else if (on_line1) 
    {
        printf("т. A лежит на прямой\n");
    }
    else if (on_line2) 
    {
        printf("т. B лежит на прямой\n");
    }
    else 
    {
        if (check_1 * check_2 > 0) 
        {
            printf("Точки A и B находятся по одну сторону\n");
        }
        else 
        {
            printf("Точки A и B находятся по разные стороны\n");
        }
    }
}

//2
void intersection_vector(double ax, double ay, double bx, double by,
                         double cx, double cy, double dx, double dy)
{   
    double cross1 = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
    double cross2 = (bx - ax) * (dy - ay) - (by - ay) * (dx - ax);
    
    if (fabs(cross1) > DBL_EPSILON || fabs(cross2) > DBL_EPSILON) {
        printf("Точки не лежат на одной прямой\n");
        return;
    }
    
    //AB - напр.вектор
    double vx = bx - ax;
    double vy = by - ay;
    //CD - напр.вектор
    double wx = dx - cx;
    double wy = dy - cy;
    
    //вырожденность
    if (fabs(vx) < DBL_EPSILON && fabs(vy) < DBL_EPSILON) {
        printf("Луч AB вырожден в точку A\n");
        double posA = (ax - cx)*wx + (ay - cy)*wy;
        if (posA >= -DBL_EPSILON) {
            printf("Точка A принадлежит лучу CD - лучи пересекаются\n");
        } else {
            printf("Лучи не пересекаются\n");
        }
        return;
    }
    
    if (fabs(wx) < DBL_EPSILON && fabs(wy) < DBL_EPSILON) {
        printf("Луч CD вырожден в точку C\n");
        double posC = (cx - ax)*vx + (cy - ay)*vy;
        if (posC >= -DBL_EPSILON) {
            printf("Точка C принадлежит лучу AB → лучи пересекаются\n");
        } else {
            printf("Лучи не пересекаются\n");
        }
        return;
    }
    
    // сонаправленность лучей
    double dot = vx*wx + vy*wy;
    //C относительно луча AB
    double posC = (cx - ax)*vx + (cy - ay)*vy;
    //A относительно луча CD
    double posA = (ax - cx)*wx + (ay - cy)*wy;
    
    printf("Направление AB: (%.2f, %.2f)\n", vx, vy);
    printf("Направление CD: (%.2f, %.2f)\n", wx, wy);
    printf("Скалярное произведение направлений: %.2f\n", dot);
    printf("Положение C относительно AB: %.2f\n", posC);
    printf("Положение A относительно CD: %.2f\n", posA);
    
    if (dot > DBL_EPSILON) {
        printf("Лучи сонаправлены\n");
        if (posC >= -DBL_EPSILON || posA >= -DBL_EPSILON) {
            printf("Лучи пересекаются\n");
            if (posC >= -DBL_EPSILON && posA >= -DBL_EPSILON) {
                // Оба начала лежат на противоположных лучах
                // Общая часть начинается от более удалённой точки
                if (posC > posA) {
                    printf("Общая часть: луч от C в направлении AB\n");
                } else {
                    printf("Общая часть: луч от A в направлении CD\n");
                }
            } else if (posC >= -DBL_EPSILON) {
                printf("Общая часть: луч от C в направлении AB\n");
            } else {
                printf("Общая часть: луч от A в направлении CD\n");
            }
        } else {
            printf("Лучи не пересекаются (разбегаются в разные стороны)\n");
        }
    }
    else if (dot < -DBL_EPSILON) {
        printf("Лучи противоположно направлены\n");
        
        if (posC >= -DBL_EPSILON && posA >= -DBL_EPSILON) {
            printf("Лучи пересекаются (смотрят друг на друга)\n");
            printf("Общая часть: отрезок [A, C]\n");
        }
        else if (posC >= -DBL_EPSILON) {
            printf("Лучи пересекаются (C лежит на AB)\n");
            printf("Общая часть: луч от C в направлении CD\n");
        }
        else if (posA >= -DBL_EPSILON) {
            printf("Лучи пересекаются (A лежит на CD)\n");
            printf("Общая часть: луч от A в направлении AB\n");
        }
        else {
            printf("Лучи не пересекаются\n");
        }
    }
}


//3
int is_point_inside_angle(Point A, Point B, Point C, Point D)
{
    Point BA = vector(B, A);
    Point BC = vector(B, C);
    Point BD = vector(B, D);

    //смешанное произведение
    Point v = cross_product(BA, BC);
    double is_compl = dot_product(v, BD);

     if (fabs(is_compl) > DBL_EPSILON) {
        printf("Точки не лежат в одной плоскости, соответственно т.D лежит вне угла ABC");
        return -1;
    }

    double sign1 = dot_product(cross_product(BA, BD), v);
    
    if (sign1 <= DBL_EPSILON) {
        printf("Точка НЕ лежит внутри угла ABC");
        return -1;
    }

    double sign2 = dot_product(cross_product(BC, BD), v);
    
    if (sign2 >= DBL_EPSILON) {
        printf("Точка НЕ лежит внутри угла ABC");
        return -1;
    }

    return 1;
}



//4
void is_same_space(double A, double B, double C, double D, double x1, double y1, double z1, 
    double x2, double y2, double z2)
{
    double check_1 = A*x1 + B*y1 + C*z1 + D;
    double check_2 = A*x2 + B*y2 + C*z2 + D;
    
    int on_plane1 = 0;
    int on_plane2 = 0;
    if (fabs(check_1) < DBL_EPSILON) on_plane1 = 1;
    if (fabs(check_2) < DBL_EPSILON) on_plane2 = 1;
    
    if (on_plane1 && on_plane2) 
    {
        printf("Точки A и B лежат на одной плоскости\n");
    }
    else if (on_plane1) 
    {
        printf("т. A лежит на плоскости\n");
    }
    else if (on_plane2) 
    {
        printf("т. B лежит на плоскости\n");
    }
    else 
    {
        if (check_1 * check_2 > 0) 
        {
            printf("Точки A и B находятся по одну сторону от плоскости\n");
        }
        else 
        {
            printf("Точки A и B находятся по разные стороны от плоскости\n");
        }
    }
}


int main() 
{    
    SetConsoleOutputCP(65001);
    int num;
    scanf("%d", &num);
    switch (num)
    {
        //Определить положение двух точек относительно прямой
        //по одну сторону от прямой, по разные, на прямой. Прямая задана своими коэффициентами
        case 1: 
        {
            double A, B, C, x1, y1, x2, y2;
            
            printf("Введите значения коэффициентов прямой A, B, C (Ax + By + C = 0)\n");
            scanf("%lf %lf %lf", &A, &B, &C);
            
            printf("Введите координаты точки A на плоскости (x1, y1)\n");
            scanf("%lf %lf", &x1, &y1);
            
            printf("Введите координаты точки B на плоскости  (x2, y2)\n");
            scanf("%lf %lf", &x2, &y2);
            
            is_same_side(A, B, C, x1, y1, x2, y2);
            break;
        }
        case 2:
        {
            double ax, ay, bx, by, cx, cy, dx, dy;
            
            printf("Enter the coordinates of the A point on the line (ax, ay)\n");
            scanf("%lf %lf", &ax, &ay);
            
            printf("Enter the coordinates of the B point on the line (bx, by)\n");
            scanf("%lf %lf", &bx, &by);
            
            printf("Enter the coordinates of the C point on the line (cx, cy)\n");
            scanf("%lf %lf", &cx, &cy);
            
            printf("Enter the coordinates of the D point on the line (dx, dy)\n");
            scanf("%lf %lf", &dx, &dy);
            
            //--------------
            break;
        }
        
        case 3:
        {
            Point A, B, C, D;
            printf("Введите координаты точки A в пространстве (x1, y1, z1)\n");
            scanf("%lf %lf %lf", &A.x, &A.y, &A.z);
            
            printf("Введите координаты точки B в пространстве (x2, y2, z2)\n");
            scanf("%lf %lf %lf", &B.x, &B.y, &B.z);
            
            printf("Введите координаты точки C в пространстве (x3, y3, z3)\n");
            scanf("%lf %lf %lf", &C.x, &C.y, &C.z);
            
            printf("Введите координаты точки D в пространстве (x4, y4, z4)\n");
            scanf("%lf %lf %lf", &D.x, &D.y, &D.z);

            if(is_point_inside_angle(A, B, C, D) == 1) printf("Точка D лежит внутри угла ABC");

            break;
        }
        
        case 4:
        {
            //Определить положение двух точек относительно плоскости
            //по одну сторону от плоскости, по разные, на плоскости.  Плоскость задана своими коэффициентами.
            double A, B, C, D, x1, y1, z1, x2, y2, z2;
            
            printf("Введите значения коэффициентов плоскости A, B, C, D (Ax + By + Cz + D = 0)\n");
            scanf("%lf %lf %lf %lf", &A, &B, &C, &D);
            
            printf("Введите координаты точки A в пространстве (x1, y1, z1)\n");
            scanf("%lf %lf %lf", &x1, &y1, &z1);
            
            printf("Введите координаты точки B в пространстве (x2, y2, z2)\n");
            scanf("%lf %lf %lf", &x2, &y2, &z2);
            
            is_same_space(A, B, C, D, x1, y1, z1, x2, y2, z2);
            break;
        }
        default:
            printf("Invalid task number\n");
    }
    return 0;
}