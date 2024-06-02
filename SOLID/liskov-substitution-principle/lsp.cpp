// 重新修改“正方形不是长方形”的继承关系
#include <iostream>

// 顶层抽象：形状
class Shape {
public:
    virtual int area() const = 0; 
};

// 长方形
class Rectangle : public Shape {
public:
    void setWidth(int w) {
        width = w;
    }
    void setHeight(int h) {
        height = h;
    }
    int area() const override {
        return width * height;
    }
private:
    int width;
    int height;
};

// 正方形
class Square : public Shape {
public:
    void setSide(int s) {
        side = s;
    }
    int area() const override {
        return side * side;
    }
private:
    int side;
};

// 接口
void process(Shape& s) {
    std::cout << "Area: " << s.area() << std::endl;
}

int main() {
    // process(矩形)
    Rectangle r;
    r.setWidth(5);
    r.setHeight(4);
    process(r); // 成功

    // process(正方形)
    Square s;
    s.setSide(5);
    process(s); // 成功

    return 0;
}