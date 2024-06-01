// C++ 11
#include<string>
#include<vector>
#include<iostream>
using namespace std;

// Product 的定义
enum class Color { Red, Green, Yellow };
enum class Size { Small, Medium, Large };
struct Product {
    string name;
    Color color;
    Size size;
};


// 规范
template <typename T> 
struct Specification
{
    virtual bool is_satisfied(T* item) = 0;
};

// 过滤器
template <typename T> 
struct Filter 
{
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) const = 0;
};

// Product 过滤器
struct BetterFilter: Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) const override {
        vector<Product*> result;
        for(auto& p: items) {
            if(spec.is_satisfied(p)) {
                result.push_back(p);
            }
        }
        return result;
    }
};

// 颜色筛选规范
struct ColorSpecification : Specification<Product>
{
    Color color;
    explicit ColorSpecification(const Color& color) : color(color) {}
    bool is_satisfied(Product* item) override {
        return item->color == color;
    }
};

// 大小筛选规范
struct SizeSpecification : Specification<Product>
{
    Size size;
    explicit SizeSpecification(const Size& size) : size(size) {}
    bool is_satisfied(Product* item) override {
        return item->size == size;
    }
};

int main () {
    // Product: apple, tree, banana
    Product apple{"Apple", Color::Green, Size::Small};
    Product tree{"Tree", Color::Green, Size::Large};
    Product banana{"Banana", Color::Yellow, Size::Small};

    // 构建 Product 容器
    vector<Product*> all{ &apple, &tree, &banana };

    // 过滤器对象
    BetterFilter bf;

    // 过滤规范
    ColorSpecification yellow(Color::Yellow);
    SizeSpecification small(Size::Small);

    // 过滤结果
    auto yellow_things = bf.filter(all, yellow);
    auto small_things = bf.filter(all, small);

    // 遍历结果集
    for(auto& x : yellow_things) {
        cout << x->name << " is yellow" << endl;
    }
    for(auto& x: small_things) {
        cout << x->name << " is small" << endl;
    }
}

// 依赖结构
// template
// Specification(virtual is_satisfied()) <- ColorSpecification(override is_satisfied())
//                                       <- SizeSpecification(override is_satisfied())

// template
// Filter(virtual filter()) <- BetterFilter(override filter())

// caller(Filter::filter) call callee(Specification<T>::is_satisfied)
// Filter::filter(*, Specification<T>& spec) {spec.is_satisfied()}