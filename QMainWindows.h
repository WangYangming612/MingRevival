#ifndef QMAINWINDOWS_H
#define QMAINWINDOWS_H

#include <QMainWindow>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "attribute.h"
#include <QRandomGenerator>
#include <QDialog>
#include <QRadioButton>
#include <QButtonGroup>
#include <QScrollArea>
#include<QGroupBox>
#include <QTime>
// 政务结构体
struct Affair {
    QString name;        // 政务名称
    QString desc;        // 政务描述
    QString requireDesc; // 属性要求描述
    int requireAttr;     // 要求的属性
    int requireValue;    // 要求的属性值

    // 成功后的数值变化
    double guoku;
    double minxin;
    double junxin;
    double lizhi;
    double minsheng;   
    double chuangjun;
    double houjin;
    double wenguan;
    double fanwang;
    
    // 成功后皇帝属性加成
    double add_poli;
    double add_zhili;
    double add_shiren;

    // 失败后的数值变化
    double fail_guoku;
    double fail_minxin;
    double fail_junxin;
    double fail_lizhi;
    double fail_minsheng;
    double fail_chuangjun;
    double fail_houjin;
    double fail_wenguan;
    double fail_fanwang;

    // 构造函数
    Affair(const QString& n, const QString& d, const QString& reqD, int reqA, int reqV,
        double g, double m, double j, double l, double ms, double cj, double hj, double wg, double fw,
        double ap, double az, double as,
        double fg, double fm, double fj, double fl, double fms, double fcj, double fhj, double fwg, double ffw)
        : name(n), desc(d), requireDesc(reqD), requireAttr(reqA), requireValue(reqV),
        guoku(g), minxin(m), junxin(j), lizhi(l), minsheng(ms), chuangjun(cj), houjin(hj), wenguan(wg), fanwang(fw),
        add_poli(ap), add_zhili(az), add_shiren(as),
        fail_guoku(fg), fail_minxin(fm), fail_junxin(fj), fail_lizhi(fl), fail_minsheng(fms),
        fail_chuangjun(fcj), fail_houjin(fhj), fail_wenguan(fwg), fail_fanwang(ffw) {
    }

    // 默认构造函数
    Affair() : Affair("", "", "", -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {}
};

// 历史事件结构体
struct HistoryEvent {
    QString title;       // 事件标题
    QString content;     // 事件内容
    QString background; // 历史背景

    // 选项1
    QString option1;
    QString opt1Effect;  // 效果描述
    double opt1_tili;    // 体力变化
    double opt1_zhili;   // 智力变化
    double opt1_poli;    // 魄力变化
    double opt1_shiren;  // 识人变化
    double opt1_guoku;   // 国库变化
    double opt1_minxin;  // 民心变化
    double opt1_junxin;  // 军心变化
    double opt1_lizhi;   // 吏治变化
    double opt1_minsheng;// 民生变化
    double opt1_chuangjun;// 闯军势力变化
    double opt1_houjin;  // 后金势力变化
    double opt1_wenguan; // 文官集团变化
    double opt1_fanwang; // 藩王势力变化

    // 选项2
    QString option2;
    QString opt2Effect;  // 效果描述
    double opt2_tili;    // 体力变化
    double opt2_zhili;   // 智力变化
    double opt2_poli;    // 魄力变化
    double opt2_shiren;  // 识人变化
    double opt2_guoku;   // 国库变化
    double opt2_minxin;  // 民心变化
    double opt2_junxin;  // 军心变化
    double opt2_lizhi;   // 吏治变化
    double opt2_minsheng;// 民生变化
    double opt2_chuangjun;// 闯军势力变化
    double opt2_houjin;  // 后金势力变化
    double opt2_wenguan; // 文官集团变化
    double opt2_fanwang; // 藩王势力变化

    // 默认构造函数
    HistoryEvent() :
        opt1_tili(0), opt1_zhili(0), opt1_poli(0), opt1_shiren(0),
        opt1_guoku(0), opt1_minxin(0), opt1_junxin(0), opt1_lizhi(0), opt1_minsheng(0),
        opt1_chuangjun(0), opt1_houjin(0), opt1_wenguan(0), opt1_fanwang(0),
        opt2_tili(0), opt2_zhili(0), opt2_poli(0), opt2_shiren(0),
        opt2_guoku(0), opt2_minxin(0), opt2_junxin(0), opt2_lizhi(0), opt2_minsheng(0),
        opt2_chuangjun(0), opt2_houjin(0), opt2_wenguan(0), opt2_fanwang(0) {
    }

    // 完整构造函数
    HistoryEvent(
        const QString& t, const QString& c, const QString& bg,
        const QString& o1, const QString& e1,
        double t1, double z1, double p1, double s1, double g1, double m1, double j1, double l1, double ms1,
        double cj1, double hj1, double wg1, double fw1,
        const QString& o2, const QString& e2,
        double t2, double z2, double p2, double s2, double g2, double m2, double j2, double l2, double ms2,
        double cj2, double hj2, double wg2, double fw2
    ) : title(t), content(c), background(bg),
        option1(o1), opt1Effect(e1),
        opt1_tili(t1), opt1_zhili(z1), opt1_poli(p1), opt1_shiren(s1),
        opt1_guoku(g1), opt1_minxin(m1), opt1_junxin(j1), opt1_lizhi(l1), opt1_minsheng(ms1),
        opt1_chuangjun(cj1), opt1_houjin(hj1), opt1_wenguan(wg1), opt1_fanwang(fw1),
        option2(o2), opt2Effect(e2),
        opt2_tili(t2), opt2_zhili(z2), opt2_poli(p2), opt2_shiren(s2),
        opt2_guoku(g2), opt2_minxin(m2), opt2_junxin(j2), opt2_lizhi(l2), opt2_minsheng(ms2),
        opt2_chuangjun(cj2), opt2_houjin(hj2), opt2_wenguan(wg2), opt2_fanwang(fw2) {
    }
};
class QMainWindows : public QMainWindow
{
    Q_OBJECT

public:
    QMainWindows(QWidget* parent = nullptr);
    ~QMainWindows();

private:
    // 核心属性对象
    EmperorAttr* m_tili;       // 体力
    EmperorAttr* m_zhili;      // 智力
    EmperorAttr* m_poli;       // 魄力
    EmperorAttr* m_shiren;     // 识人
    CountryAttr* m_guoku;      // 国库
    CountryAttr* m_minxin;     // 民心
    CountryAttr* m_junxin;     // 军心
    CountryAttr* m_lizhi;      // 吏治
    CountryAttr* m_minsheng;   // 民生
    ForceAttr* m_chuangjun;    // 闯军势力
    ForceAttr* m_houjin;       // 后金势力
    ForceAttr* m_wenguan;      // 文官集团支持度
    ForceAttr* m_fanwang;      // 藩王支持度

    int m_currentMonth;
    const int m_totalMonth = 36;

    // 界面控件
    QWidget* m_leftWidget;
    QVBoxLayout* m_leftLayout;
    QWidget* m_midWidget;
    QVBoxLayout* m_midLayout;
    QLabel* m_timeLabel;
    QPushButton* m_affairBtn;
    QPushButton* m_nextMonthBtn;
    QPushButton* m_restartBtn;
    QWidget* m_rightWidget;
    QVBoxLayout* m_rightLayout;
    QTextEdit* m_logEdit;

    void initUI();
    void initData();
    void updateUI();
    void checkGameEnd();
    void addLog(QString content);

    // 政务系统相关
    QList<Affair> m_affairList;
    void initAffairList(); // 初始化政务池
    void showAffairDialog(); // 显示政务选择弹窗
    void applyAffairEffects(const Affair& affair, bool isSuccess); // 应用政务效果
    void logValueChanges(); // 记录数值变化
    // 历史事件系统相关
    QList<HistoryEvent> m_eventList;
    void initEventList(); // 初始化事件池
    void showEventDialog(const HistoryEvent& event); // 显示事件弹窗
    void applyEventEffects(const HistoryEvent& event, bool chooseOption1);
private slots:
    void onNextMonth();
    void onRestartGame();
};
#endif // QMAINWINDOWS_H