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
#include <QTime>

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

private slots:
    void onNextMonth();
    void onHandleAffair();
    void onRestartGame();
};
#endif // QMAINWINDOWS_H