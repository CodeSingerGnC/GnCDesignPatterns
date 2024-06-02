// 反例：正方形不是长方形
#include <assert.h>

// 矩形
class Rectangle {
public:
    virtual void setWidth(int w) {
        width = w;
    }
    virtual void setHeight(int h) {
        height = h;
    }
    int getWidth() const {
        return width;
    }
    int getHeight() const {
        return height;
    }
    virtual int area() const {
        return width * height;
    }
protected:
    int width;
    int height;
};

// 正方形
class Square : public Rectangle {
public:
    void setWidth(int w) override {
        width = height = w;
    }
    void setHeight(int h) override {
        width = height = h;
    }
};

// 接口
void process(Rectangle& r) {
    r.setWidth(5);
    r.setHeight(4);
    assert(r.area() == 20); // 当 r 为 Square 时断言错误。
}

int main() {
    // 传递矩形对象
    Rectangle r;
    process(r); // 成功

    // 传递正方形对象
    Square s;
    process(s); // 失败

    return 0;
}