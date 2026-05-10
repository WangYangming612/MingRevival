#include "Attribute.h"

// 基类构造函数
Attribute::Attribute(double initValue, double min, double max)
    : m_value(initValue), m_min(min), m_max(max)
{
    // 确保初始值在范围内
    if (m_value < m_min) m_value = m_min;
    if (m_value > m_max) m_value = m_max;
}

// 基类虚析构函数
Attribute::~Attribute()
{
}

// 基类通用方法：增加数值，自动限制边界
void Attribute::addValue(double num)
{
    m_value += num;
    if (m_value > m_max) m_value = m_max;
    if (m_value < m_min) m_value = m_min;
}

// 基类通用方法：减少数值，自动限制边界
void Attribute::reduceValue(double num)
{
    m_value -= num;
    if (m_value < m_min) m_value = m_min;
    if (m_value > m_max) m_value = m_max;
}

// 新增：带自定义边界的增加值方法
void Attribute::addValueWithBounds(double delta, double minBound, double maxBound)
{
    double newValue = m_value + delta;
    if (newValue < minBound) newValue = minBound;
    if (newValue > maxBound) newValue = maxBound;
    m_value = newValue;
}
// 基类get/set方法，封装属性
double Attribute::getValue() const
{
    return m_value;
}

void Attribute::setValue(double value)
{
    m_value = value;
    // 自动限制边界
    if (m_value < m_min) m_value = m_min;
    if (m_value > m_max) m_value = m_max;
}

double Attribute::getMin() const
{
    return m_min;
}

double Attribute::getMax() const
{
    return m_max;
}

// 派生类1：崇祯皇帝个人属性
EmperorAttr::EmperorAttr(double initValue, double min, double max)
    : Attribute(initValue, min, max)
{
}
// 重写：皇帝属性的带边界增加值方法
void EmperorAttr::addValueWithBounds(double delta, double minBound, double maxBound)
{
    // 使用标准边界：0-100
    double actualMin = (minBound < 0) ? 0 : minBound;
    double actualMax = (maxBound > 100) ? 100 : maxBound;
    Attribute::addValueWithBounds(delta, actualMin, actualMax);
}
// 派生类2：大明国家属性
CountryAttr::CountryAttr(double initValue, double min, double max)
    : Attribute(initValue, min, max)
{
}
// 重写：国家属性的带边界增加值方法
void CountryAttr::addValueWithBounds(double delta, double minBound, double maxBound)
{
    // 使用标准边界：0-1500
    double actualMin = (minBound < 0) ? 0 : minBound;
    double actualMax = (maxBound > 1500) ? 1500 : maxBound;
    Attribute::addValueWithBounds(delta, actualMin, actualMax);
}
// 派生类3：敌对/可控势力属性
ForceAttr::ForceAttr(double initValue, double min, double max)
    : Attribute(initValue, min, max)
{
}
// 重写：势力属性的带边界增加值方法
void ForceAttr::addValueWithBounds(double delta, double minBound, double maxBound)
{
    // 使用标准边界：0-3000
    double actualMin = (minBound < 0) ? 0 : minBound;
    double actualMax = (maxBound > 3000) ? 3000 : maxBound;
    Attribute::addValueWithBounds(delta, actualMin, actualMax);
}

// 派生类1：皇帝属性重写，检查是否低于0
bool EmperorAttr::checkLimit()
{
    return m_value > m_min;
}

// 派生类2：国家属性重写，检查是否低于0
bool CountryAttr::checkLimit()
{
    return m_value > m_min;
}

// 派生类3：势力属性重写，检查是否超过上限
bool ForceAttr::checkLimit()
{
    return m_value < m_max;
}