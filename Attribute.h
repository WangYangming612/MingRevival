#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>

class Attribute
{
public:
    Attribute(double initValue, double min, double max);
    virtual ~Attribute();

    virtual void addValue(double num);  // 增加数值
    virtual void reduceValue(double num); // 减少数值
    virtual bool checkLimit() = 0; // 检查数值是否越界

    double getValue() const;
    void setValue(double value);
    double getMin() const;
    double getMax() const;

protected:
    double m_value; // 当前数值
    double m_min;   // 最小值边界
    double m_max;   // 最大值边界
};

// 派生类1：崇祯皇帝个人属性
class EmperorAttr : public Attribute
{
public:
    EmperorAttr(double initValue = 50, double min = 0, double max = 100);
    bool checkLimit() override;
};

// 派生类2：大明国家属性
class CountryAttr : public Attribute
{
public:
    CountryAttr(double initValue = 500, double min = 0, double max = 1000);
    bool checkLimit() override;
};

// 派生类3：敌对/可控势力属性
class ForceAttr : public Attribute
{
public:
    ForceAttr(double initValue = 1000, double min = 0, double max = 2000);
    bool checkLimit() override;
};

#endif // ATTRIBUTE_H