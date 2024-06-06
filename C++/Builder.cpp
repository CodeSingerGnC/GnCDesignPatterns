// C++11 
// 代码来自 Dmitri Nesteruk 的 C++20设计模式
// 包含所需的头文件
#include <string>
#include <iostream>
#include <numeric>
using namespace std;

// 前向声明Builder类
class PersonJobBuilder;
class PersonAddressBuilder;
class PersonBuilder;

// 定义Person类
class Person
{
    // 地址相关的成员变量
    string street_address, post_code, city;
    // 工作相关的成员变量
    string company_name, position;
    int annual_income = 0;

    // 私有的默认构造函数
    Person() {}

    // 声明Builder类为友元类，使它们可以访问Person的私有成员
    friend class PersonBuilderBase;
    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;

public:
    // 提供一个静态方法来创建一个PersonBuilder对象
    static PersonBuilder& build();

    // 返回一个描述Person对象的字符串
    string str() {
        return "lives at " + street_address 
            + " in " + city 
            + " with post code " + post_code
            + " works at " + company_name
            + " earning " + to_string(annual_income);
    }
};

// 定义PersonBuilderBase类，作为所有Builder类的基类
class PersonBuiderBase 
{
public:
    // 定义类型转换运算符，将PersonBuilderBase对象转换为Person对象
    operator Person()
    {
        return move(person);
    }

    // 定义两个方法，返回PersonAddressBuilder和PersonJobBuilder对象
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

protected:
    // 保护的成员变量，指向一个Person对象
    Person& person;

    // 保护的构造函数，接受一个Person对象的引用
    explicit PersonBuiderBase(Person& person)
        : person(person) {}
};

// 定义PersonBuilder类，继承自PersonBuilderBase
class PersonBuilder : public PersonBuiderBase {
public:
    // 构造函数，创建一个新的Person对象
    PersonBuilder() : PersonBuiderBase(p) {}

private:
    // 私有的成员变量，存储一个Person对象
    Person p;
};

// 实现Person类的build方法，返回一个PersonBuilder对象
PersonBuilder& Person::build() {
    PersonBuilder* pb = new PersonBuilder();
    return *pb;
}

// 定义PersonAddressBuilder类，用于设置Person对象的地址相关的属性
class PersonAddressBuilder : public PersonBuiderBase
{
public:
    typedef PersonAddressBuilder self;

    explicit PersonAddressBuilder(Person& person)
        : PersonBuiderBase{ person } {}

    // 定义一系列方法，用于设置Person对象的地址相关的属性
    self& at(string street_address)
    {
        person.street_address = street_address;
        return *this;
    }
    self& with_post_code(string post_code) {
        person.post_code = post_code;
        return *this;
    }
    self& in(string city) {
        person.city = city;
        return *this;
    }
};

// 定义PersonJobBuilder类，用于设置Person对象的工作相关的属性
class PersonJobBuilder : public PersonBuiderBase
{
public:
    typedef PersonJobBuilder self;

    explicit PersonJobBuilder(Person& person)
        : PersonBuiderBase{ person } {}

    // 定义一系列方法，用于设置Person对象的工作相关的属性
    self& at(string company_name) {
        person.company_name = company_name;
        return *this;
    }
    self& as_a(string position) {
        person.position = position;
        return *this;
    }
    self& earning(int income) {
        person.annual_income = income;
        return *this;
    }
};

// 实现PersonBuilderBase类的lives和works方法
PersonAddressBuilder PersonBuiderBase::lives() const {
    return *(new PersonAddressBuilder(person));
}

PersonJobBuilder PersonBuiderBase::works() const {
    return *(new PersonJobBuilder(person));
}

// 主函数，创建一个Person对象，并设置其属性
int main() {
    Person p = Person::build()
        .lives().at("SomeWhere")
                .in("China")
                .with_post_code("0")
        .works().at("NoWhere")
                .as_a("Programmer")
                .earning(10e6);
    cout << p.str() << endl;
}