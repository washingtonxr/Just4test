#include "classPack.h"
#include <iostream>
#include <assert.h>

using namespace std;
 
class Box
{
   public:
      double length;   // 长度
      double breadth;  // 宽度
      double height;   // 高度
      // 成员函数声明
      double get(void);
      void set( double len, double bre, double hei );
};
// 成员函数定义
double Box::get(void)
{
    return length * breadth * height;
}
 
void Box::set( double len, double bre, double hei)
{
    length = len;
    breadth = bre;
    height = hei;
}

int testClass(void)
{
    Box Box1;        // 声明 Box1，类型为 Box
    Box Box2;        // 声明 Box2，类型为 Box
    Box Box3;        // 声明 Box3，类型为 Box
    double volume = 0.0;     // 用于存储体积

    // box 1 详述
    Box1.height = 5.0; 
    Box1.length = 6.0; 
    Box1.breadth = 7.0;

    // box 2 详述
    Box2.height = 10.0;
    Box2.length = 12.0;
    Box2.breadth = 13.0;

    // box 1 的体积
    volume = Box1.height * Box1.length * Box1.breadth;
    cout << "Box1 的体积：" << volume <<endl;

    // box 2 的体积
    volume = Box2.height * Box2.length * Box2.breadth;
    cout << "Box2 的体积：" << volume <<endl;


    // box 3 详述
    Box3.set(16.0, 8.0, 12.0); 
    volume = Box3.get(); 
    cout << "Box3 的体积：" << volume <<endl;
    return 0;
}

class Box2
{
   public:
      double length;         // 长度
      double breadth;        // 宽度
      double height;         // 高度
 
      // 成员函数声明
      double getVolume(void);
      void setLength( double len );
      void setBreadth( double bre );
      void setHeight( double hei );
};
 
// 成员函数定义
double Box2::getVolume(void)
{
    return length * breadth * height;
}
 
void Box2::setLength( double len )
{
    length = len;
}
 
void Box2::setBreadth( double bre )
{
    breadth = bre;
}
 
void Box2::setHeight( double hei )
{
    height = hei;
}
 
// 程序的主函数
int testClass2(void)
{
   Box2 Box1;                // 声明 Box1，类型为 Box
   Box2 Box2;                // 声明 Box2，类型为 Box
   double volume = 0.0;     // 用于存储体积
 
   // box 1 详述
   Box1.setLength(6.0); 
   Box1.setBreadth(7.0); 
   Box1.setHeight(5.0);
 
   // box 2 详述
   Box2.setLength(12.0); 
   Box2.setBreadth(13.0); 
   Box2.setHeight(10.0);
 
   // box 1 的体积
   volume = Box1.getVolume();
   cout << "Box1 的体积：" << volume <<endl;
 
   // box 2 的体积
   volume = Box2.getVolume();
   cout << "Box2 的体积：" << volume <<endl;
   return 0;
}

class Box3
{
   public:
      double length;
      void setWidth( double wid );
      double getWidth( void );
 
   private:
      double width;
};
 
// 成员函数定义
double Box3::getWidth(void)
{
    return width ;
}
 
void Box3::setWidth( double wid )
{
    width = wid;
}

int privateClass(void)
{
   Box3 box;
 
   // 不使用成员函数设置长度
   box.length = 10.0; // OK: 因为 length 是公有的
   cout << "Length of box : " << box.length <<endl;
 
   // 不使用成员函数设置宽度
   // box.width = 10.0; // Error: 因为 width 是私有的
   box.setWidth(10.0);  // 使用成员函数设置宽度
   cout << "Width of box : " << box.getWidth() <<endl;
 
   return 0;
}

class Box4
{
   protected:
      double width;
      double length;
};
 
class SmallBox:Box4 // SmallBox 是派生类
{
   public:
      void setSmallWidth(double wid);
      void setSmallLength(double len);
      double getSmallWidth(void);
      double getSmallLength(void);
      double getArea(void);
};
 
// 子类的成员函数
double SmallBox::getArea(void)
{
    return width*length;
}

double SmallBox::getSmallWidth(void)
{
    return width ;
}

double SmallBox::getSmallLength(void)
{
    return length;
}
 
void SmallBox::setSmallWidth(double wid)
{
    width = wid;
}

void SmallBox::setSmallLength(double len)
{
    length = len;
}
 
// 程序的主函数
int protectClass(void)
{
    SmallBox box;

    // 使用成员函数设置宽度
    box.setSmallWidth(5.0);
    box.setSmallLength(3.3);
    cout << "Width of box : "<< box.getSmallWidth() << endl;
    cout << "Length of box: "<< box.getSmallLength() << endl;
    cout << "Area of box: "<< box.getArea() << endl;
    return 0;
}

class A{
    public:
        int a;
        A(){
            a1 = 1;
            a2 = 2;
            a3 = 3;
            a = 4;
        }
        void fun(){
            cout << a << endl;    //正确
            cout << a1 << endl;   //正确
            cout << a2 << endl;   //正确
            cout << a3 << endl;   //正确
        }
    public:
        int a1;
    protected:
        int a2;
    private:
        int a3;
};
class B : public A {
    public:
        int a;
        B(int i){
            A();
            a = i;
        }
        void fun(){
            cout << a << endl;       //正确，public成员
            cout << a1 << endl;       //正确，基类的public成员，在派生类中仍是public成员。
            cout << a2 << endl;       //正确，基类的protected成员，在派生类中仍是protected可以被派生类访问。
            //cout << a3 << endl;       //错误，基类的private成员不能被派生类访问。
        }
};

int publicInheritance(void)
{
    B b(10);
    cout << b.a << endl;
    cout << b.a1 << endl;   //正确
    //cout << b.a2 << endl;   //错误，类外不能访问protected成员
    //cout << b.a3 << endl;   //错误，类外不能访问private成员
    //system("pause");
    return 0;
}


/* End of this file. */
