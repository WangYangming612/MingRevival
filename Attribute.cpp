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

// ✅ 修复：添加派生类构造函数实现
// 派生类1：崇祯皇帝个人属性
EmperorAttr::EmperorAttr(double initValue, double min, double max)
    : Attribute(initValue, min, max)
{
}

// 派生类2：大明国家属性
CountryAttr::CountryAttr(double initValue, double min, double max)
    : Attribute(initValue, min, max)
{
}

// 派生类3：敌对/可控势力属性
ForceAttr::ForceAttr(double initValue, double min, double max)
    : Attribute(initValue, min, max)
{
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