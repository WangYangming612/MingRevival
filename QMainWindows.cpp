#include "qmainwindows.h"
#include <QMessageBox>
#include <QTime>
#include <QProgressBar>
#include <QRandomGenerator>
#include <Qt>

QMainWindows::QMainWindows(QWidget* parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("崇祯救明：大明中兴模拟器");
    this->resize(1200, 800);

    // 优化的古风QSS样式表
    this->setStyleSheet(R"(
        QMainWindow {
            background-color: #f5f0e6;
        }
        QLabel {
            font-family: "SimSun", "Microsoft YaHei";
            font-size: 14px;
            color: #3b2313;
            font-weight: bold;
        }
        QPushButton {
            font-family: "SimSun", "Microsoft YaHei";
            font-size: 16px;
            background-color: #e8d4b4;
            border: 2px solid #8b5a2b;
            border-radius: 5px;
            padding: 10px;
            min-width: 150px;
        }
        QPushButton:hover {
            background-color: #f5e6cc;
        }
        QPushButton:pressed {
            background-color: #d4b88c;
        }
        QPushButton:disabled {
            background-color: #c0b0a0;
            border: 2px solid #7a6a5a;
        }
        QProgressBar {
            border: 1px solid #8b5a2b;
            border-radius: 3px;
            text-align: center;
            background-color: #f5f0e6;
            height: 20px;
            font-family: "SimSun", "Microsoft YaHei";
            font-size: 12px;
        }
        QProgressBar::chunk {
            background-color: #b88646;
        }
        QTextEdit {
            font-family: "SimSun", "Microsoft YaHei";
            font-size: 13px;
            background-color: rgba(245, 240, 230, 200);
            border: 2px solid #8b5a2b;
            color: #3b2313;
            selection-background-color: #e8d4b4;
        }
        QGroupBox {
            font-weight: bold;
            border: 1px solid #8b5a2b;
            border-radius: 5px;
            margin-top: 1ex;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top left;
            padding: 0 5px;
            color: #8b4513;
        }
        QRadioButton {
            font-family: "SimSun", "Microsoft YaHei";
            font-size: 14px;
            color: #3b2313;
        }
        QDialog {
            background-color: #f5f0e6;
        }
    )");

    initUI();
    initData();
    updateUI();
}

QMainWindows::~QMainWindows()
{
    delete m_tili;
    delete m_zhili;
    delete m_poli;
    delete m_shiren;
    delete m_guoku;
    delete m_minxin;
    delete m_junxin;
    delete m_lizhi;
    delete m_minsheng;
    delete m_chuangjun;
    delete m_houjin;
    delete m_wenguan;
    delete m_fanwang;
}

void QMainWindows::initUI()
{
    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    this->setCentralWidget(centralWidget);

    // ===================== 左侧数值区 =====================
    m_leftWidget = new QWidget();
    m_leftLayout = new QVBoxLayout(m_leftWidget);
    m_leftLayout->setSpacing(10);

    // 皇帝属性
    m_leftLayout->addWidget(new QLabel("=== 崇祯皇帝属性 ==="));
    m_leftLayout->addWidget(new QLabel("体力"));
    QProgressBar* tiliBar = new QProgressBar();
    tiliBar->setObjectName("tiliBar");
    tiliBar->setRange(0, 100);
    m_leftLayout->addWidget(tiliBar);

    m_leftLayout->addWidget(new QLabel("智力"));
    QProgressBar* zhiliBar = new QProgressBar();
    zhiliBar->setObjectName("zhiliBar");
    zhiliBar->setRange(0, 100);
    m_leftLayout->addWidget(zhiliBar);

    m_leftLayout->addWidget(new QLabel("魄力"));
    QProgressBar* poliBar = new QProgressBar();
    poliBar->setObjectName("poliBar");
    poliBar->setRange(0, 100);
    m_leftLayout->addWidget(poliBar);

    m_leftLayout->addWidget(new QLabel("识人"));
    QProgressBar* shirenBar = new QProgressBar();
    shirenBar->setObjectName("shirenBar");
    shirenBar->setRange(0, 100);
    m_leftLayout->addWidget(shirenBar);

    // 国家属性
    m_leftLayout->addSpacing(20);
    m_leftLayout->addWidget(new QLabel("=== 大明国家属性 ==="));
    m_leftLayout->addWidget(new QLabel("国库"));
    QProgressBar* guokuBar = new QProgressBar();
    guokuBar->setObjectName("guokuBar");
    guokuBar->setRange(0, 1000);
    m_leftLayout->addWidget(guokuBar);

    m_leftLayout->addWidget(new QLabel("民心"));
    QProgressBar* minxinBar = new QProgressBar();
    minxinBar->setObjectName("minxinBar");
    minxinBar->setRange(0, 1000);
    m_leftLayout->addWidget(minxinBar);

    m_leftLayout->addWidget(new QLabel("军心"));
    QProgressBar* junxinBar = new QProgressBar();
    junxinBar->setObjectName("junxinBar");
    junxinBar->setRange(0, 1000);
    m_leftLayout->addWidget(junxinBar);

    m_leftLayout->addWidget(new QLabel("吏治"));
    QProgressBar* lizhiBar = new QProgressBar();
    lizhiBar->setObjectName("lizhiBar");
    lizhiBar->setRange(0, 1000);
    m_leftLayout->addWidget(lizhiBar);

    m_leftLayout->addWidget(new QLabel("民生"));
    QProgressBar* minshengBar = new QProgressBar();
    minshengBar->setObjectName("minshengBar");
    minshengBar->setRange(0, 1000);
    m_leftLayout->addWidget(minshengBar);

    // 势力属性
    m_leftLayout->addSpacing(20);
    m_leftLayout->addWidget(new QLabel("=== 各方势力 ==="));
    m_leftLayout->addWidget(new QLabel("闯军势力（越低越安全）"));
    QProgressBar* chuangjunBar = new QProgressBar();
    chuangjunBar->setObjectName("chuangjunBar");
    chuangjunBar->setRange(0, 2000);
    chuangjunBar->setStyleSheet("QProgressBar::chunk { background-color: red; }");
    m_leftLayout->addWidget(chuangjunBar);

    m_leftLayout->addWidget(new QLabel("后金势力（越低越安全）"));
    QProgressBar* houjinBar = new QProgressBar();
    houjinBar->setObjectName("houjinBar");
    houjinBar->setRange(0, 2000);
    houjinBar->setStyleSheet("QProgressBar::chunk { background-color: darkred; }");
    m_leftLayout->addWidget(houjinBar);

    m_leftLayout->addWidget(new QLabel("文官集团支持度"));
    QProgressBar* wenguanBar = new QProgressBar();
    wenguanBar->setObjectName("wenguanBar");
    wenguanBar->setRange(0, 2000);
    m_leftLayout->addWidget(wenguanBar);

    m_leftLayout->addWidget(new QLabel("藩王支持度"));
    QProgressBar* fanwangBar = new QProgressBar();
    fanwangBar->setObjectName("fanwangBar");
    fanwangBar->setRange(0, 2000);
    m_leftLayout->addWidget(fanwangBar);

    m_leftLayout->addStretch();

    // ===================== 中间操作区 =====================
    m_midWidget = new QWidget();
    m_midLayout = new QVBoxLayout(m_midWidget);
    m_midLayout->setSpacing(20);

    m_timeLabel = new QLabel();
    m_timeLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    m_midLayout->addWidget(m_timeLabel, 0, Qt::AlignCenter);

    m_affairBtn = new QPushButton("处理月度政务");
    m_affairBtn->setFixedSize(200, 60);
    m_midLayout->addWidget(m_affairBtn, 0, Qt::AlignCenter);

    m_nextMonthBtn = new QPushButton("推进到下一个月");
    m_nextMonthBtn->setFixedSize(200, 60);
    m_midLayout->addWidget(m_nextMonthBtn, 0, Qt::AlignCenter);

    m_restartBtn = new QPushButton("重新开始游戏");
    m_restartBtn->setFixedSize(200, 60);
    m_midLayout->addWidget(m_restartBtn, 0, Qt::AlignCenter);

    m_midLayout->addStretch();

    // ===================== 右侧日志区 =====================
    m_rightWidget = new QWidget();
    m_rightLayout = new QVBoxLayout(m_rightWidget);

    m_rightLayout->addWidget(new QLabel("=== 朝政日志 ==="));
    m_logEdit = new QTextEdit();
    m_logEdit->setReadOnly(true);
    m_rightLayout->addWidget(m_logEdit);

    // ===================== 加入主布局 =====================
    mainLayout->addWidget(m_leftWidget, 3);
    mainLayout->addWidget(m_midWidget, 2);
    mainLayout->addWidget(m_rightWidget, 3);

    // ===================== 绑定信号槽 =====================
    connect(m_nextMonthBtn, &QPushButton::clicked, this, &QMainWindows::onNextMonth);
    connect(m_affairBtn, &QPushButton::clicked, this, &QMainWindows::onHandleAffair);
    connect(m_restartBtn, &QPushButton::clicked, this, &QMainWindows::onRestartGame);
}

void QMainWindows::initData()
{
    m_currentMonth = 1;

    // ✅ 修复后的随机数种子设置
#if !defined(QT_DEBUG)
    QRandomGenerator::global()->seed(static_cast<quint32>(QTime::currentTime().msec()));
#endif

    // 初始化属性
    m_tili = new EmperorAttr(50);
    m_zhili = new EmperorAttr(50);
    m_poli = new EmperorAttr(50);
    m_shiren = new EmperorAttr(50);
    m_guoku = new CountryAttr(500);
    m_minxin = new CountryAttr(500);
    m_junxin = new CountryAttr(500);
    m_lizhi = new CountryAttr(500);
    m_minsheng = new CountryAttr(500);
    m_chuangjun = new ForceAttr(800);
    m_houjin = new ForceAttr(1000);
    m_wenguan = new ForceAttr(500);
    m_fanwang = new ForceAttr(500);

    // 开局日志
    m_logEdit->clear();
    addLog("【游戏开局】崇祯元年，大明内忧外患，国库空虚，民不聊生，你能否改写国运？");
    addLog("【提示】每月可处理1次政务，处理后推进月份，应对随机历史事件");
}

void QMainWindows::updateUI()
{
    m_timeLabel->setText(QString("崇祯 %1 年 %2 月\n剩余时间：%3 个月")
        .arg((m_currentMonth - 1) / 12 + 1)
        .arg((m_currentMonth - 1) % 12 + 1)
        .arg(m_totalMonth - m_currentMonth));

    // 更新所有进度条
    findChild<QProgressBar*>("tiliBar")->setValue(m_tili->getValue());
    findChild<QProgressBar*>("zhiliBar")->setValue(m_zhili->getValue());
    findChild<QProgressBar*>("poliBar")->setValue(m_poli->getValue());
    findChild<QProgressBar*>("shirenBar")->setValue(m_shiren->getValue());
    findChild<QProgressBar*>("guokuBar")->setValue(m_guoku->getValue());
    findChild<QProgressBar*>("minxinBar")->setValue(m_minxin->getValue());
    findChild<QProgressBar*>("junxinBar")->setValue(m_junxin->getValue());
    findChild<QProgressBar*>("lizhiBar")->setValue(m_lizhi->getValue());
    findChild<QProgressBar*>("minshengBar")->setValue(m_minsheng->getValue());
    findChild<QProgressBar*>("chuangjunBar")->setValue(m_chuangjun->getValue());
    findChild<QProgressBar*>("houjinBar")->setValue(m_houjin->getValue());
    findChild<QProgressBar*>("wenguanBar")->setValue(m_wenguan->getValue());
    findChild<QProgressBar*>("fanwangBar")->setValue(m_fanwang->getValue());
}

void QMainWindows::addLog(QString content)
{
    m_logEdit->append(content);
    m_logEdit->moveCursor(QTextCursor::End);
}

void QMainWindows::onRestartGame()
{
    QMessageBox::information(this, "提示", "游戏已重置，回到崇祯元年！");
    initData();
    updateUI();
}

void QMainWindows::onNextMonth()
{
    m_currentMonth++;
    addLog(QString("【时间推进】已进入崇祯 %1 年 %2 月")
        .arg((m_currentMonth - 1) / 12 + 1)
        .arg((m_currentMonth - 1) % 12 + 1));

    m_affairBtn->setEnabled(true);
    m_tili->addValue(5);
    addLog(QString("【体力恢复】本月休息恢复5点体力，当前体力：%1").arg(m_tili->getValue()));

    updateUI();
    checkGameEnd();
}

void QMainWindows::onHandleAffair()
{
    // 基础政务处理功能
    QMessageBox::information(this, "政务处理",
        "请选择一项政务：\n1. 兴修水利，赈灾救民\n2. 整顿吏治，严查贪腐\n3. 向藩王征饷");

    // 简单示例：处理政务消耗体力
    m_tili->reduceValue(10);
    addLog("【政务】处理月度政务，体力-10");
    m_affairBtn->setEnabled(false);
    updateUI();
}

void QMainWindows::checkGameEnd()
{
    // 游戏结束条件检查
    if (m_currentMonth > m_totalMonth) {
        QMessageBox::information(this, "游戏结束", "36个月已到，崇祯四年结束！\n大明国运如何，由你定夺。");
        onRestartGame();
        return;
    }

    // 体力耗尽
    if (m_tili->getValue() <= 0) {
        QMessageBox::critical(this, "游戏结束", "陛下积劳成疾，驾崩于紫禁城！\n大明江山就此倾覆...");
        onRestartGame();
        return;
    }

    // 闯军过强
    if (m_chuangjun->getValue() >= 2000) {
        QMessageBox::critical(this, "游戏结束", "闯军势如破竹，攻破北京城！\n崇祯皇帝自缢煤山...");
        onRestartGame();
        return;
    }

    // 后金过强
    if (m_houjin->getValue() >= 2000) {
        QMessageBox::critical(this, "游戏结束", "清军入关，铁骑踏破山河！\n大明江山易主...");
        onRestartGame();
        return;
    }

    // 国库空虚
    if (m_guoku->getValue() <= 0) {
        QMessageBox::critical(this, "游戏结束", "国库空虚，军饷断绝，士兵哗变！\n京师陷落...");
        onRestartGame();
        return;
    }
}