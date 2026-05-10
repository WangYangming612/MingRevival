#include "qmainwindows.h"
#include <QMessageBox>
#include <QTime>
#include <QProgressBar>
#include <QRandomGenerator>
#include <Qt>
#include <QDebug>      
#include <QDateTime>   
#include <QTextCursor>

QMainWindows::QMainWindows(QWidget* parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("崇祯救明：大明中兴模拟器");
    this->resize(1200, 800);

    // 古风QSS样式表
    this->setStyleSheet(R"(
    QMainWindow {
        background-color: #f5f0e6;
        font-family: "SimSun", "Microsoft YaHei";
    }
    
    QLabel {
        font-family: "SimSun", "Microsoft YaHei";
        font-size: 14px;
        color: #3b2313;
        font-weight: bold;
    }
    
    QLabel.title {
        font-size: 18px;
        color: #8b0000;
        font-weight: bold;
        margin: 10px 0;
        text-align: center;
    }
    
    QPushButton {
        font-family: "SimSun", "Microsoft YaHei";
        font-size: 16px;
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #e8d4b4, stop:1 #d4b88c);
        border: 2px solid #8b5a2b;
        border-radius: 8px;
        padding: 10px 15px;
        min-width: 150px;
        box-shadow: 0px 2px 4px rgba(0,0,0,0.2);
    }
    
    QPushButton:hover {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #f5e6cc, stop:1 #e8d4b4);
        border: 2px solid #a0522d;
    }
    
    QPushButton:pressed {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #d4b88c, stop:1 #c0a878);
        padding-top: 12px;
        padding-bottom: 8px;
    }
    
    QPushButton:disabled {
        background-color: #c0b0a0;
        border: 2px solid #7a6a5a;
        color: #7a6a5a;
    }
    
    QProgressBar {
        border: 1px solid #8b5a2b;
        border-radius: 4px;
        text-align: center;
        background-color: #f8f3e9;
        height: 22px;
        font-family: "SimSun", "Microsoft YaHei";
        font-size: 12px;
        margin: 3px 0;
    }
    
    QProgressBar::chunk {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #d4af37, stop:1 #b8860b);
        border-radius: 3px;
    }
    
    QTextEdit {
        font-family: "SimSun", "Microsoft YaHei";
        font-size: 13px;
        background-color: rgba(248, 243, 233, 230);
        border: 2px solid #8b5a2b;
        border-radius: 5px;
        color: #3b2313;
        selection-background-color: #e8d4b4;
        padding: 8px;
    }
    
    QGroupBox {
        font-weight: bold;
        font-size: 15px;
        border: 1px solid #8b5a2b;
        border-radius: 6px;
        margin-top: 16px;
        background-color: rgba(245, 240, 230, 200);
        padding: 5px;
    }
    
    QGroupBox::title {
        subcontrol-origin: margin;
        subcontrol-position: top left;
        padding: 0 8px;
        color: #8b4513;
        background-color: #e8d4b4;
        border-radius: 3px;
    }
    
    QRadioButton {
        font-family: "SimSun", "Microsoft YaHei";
        font-size: 14px;
        color: #3b2313;
        spacing: 8px;
    }
    
    QRadioButton::indicator {
        width: 16px;
        height: 16px;
        border: 2px solid #8b5a2b;
        border-radius: 8px;
        background-color: #f5f0e6;
    }
    
    QRadioButton::indicator:checked {
        background-color: #b8860b;
        border: 2px solid #8b4513;
    }
    
    QDialog {
        background-color: #f5f0e6;
        border: 3px solid #8b5a2b;
        border-radius: 10px;
    }
    
    QDialog QLabel {
        font-size: 15px;
    }
    
    QDialog QPushButton {
        min-width: 120px;
        margin: 5px;
    }
    
    QScrollArea {
        border: none;
        background-color: transparent;
    }
    
    QScrollBar:vertical {
        border: 1px solid #8b5a2b;
        background: #f5f0e6;
        width: 12px;
        margin: 0px 0px 0px 0px;
        border-radius: 6px;
    }
    
    QScrollBar::handle:vertical {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, 
                    stop:0 #d4b88c, stop:1 #b8860b);
        min-height: 20px;
        border-radius: 5px;
    }
    
    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
        height: 0px;
    }
)");
    initUI();
    initData();
    updateUI();
}

QMainWindows::~QMainWindows()
{
    auto safeDelete = [](auto& ptr) {
        delete ptr;
        ptr = nullptr;
        };

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
    connect(m_affairBtn, &QPushButton::clicked, this, &QMainWindows::showAffairDialog);
    connect(m_restartBtn, &QPushButton::clicked, this, &QMainWindows::onRestartGame);
}

void QMainWindows::initData()
{
    m_currentMonth = 1;

    
#if !defined(QT_DEBUG)
    QRandomGenerator::global()->seed(static_cast<quint32>(QDateTime::currentMSecsSinceEpoch()));
#endif
    // 初始化属性
   // 传入三个参数（初始值，最小值，最大值）
    m_tili = new EmperorAttr(50, 0, 100);
    m_zhili = new EmperorAttr(50, 0, 100);
    m_poli = new EmperorAttr(50, 0, 100);
    m_shiren = new EmperorAttr(50, 0, 100);
    m_guoku = new CountryAttr(500, 0, 1500);
    m_minxin = new CountryAttr(500, 0, 1500);
    m_junxin = new CountryAttr(500, 0, 1500);
    m_lizhi = new CountryAttr(500, 0, 1500);
    m_minsheng = new CountryAttr(500, 0, 1500);
    m_chuangjun = new ForceAttr(800, 0, 3000);
    m_houjin = new ForceAttr(1000, 0, 3000);
    m_wenguan = new ForceAttr(500, 0, 2000);
    m_fanwang = new ForceAttr(500, 0, 2000);
    // 初始化政务和事件列表
    initAffairList();
    initEventList();

    // 开局日志
    m_logEdit->clear();
    addLog("【游戏开局】崇祯元年，大明内忧外患，国库空虚，民不聊生，你能否改写国运？");
    addLog("【提示】每月可处理1次政务，每3个月会遭遇重大历史事件，需要谨慎决策！");
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

    // ===================== 月度财政系统 =====================
    // 1. 计算月度税收（基础税收70，乘以民心、吏治、民生系数）
    double baseTax = 70.0;
    double minxinFactor = m_minxin->getValue() / 500.0; // 民心系数0-2
    double lizhiFactor = m_lizhi->getValue() / 500.0;   // 吏治系数0-2
    double minshengFactor = m_minsheng->getValue() / 500.0; // 民生系数0-2

    // 确保系数在合理范围内
    minxinFactor = qBound(0.0, minxinFactor, 2.0);
    lizhiFactor = qBound(0.0, lizhiFactor, 2.0);
    minshengFactor = qBound(0.0, minshengFactor, 2.0);

    double monthlyTax = baseTax * (minxinFactor + lizhiFactor + minshengFactor) / 3.0;

    // 2. 计算月度军费（基础军费40，乘以威胁系数）
    double baseMilitary = 40.0;
    double chuangjunThreat = m_chuangjun->getValue() / 1000.0;
    double houjinThreat = m_houjin->getValue() / 1000.0;

    // 确保威胁系数在合理范围内
    chuangjunThreat = qBound(0.0, chuangjunThreat, 2.0);
    houjinThreat = qBound(0.0, houjinThreat, 2.0);

    double threatFactor = (chuangjunThreat + houjinThreat) / 2.0;
    double monthlyMilitary = baseMilitary * (1.0 + threatFactor);

    // 3. 计算净收入并应用
    double netIncome = monthlyTax - monthlyMilitary;
    m_guoku->addValue(netIncome);

    addLog(QString("【月度财政】税收收入：%1，军费支出：%2，净收入：%3")
        .arg(QString::number(monthlyTax, 'f', 1))
        .arg(QString::number(monthlyMilitary, 'f', 1))
        .arg(QString::number(netIncome, 'f', 1)));
    // ============================================================

    // 每月默认势力增长
    m_chuangjun->addValue(20);
    m_houjin->addValue(15);
    addLog("【月度变化】闯军与后金势力持续扩张");

    // 每3个月随机触发一次历史事件
    if (!m_eventList.isEmpty() && m_currentMonth % 3 == 0) {
        auto rng = QRandomGenerator::global();
        int randomIndex = rng->bounded(m_eventList.size());
        showEventDialog(m_eventList[randomIndex]);
    }

    // 恢复政务按钮
    m_affairBtn->setEnabled(true);

    // 每月恢复5点体力 + 属性自然成长
    m_tili->addValue(5);
    m_poli->addValue(0.5);
    m_zhili->addValue(0.5);
    m_shiren->addValue(0.5);

    QString attributeGrowth = "";
    if (m_poli->getValue() > 0 || m_zhili->getValue() > 0 || m_shiren->getValue() > 0) {
        attributeGrowth = QString("（魄力+%1，智力+%2，识人+%3）")
            .arg(0.5, 0, 'f', 1)
            .arg(0.5, 0, 'f', 1)
            .arg(0.5, 0, 'f', 1);
    }

    addLog(QString("【体力恢复】本月休息恢复5点体力，当前体力：%1%2")
        .arg(m_tili->getValue())
        .arg(attributeGrowth));

    updateUI();
    checkGameEnd();
}

// 初始化政务池
void QMainWindows::initAffairList()
{
    m_affairList.clear();

    // 1. 兴修水利，赈灾救民
    m_affairList.append(Affair(
        "兴修水利，赈灾救民",
        "拨款修缮河道，开仓放粮，缓解各地饥荒，恢复农业生产",
        "无属性要求",
        -1, 0,
        -150, 80, 20, 30, 100, -50, 0, 20, 0,
        0, 3, 0, // 成功：智力+3
        0, -20, -10, -10, -30, 30, 0, -10, 0
    ));

    // 2. 整顿吏治，严查贪腐
    m_affairList.append(Affair(
        "整顿吏治，严查贪腐",
        "设立都察院，查办贪腐官员，整肃朝堂风气",
        "要求魄力≥60",
        0, 60,
        50, 30, 10, 100, 20, -30, 0, -40, 10,
        5, 0, 0, // 成功：魄力+5
        -50, -50, -20, -30, -40, 50, 0, 20, -20
    ));

    // 3. 向藩王征饷
    m_affairList.append(Affair(
        "向藩王征饷",
        "勒令各地藩王缴纳军饷，补充国库，加强中央集权",
        "要求魄力≥70",
        0, 70,
        300, 20, 20, 0, 0, 0, 0, -100, 150,
        4, 0, 0, // 成功：魄力+4
        0, -30, -10, 0, -20, 0, 0, 50, -100
    ));

    // 4. 提拔孙传庭，围剿闯军
    m_affairList.append(Affair(
        "提拔孙传庭，围剿闯军",
        "任用孙传庭为陕西总督，率军围剿李自成起义军",
        "要求识人≥60",
        2, 60,
        -200, 10, 80, 20, 10, -200, 0, 30, -10,
        0, 0, 6, // 成功：识人+6
        -150, -20, -80, -10, -30, 150, 0, -20, 0
    ));

    // 5. 加固关宁防线，抵御后金
    m_affairList.append(Affair(
        "加固关宁防线，抵御后金",
        "拨款修缮关宁锦防线，补充边防军饷，训练精兵",
        "要求智力≥50",
        1, 50,
        -180, 20, 60, 10, 0, 0, -150, 20, 0,
        0, 4, 0, // 成功：智力+4
        -100, -10, -40, 0, -20, 0, 100, -10, 0
    ));

    // 6. 减免赋税，休养生息
    m_affairList.append(Affair(
        "减免赋税，休养生息",
        "减免受灾地区赋税，恢复农业生产，安抚民心",
        "无属性要求",
        -1, 0,
        -100, 100, 10, 20, 80, -80, 0, 10, 0,
        0, 2, 0, // 成功：智力+2
        0, 0, 0, 0, 0, 50, 0, -10, 0
    ));

    // 7. 裁撤冗官，精简朝堂
    m_affairList.append(Affair(
        "裁撤冗官，精简朝堂",
        "裁撤无用官员，减少国库开支，提高行政效率",
        "要求智力≥60",
        1, 60,
        100, 10, 5, 50, 0, 0, 0, -30, 20,
        0, 3, 0, // 成功：智力+3
        -50, -20, 0, -30, -10, 0, 0, 20, -30
    ));

    // 8. 安抚流民，编入军伍
    m_affairList.append(Affair(
        "安抚流民，编入军伍",
        "收拢各地流民，补充军队兵源，稳定社会秩序",
        "要求魄力≥50",
        0, 50,
        -80, 50, 50, 10, 30, -100, 0, 20, 0,
        3, 0, 0, // 成功：魄力+3
        -50, -20, -30, 0, -20, 50, 0, -10, 0
    ));

    // 9. 与后金议和，暂缓边患
    m_affairList.append(Affair(
        "与后金议和，暂缓边患",
        "秘密与后金议和，争取喘息时间，积蓄国力",
        "要求智力≥70",
        1, 70,
        -100, -30, -20, 0, 0, 0, -200, 30, -30,
        0, 5, 0, // 成功：智力+5
        -50, -80, -50, -20, -30, 0, 50, -20, 20
    ));

    // 10. 开征商税，补充国库
    m_affairList.append(Affair(
        "开征商税，补充国库",
        "向江南富商征收商税，增加国库收入，缓解财政危机",
        "要求魄力≥60",
        0, 60,
        200, -10, 10, -20, -30, 0, 0, -40, 10,
        3, 0, 0, // 成功：魄力+3
        0, -30, 0, -50, -40, 0, 0, 20, -20
    ));

    // 新增11. 经筵讲学，提升学识
    m_affairList.append(Affair(
        "经筵讲学，提升学识",
        "每日听大儒讲学，研习经史子集，提升治国理政能力",
        "无属性要求",
        -1, 0,
        -30, 0, 0, 0, 20, 0, 0, 0, 0,
        0, 8, 0, // 成功：智力+8
        0, 0, 0, 0, 0, 0, 0, 0, 0
    ));

    // 新增12. 校阅禁军，锻炼魄力
    m_affairList.append(Affair(
        "校阅禁军，锻炼魄力",
        "亲自前往军营校阅军队，鼓舞士气，锻炼统帅能力",
        "无属性要求",
        -1, 0,
        -40, 0, 20, 0, 10, 0, 0, 0, 0,
        8, 0, 0, // 成功：魄力+8
        0, 0, 0, 0, 0, 0, 0, 0, 0
    ));

    // 新增13. 召见官员，考察识人
    m_affairList.append(Affair(
        "召见官员，考察识人",
        "单独召见各级官员，考察其能力品行，提升识人能力",
        "无属性要求",
        -1, 0,
        -20, 0, 0, 10, 10, 0, 0, 0, 0,
        0, 0, 8, // 成功：识人+8
        0, 0, 0, 0, 0, 0, 0, 0, 0
    ));
}
// 政务选择弹窗
void QMainWindows::showAffairDialog()
{
    if (m_affairList.isEmpty()) {
        QMessageBox::warning(this, "错误", "政务列表为空，请检查初始化！");
        qDebug() << "政务列表大小：" << m_affairList.size();
        return;
    }

    // 使用随机数生成
    auto rng = QRandomGenerator::global();

    // 随机抽取3条不同的政务
    QList<Affair> randomAffairs;
    QList<int> usedIndexes;

    while (randomAffairs.size() < 3 && usedIndexes.size() < m_affairList.size()) {
        int index = rng->bounded(m_affairList.size());
        if (!usedIndexes.contains(index)) {
            usedIndexes.append(index);
            randomAffairs.append(m_affairList[index]);
        }
    }

    qDebug() << "随机抽取的政务数量：" << randomAffairs.size();

    // 创建弹窗
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("月度政务处理");
    dialog->resize(700, 500);
    dialog->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动删除

    QVBoxLayout* mainLayout = new QVBoxLayout(dialog);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // 标题和说明
    QLabel* titleLabel = new QLabel("【崇祯皇帝政务决策】", dialog);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #8b0000;");
    mainLayout->addWidget(titleLabel);

    QLabel* descLabel = new QLabel("请选择一项本月要处理的政务：\n（每项政务都有特定属性要求，不满足可能导致负面效果）", dialog);
    descLabel->setWordWrap(true);
    mainLayout->addWidget(descLabel);

    // 滚动区域
    QScrollArea* scrollArea = new QScrollArea(dialog);
    scrollArea->setWidgetResizable(true);

    QWidget* scrollContent = new QWidget(dialog); // 设置父对象
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setSpacing(10);
    scrollLayout->setContentsMargins(0, 0, 0, 0);

    QButtonGroup* btnGroup = new QButtonGroup(dialog); // 设置父对象

    // 动态创建所有控件
    for (int i = 0; i < randomAffairs.size(); i++) {
        Affair affair = randomAffairs[i];

        QGroupBox* groupBox = new QGroupBox(affair.name, scrollContent);
        groupBox->setStyleSheet("QGroupBox { font-weight: bold; border: 1px solid #8b4513; border-radius: 5px; margin-top: 1ex; }");

        QVBoxLayout* groupLayout = new QVBoxLayout(groupBox);

        QLabel* descLabel = new QLabel(affair.desc, groupBox);
        descLabel->setWordWrap(true);
        descLabel->setStyleSheet("color: #4a4a4a;");
        groupLayout->addWidget(descLabel);

        QLabel* requireLabel = new QLabel(QString("【要求】%1").arg(affair.requireDesc), groupBox);
        requireLabel->setStyleSheet("color: #b22222; font-weight: bold;");
        groupLayout->addWidget(requireLabel);

        QRadioButton* radioButton = new QRadioButton(groupBox);
        radioButton->setProperty("index", i);
        btnGroup->addButton(radioButton, i);

        groupLayout->addWidget(radioButton);
        scrollLayout->addWidget(groupBox);
    }

    scrollLayout->addStretch();
    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);

    // 按钮区域
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QPushButton* confirmBtn = new QPushButton("确认执行", dialog);
    confirmBtn->setStyleSheet("QPushButton { background-color: #e8d4b4; border: 2px solid #8b5a2b; border-radius: 5px; padding: 8px; }"
        "QPushButton:hover { background-color: #f5e6cc; }");
    buttonLayout->addWidget(confirmBtn);

    QPushButton* cancelBtn = new QPushButton("取消", dialog);
    cancelBtn->setStyleSheet("QPushButton { background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 8px; }");
    buttonLayout->addWidget(cancelBtn);

    mainLayout->addLayout(buttonLayout);

    // 捕获需要的数据
    connect(confirmBtn, &QPushButton::clicked, [=]() {
        int selectId = btnGroup->checkedId();
        if (selectId < 0 || selectId >= randomAffairs.size()) {
            QMessageBox::warning(dialog, "提示", "请选择一项政务！");
            return;
        }

        Affair selectAffair = randomAffairs[selectId];
        addLog(QString("【政务处理】你选择了：%1").arg(selectAffair.name));
        addLog(QString("　　%1").arg(selectAffair.desc));

        // 检查属性要求
        bool isSuccess = true;
        QString failReason = "";

        if (selectAffair.requireAttr != -1) {
            int currentValue = 0;
            QString attrName = "";

            switch (selectAffair.requireAttr) {
            case 0:
                currentValue = m_poli->getValue();
                attrName = "魄力";
                break;
            case 1:
                currentValue = m_zhili->getValue();
                attrName = "智力";
                break;
            case 2:
                currentValue = m_shiren->getValue();
                attrName = "识人";
                break;
            }

            if (currentValue < selectAffair.requireValue) {
                isSuccess = false;
                failReason = QString("你的%1（%2）不满足要求（%3）")
                    .arg(attrName)
                    .arg(currentValue)
                    .arg(selectAffair.requireValue);
            }
        }

        // 应用数值变化
        if (isSuccess) {
            addLog("【执行结果】政务执行成功！");
            applyAffairEffects(selectAffair, true);

            // 应用皇帝属性加成
            m_poli->addValue(selectAffair.add_poli);
            m_zhili->addValue(selectAffair.add_zhili);
            m_shiren->addValue(selectAffair.add_shiren);

            if (selectAffair.add_poli != 0 || selectAffair.add_zhili != 0 || selectAffair.add_shiren != 0) {
                addLog(QString("【属性提升】魄力%1%2，智力%3%4，识人%5%6")
                    .arg(selectAffair.add_poli > 0 ? "+" : "")
                    .arg(selectAffair.add_poli)
                    .arg(selectAffair.add_zhili > 0 ? "+" : "")
                    .arg(selectAffair.add_zhili)
                    .arg(selectAffair.add_shiren > 0 ? "+" : "")
                    .arg(selectAffair.add_shiren));
            }
        }
        else {
            addLog(QString("【执行结果】政务执行失败！%1").arg(failReason));
            applyAffairEffects(selectAffair, false);
        }

        // 处理政务消耗体力
        m_tili->reduceValue(10);
        addLog(QString("【体力消耗】处理政务消耗10点体力，当前体力：%1").arg(m_tili->getValue()));

        // 禁用政务按钮，本月只能处理一次
        m_affairBtn->setEnabled(false);
        updateUI();

        // 检查游戏结束状态
        checkGameEnd();

        dialog->accept(); // 关闭对话框
        });

    connect(cancelBtn, &QPushButton::clicked, dialog, &QDialog::reject);

    // 显示弹窗
    dialog->exec();
}
// 应用政务效果
void QMainWindows::applyAffairEffects(const Affair& affair, bool isSuccess)
{
    if (isSuccess) {
        m_guoku->addValue(affair.guoku);
        m_minxin->addValue(affair.minxin);
        m_junxin->addValue(affair.junxin);
        m_lizhi->addValue(affair.lizhi);
        m_minsheng->addValue(affair.minsheng);
        m_chuangjun->addValue(affair.chuangjun);
        m_houjin->addValue(affair.houjin);
        m_wenguan->addValue(affair.wenguan);
        m_fanwang->addValue(affair.fanwang);
    }
    else {
        m_guoku->addValue(affair.fail_guoku);
        m_minxin->addValue(affair.fail_minxin);
        m_junxin->addValue(affair.fail_junxin);
        m_lizhi->addValue(affair.fail_lizhi);
        m_minsheng->addValue(affair.fail_minsheng);
        m_chuangjun->addValue(affair.fail_chuangjun);
        m_houjin->addValue(affair.fail_houjin);
        m_wenguan->addValue(affair.fail_wenguan);
        m_fanwang->addValue(affair.fail_fanwang);
    }

    logValueChanges();
}
// 初始化历史事件池
void QMainWindows::initEventList()
{
    m_eventList.clear();

    // 1. 袁崇焕杀毛文龙
    m_eventList.append(HistoryEvent(
        "袁崇焕斩杀毛文龙",
        "蓟辽督师袁崇焕未经请旨，擅自杀害皮岛总兵毛文龙，东江军军心涣散，朝野震动。",
        "崇祯二年（1629年），袁崇焕以尚方宝剑诛杀毛文龙，本意是整肃军纪，但引发了东江军的强烈不满。",
        "支持袁崇焕，认可其行为",
        "强化军权，震慑不臣，但东江军心涣散",
        -5, 0, 3, 0, 0, -20, 30, 0, 100, 0, 0, -50, 0,  // 体力、智力、魄力、识人、国库、民心、军心、吏治、民生、闯军、后金、文官、藩王
        "追责袁崇焕，将其革职下狱",
        "整肃朝纲，安抚军心，但削弱边防力量",
        -10, 0, 0, 2, -50, 30, -30, -50, 0, 0, 0, 50, 0
    ));

    // 2. 陕西大旱，流民四起
    m_eventList.append(HistoryEvent(
        "陕西大旱，流民四起",
        "陕西遭遇百年大旱，颗粒无收，百姓易子而食，大量流民加入李自成起义军。",
        "崇祯元年（1628年），陕西连年大旱，饥民遍地，官府无力赈济，民变四起。",
        "开仓放粮，全力赈灾",
        "消耗国库，但暂时稳定民心，减少流民",
        -10, 0, 0, 2, -200, 100, 10, -150, 50, 0, -30, 0, 0,
        "置之不理，优先保障军饷",
        "节省开支，但民心大失，起义军迅速壮大",
        0, 0, -2, 0, 50, -100, -20, 200, -30, 0, 30, 0, 0
    ));

    // 3. 李自成攻破洛阳
    m_eventList.append(HistoryEvent(
        "李自成攻破洛阳",
        "李自成率军攻破洛阳，杀福王朱常洵，没收福王府巨额财富，闯军声势大振。",
        "崇祯十四年（1641年），李自成攻破洛阳，处死福王朱常洵，获得大量财富，起义军迅速壮大。",
        "调集大军围剿闯军",
        "消耗巨大，但可能遏制起义军扩张",
        -15, -3, 2, 0, -250, -30, 50, -200, 0, 30, 0, 0, 0,
        "下旨罪己，安抚民心",
        "承认过失，争取民心，但可能被视为软弱",
        -10, 2, -1, 1, -50, 50, -20, -50, 30, 0, 0, 0, 0
    ));

    // 4. 皇太极率军入关
    m_eventList.append(HistoryEvent(
        "皇太极率军入关",
        "后金皇太极率军绕过山海关，突破长城防线，直逼京师，朝野震动。",
        "崇祯二年（1629年），皇太极率军绕道蒙古，突破长城防线，兵临北京城下。",
        "急召袁崇焕回师勤王",
        "加强防御，但可能引发内部矛盾",
        -10, -2, 3, 0, -150, -20, 40, 0, -100, 0, 30, 0, 0,
        "坚守京师，调各地兵马驰援",
        "稳扎稳打，但损失较大",
        -5, 1, 1, 0, -100, -30, 20, 0, -50, 0, 20, 0, 0
    ));

    // 5. 官员奏请裁撤驿站
    m_eventList.append(HistoryEvent(
        "官员奏请裁撤驿站",
        "有官员奏请裁撤全国驿站，可节省大量国库开支，但会导致大量驿卒失业。",
        "崇祯二年（1629年），兵科给事中刘懋建议裁撤驿站，以节省开支，但导致大量驿卒失业，其中就包括李自成。",
        "批准裁撤，节省开支",
        "国库增收，但大量驿卒失业，可能加入起义军",
        0, 0, 2, 0, 100, -50, 0, 100, -20, 30, 0, 0, 0,
        "驳回奏请，维持现状",
        "维持稳定，但财政压力增大",
        0, 1, -1, 1, -50, 20, 0, 0, 10, 0, 0, 0, 0
    ));

    // 6. 陈新甲议和事件
    m_eventList.append(HistoryEvent(
        "陈新甲秘密议和",
        "兵部尚书陈新甲秘密与后金议和，事泄后朝野哗然，要求严惩。",
        "崇祯十五年（1642年），陈新甲奉密旨与后金议和，但消息泄露，引发东林党人强烈反对。",
        "支持议和，保全实力",
        "争取喘息时间，但背负骂名，东林党不满",
        -8, 3, 0, 2, -100, -30, -10, 50, 0, 0, 30, -30, 0,
        "处死陈新甲，主战到底",
        "安抚朝臣，但失去议和机会，外患加剧",
        -12, -2, 2, -1, -50, 20, -20, -30, 0, 0, 50, 20, 0
    ));

    // 7. 松锦大战
    m_eventList.append(HistoryEvent(
        "松锦大战惨败",
        "洪承畴率13万精锐与后金决战于松山、锦州，全军覆没，关外防线崩溃。",
        "崇祯十三年至十四年（1640-1641年），明清松锦大战，明军惨败，损失最后的精锐部队。",
        "启用孙传庭，重建防线",
        "重新整军备战，但需要巨大投入",
        -15, 0, -2, 4, -300, -50, 30, -200, 0, 0, 0, 0, 0,
        "收缩防线，固守关内",
        "保存实力，但失去战略主动权",
        -8, 2, 1, 0, -100, 10, -10, 50, 0, 0, 20, 0, 0
    ));

    // 8. 周延儒复出
    m_eventList.append(HistoryEvent(
        "周延儒复出任首辅",
        "前首辅周延儒复出，承诺整肃朝纲，但实际结党营私，吏治更加腐败。",
        "崇祯十四年（1641年），周延儒复出担任首辅，初期颇得崇祯信任，但很快暴露其贪腐本质。",
        "信任周延儒，委以重任",
        "短期稳定朝局，但长期吏治更加腐败",
        -5, 0, 2, -2, 50, -20, 0, -50, 0, 0, 0, -30, 0,
        "罢免周延儒，另选贤能",
        "需要时间寻找合适人选，但可避免更大损失",
        -10, 1, -1, 3, -30, 10, 0, 20, 0, 0, 0, 20, 0
    ));

    // 9. 三饷加派
    m_eventList.append(HistoryEvent(
        "加派三饷",
        "为应对军费不足，朝廷加派辽饷、剿饷、练饷，百姓负担剧增，民怨沸腾。",
        "崇祯年间，为应对后金和农民军，朝廷先后加派三饷，导致民不聊生，加速了明朝灭亡。",
        "同意加派，保障军费",
        "短期解决军费问题，但民心大失，起义加剧",
        -10, 0, 3, -1, 200, -100, 20, 100, -150, 0, 0, 0, 0,
        "拒绝加派，寻求其他方案",
        "维护民心，但军费短缺，边防危急",
        -5, 2, -1, 1, -50, 50, -30, -50, 50, 0, 0, 0, 0
    ));

    // 10. 宁远兵变
    m_eventList.append(HistoryEvent(
        "宁远兵变",
        "因军饷拖欠，宁远守军发生兵变，扣押巡抚，边防出现危机。",
        "崇祯四年（1631年），因军饷长期拖欠，宁远守军发生兵变，扣押巡抚毕自肃，边防形势危急。",
        "迅速拨款安抚，惩治贪官",
        "平息兵变，但需严查吏治",
        -8, 1, 2, 0, -150, 30, 40, -100, 20, 0, 0, -20, 0,
        "武力镇压，严惩首恶",
        "震慑军心，但可能引发更大动荡",
        -12, -1, 3, -1, -50, -40, -30, 50, -30, 0, 0, 30, 0
    ));

    // 11. 东林党争
    m_eventList.append(HistoryEvent(
        "东林党与阉党余孽争斗",
        "朝中东林党与阉党余孽激烈争斗，互相攻讦，政务停滞。",
        "崇祯朝，东林党与阉党余孽持续争斗，崇祯频繁更换阁臣，导致朝政混乱，效率低下。",
        "支持东林党，清除阉党",
        "获得士大夫支持，但可能失去实用人才",
        -5, 1, -1, 2, -30, 20, 0, 30, 0, 0, 0, -20, 0,
        "平衡两派，唯才是举",
        "维持朝局稳定，但需要高超的政治智慧",
        -8, 2, 0, 3, -20, 10, 0, 20, 0, 0, 0, 0, 0
    ));

    // 12. 孙传庭出关
    m_eventList.append(HistoryEvent(
        "孙传庭被迫出关作战",
        "在朝廷压力下，尚未准备充分的孙传庭被迫率军出潼关与李自成决战。",
        "崇祯十六年（1643年），在朝廷催促下，孙传庭率新募军队出关作战，结果在郏县大败，损失惨重。",
        "坚持让孙传庭固守待机",
        "保存实力，但可能被指责畏战",
        -10, 2, -1, 4, -50, 10, -10, -30, 0, 0, 0, 0, 0,
        "催促孙传庭速战速决",
        "符合朝廷期望，但风险巨大",
        -15, -2, 3, -1, -100, -20, 20, -50, 0, 0, 50, 0, 0
    ));

    // 13. 吴三桂请饷
    m_eventList.append(HistoryEvent(
        "吴三桂请求增饷守关",
        "宁远总兵吴三桂请求增加军饷以守卫山海关，国库空虚难以满足。",
        "崇祯末年，吴三桂镇守山海关，多次请求增饷，但朝廷财政困难，难以满足其要求。",
        "全力满足吴三桂要求",
        "确保山海关安全，但国库压力巨大",
        -8, 0, 2, 1, -200, 0, 30, -100, 0, 0, 0, 0, -30,
        "部分满足，要求其节俭用兵",
        "平衡财政压力，但可能影响守关士气",
        -5, 1, 0, 0, -80, 10, 10, -30, 0, 0, 0, 0, -10
    ));

    // 14. 李明睿建议南迁
    m_eventList.append(HistoryEvent(
        "李明睿建议南迁",
        "左都御史李明睿秘密建议崇祯南迁南京，以保全半壁江山。",
        "崇祯十七年（1644年）初，面对李自成大军压境，李明睿建议崇祯放弃北京，南迁南京，延续明朝国祚。",
        "秘密准备南迁",
        "保留复兴希望，但可能被指责逃跑主义",
        -12, 3, -2, 2, -100, -30, -20, 50, 0, 0, 0, 0, 0,
        "拒绝南迁，死守北京",
        "彰显帝王气节，但面临全军覆没风险",
        -8, -1, 4, 0, -50, 20, 10, -20, 0, 0, 0, 0, 0
    ));

    // 15. 魏藻德罢相
    m_eventList.append(HistoryEvent(
        "首辅魏藻德贪腐案发",
        "首辅魏藻德贪污受贿案发，朝野震惊，吏治腐败达到顶点。",
        "崇祯末年，首辅魏藻德被揭发贪污巨额军饷，崇祯震怒，朝野上下对吏治彻底失望。",
        "严惩魏藻德，整顿吏治",
        "震慑贪官，但需要时间重建信任",
        -10, 1, 2, 3, -50, 30, -10, 100, 0, 0, 0, -30, 0,
        "从轻发落，维持朝局稳定",
        "避免朝局动荡，但吏治继续恶化",
        -5, -2, 0, -2, 20, -10, 0, -30, 0, 0, 0, 20, 0
    ));

    qDebug() << "历史事件列表初始化完成，共" << m_eventList.size() << "个事件";
}
// 历史事件弹窗
void QMainWindows::showEventDialog(const HistoryEvent& event)
{
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle(QString("【重大历史事件】%1").arg(event.title));
    dialog->resize(800, 600);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    QVBoxLayout* mainLayout = new QVBoxLayout(dialog);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // 事件背景
    QGroupBox* bgGroup = new QGroupBox("历史背景", dialog);
    bgGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 1px solid #8b4513; border-radius: 5px; margin-top: 1ex; }");
    QVBoxLayout* bgLayout = new QVBoxLayout(bgGroup);

    QLabel* bgLabel = new QLabel(event.background, bgGroup);
    bgLabel->setWordWrap(true);
    bgLabel->setStyleSheet("color: #2e8b57; font-style: italic;");
    bgLayout->addWidget(bgLabel);

    mainLayout->addWidget(bgGroup);

    // 事件内容
    QGroupBox* contentGroup = new QGroupBox("事件详情", dialog);
    contentGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 1px solid #8b4513; border-radius: 5px; margin-top: 1ex; }");
    QVBoxLayout* contentLayout = new QVBoxLayout(contentGroup);

    QLabel* contentLabel = new QLabel(event.content, contentGroup);
    contentLabel->setWordWrap(true);
    contentLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #8b0000;");
    contentLayout->addWidget(contentLabel);

    mainLayout->addWidget(contentGroup);

    // 应对选项
    QGroupBox* optionGroup = new QGroupBox("应对选项", dialog);
    optionGroup->setStyleSheet("QGroupBox { font-weight: bold; border: 1px solid #8b4513; border-radius: 5px; margin-top: 1ex; }");
    QVBoxLayout* optionLayout = new QVBoxLayout(optionGroup);

    QButtonGroup* btnGroup = new QButtonGroup(dialog);

    // 选项1
    QGroupBox* opt1Group = new QGroupBox(event.option1, optionGroup);
    opt1Group->setStyleSheet("border: 1px solid #4682b4; border-radius: 3px;");
    QVBoxLayout* opt1Layout = new QVBoxLayout(opt1Group);

    QLabel* opt1Desc = new QLabel(event.opt1Effect, opt1Group);
    opt1Desc->setWordWrap(true);
    opt1Desc->setStyleSheet("color: #1e90ff;");
    opt1Layout->addWidget(opt1Desc);

    QRadioButton* opt1Radio = new QRadioButton(opt1Group);
    btnGroup->addButton(opt1Radio, 1);
    opt1Layout->addWidget(opt1Radio);

    optionLayout->addWidget(opt1Group);

    // 选项2
    QGroupBox* opt2Group = new QGroupBox(event.option2, optionGroup);
    opt2Group->setStyleSheet("border: 1px solid #4682b4; border-radius: 3px;");
    QVBoxLayout* opt2Layout = new QVBoxLayout(opt2Group);

    QLabel* opt2Desc = new QLabel(event.opt2Effect, opt2Group);
    opt2Desc->setWordWrap(true);
    opt2Desc->setStyleSheet("color: #1e90ff;");
    opt2Layout->addWidget(opt2Desc);

    QRadioButton* opt2Radio = new QRadioButton(opt2Group);
    btnGroup->addButton(opt2Radio, 2);
    opt2Layout->addWidget(opt2Radio);

    optionLayout->addWidget(opt2Group);

    mainLayout->addWidget(optionGroup);

    // 按钮
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* confirmBtn = new QPushButton("确认选择", dialog);
    confirmBtn->setStyleSheet("background-color: #e8d4b4; border: 2px solid #8b5a2b; border-radius: 5px; padding: 8px;");
    buttonLayout->addWidget(confirmBtn);

    QPushButton* cancelBtn = new QPushButton("稍后再议", dialog);
    cancelBtn->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ccc; border-radius: 5px; padding: 8px;");
    buttonLayout->addWidget(cancelBtn);

    mainLayout->addLayout(buttonLayout);

    // 捕获事件数据
    connect(confirmBtn, &QPushButton::clicked, [=]() {
        int selectId = btnGroup->checkedId();
        if (selectId != 1 && selectId != 2) {
            QMessageBox::warning(dialog, "提示", "请选择一个应对方案！");
            return;
        }

        if (selectId == 1) {
            addLog(QString("【事件应对】%1：你选择了【%2】").arg(event.title).arg(event.option1));
            addLog(QString("　　%1").arg(event.opt1Effect));

            // 应用效果
            m_tili->addValue(event.opt1_tili);
            m_zhili->addValue(event.opt1_zhili);
            m_poli->addValue(event.opt1_poli);
            m_shiren->addValue(event.opt1_shiren);
            m_guoku->addValue(event.opt1_guoku);
            m_minxin->addValue(event.opt1_minxin);
            m_junxin->addValue(event.opt1_junxin);
            m_lizhi->addValue(event.opt1_lizhi);
            m_minsheng->addValue(event.opt1_minsheng);
            m_chuangjun->addValue(event.opt1_chuangjun);
            m_houjin->addValue(event.opt1_houjin);
            m_wenguan->addValue(event.opt1_wenguan);
            m_fanwang->addValue(event.opt1_fanwang);

            // 记录属性变化
            if (event.opt1_poli != 0 || event.opt1_zhili != 0 || event.opt1_shiren != 0) {
                addLog(QString("【属性变化】魄力%1%2，智力%3%4，识人%5%6")
                    .arg(event.opt1_poli > 0 ? "+" : "")
                    .arg(event.opt1_poli)
                    .arg(event.opt1_zhili > 0 ? "+" : "")
                    .arg(event.opt1_zhili)
                    .arg(event.opt1_shiren > 0 ? "+" : "")
                    .arg(event.opt1_shiren));
            }
        }
        else {
            addLog(QString("【事件应对】%1：你选择了【%2】").arg(event.title).arg(event.option2));
            addLog(QString("　　%1").arg(event.opt2Effect));

            // 应用效果
            m_tili->addValue(event.opt2_tili);
            m_zhili->addValue(event.opt2_zhili);
            m_poli->addValue(event.opt2_poli);
            m_shiren->addValue(event.opt2_shiren);
            m_guoku->addValue(event.opt2_guoku);
            m_minxin->addValue(event.opt2_minxin);
            m_junxin->addValue(event.opt2_junxin);
            m_lizhi->addValue(event.opt2_lizhi);
            m_minsheng->addValue(event.opt2_minsheng);
            m_chuangjun->addValue(event.opt2_chuangjun);
            m_houjin->addValue(event.opt2_houjin);
            m_wenguan->addValue(event.opt2_wenguan);
            m_fanwang->addValue(event.opt2_fanwang);

            // 记录属性变化
            if (event.opt2_poli != 0 || event.opt2_zhili != 0 || event.opt2_shiren != 0) {
                addLog(QString("【属性变化】魄力%1%2，智力%3%4，识人%5%6")
                    .arg(event.opt2_poli > 0 ? "+" : "")
                    .arg(event.opt2_poli)
                    .arg(event.opt2_zhili > 0 ? "+" : "")
                    .arg(event.opt2_zhili)
                    .arg(event.opt2_shiren > 0 ? "+" : "")
                    .arg(event.opt2_shiren));
            }
        }

        logValueChanges();
        updateUI();
        checkGameEnd();

        dialog->accept();
        });

    connect(cancelBtn, &QPushButton::clicked, dialog, &QDialog::reject);

    dialog->exec();
}
// 应用事件效果
void QMainWindows::applyEventEffects(const HistoryEvent& event, bool chooseOption1)
{
    if (chooseOption1) {
        // 选项1效果
        m_tili->addValueWithBounds(event.opt1_tili, 0, 100);
        m_zhili->addValueWithBounds(event.opt1_zhili, 0, 100);
        m_poli->addValueWithBounds(event.opt1_poli, 0, 100);
        m_shiren->addValueWithBounds(event.opt1_shiren, 0, 100);
        m_guoku->addValueWithBounds(event.opt1_guoku, 0, 5000);
        m_minxin->addValueWithBounds(event.opt1_minxin, 0, 1500);
        m_junxin->addValueWithBounds(event.opt1_junxin, 0, 1500);
        m_lizhi->addValueWithBounds(event.opt1_lizhi, 0, 1500);
        m_minsheng->addValueWithBounds(event.opt1_minsheng, 0, 1500);
        m_chuangjun->addValueWithBounds(event.opt1_chuangjun, 0, 3000);
        m_houjin->addValueWithBounds(event.opt1_houjin, 0, 3000);
        m_wenguan->addValueWithBounds(event.opt1_wenguan, 0, 2000);
        m_fanwang->addValueWithBounds(event.opt1_fanwang, 0, 2000);
    }
    else {
        // 选项2效果
        m_tili->addValueWithBounds(event.opt2_tili, 0, 100);
        m_zhili->addValueWithBounds(event.opt2_zhili, 0, 100);
        m_poli->addValueWithBounds(event.opt2_poli, 0, 100);
        m_shiren->addValueWithBounds(event.opt2_shiren, 0, 100);
        m_guoku->addValueWithBounds(event.opt2_guoku, 0, 5000);
        m_minxin->addValueWithBounds(event.opt2_minxin, 0, 1500);
        m_junxin->addValueWithBounds(event.opt2_junxin, 0, 1500);
        m_lizhi->addValueWithBounds(event.opt2_lizhi, 0, 1500);
        m_minsheng->addValueWithBounds(event.opt2_minsheng, 0, 1500);
        m_chuangjun->addValueWithBounds(event.opt2_chuangjun, 0, 3000);
        m_houjin->addValueWithBounds(event.opt2_houjin, 0, 3000);
        m_wenguan->addValueWithBounds(event.opt2_wenguan, 0, 2000);
        m_fanwang->addValueWithBounds(event.opt2_fanwang, 0, 2000);
    }

    logValueChanges();
    updateUI();
    checkGameEnd();
}
struct ValueChange {
    QString name;
    Attribute* attr; 
    double oldValue;
};
// 记录数值变化
void QMainWindows::logValueChanges()
{
    QString log = "【数值变化】";
    bool hasChanges = false;
    QStringList changes;

    struct AttrInfo {
        QString name;
        Attribute* attr;
        double oldValue;
    };

    // 先保存旧值
    QVector<AttrInfo> attrs = {
        {"国库", m_guoku, m_guoku->getValue()},
        {"民心", m_minxin, m_minxin->getValue()},
        {"军心", m_junxin, m_junxin->getValue()},
        {"吏治", m_lizhi, m_lizhi->getValue()},
        {"民生", m_minsheng, m_minsheng->getValue()},
        {"闯军", m_chuangjun, m_chuangjun->getValue()},
        {"后金", m_houjin, m_houjin->getValue()},
        {"文官", m_wenguan, m_wenguan->getValue()},
        {"藩王", m_fanwang, m_fanwang->getValue()}
    };

    // 应用变化后检查
    for (auto& item : attrs) {
        double newValue = item.attr->getValue();
        if (qAbs(newValue - item.oldValue) > 0.1) {
            QString change = QString("%1:%2→%3")
                .arg(item.name)
                .arg(static_cast<int>(item.oldValue))
                .arg(static_cast<int>(newValue));
            changes.append(change);
            hasChanges = true;
        }
    }

    if (hasChanges) {
        addLog(log + changes.join("，"));
    }
}
// 优化后的游戏结束检查
void QMainWindows::checkGameEnd()
{
    // 失败判定
    bool isGameOver = false;
    QString failReason = "";

    if (m_tili->getValue() <= 0) {
        isGameOver = true;
        failReason = "你积劳成疾，驾崩于紫禁城，大明群龙无首，很快灭亡";
    }
    else if (m_guoku->getValue() <= 0) {
        isGameOver = true;
        failReason = "国库彻底空虚，军饷断绝，军队哗变，李自成攻破北京";
    }
    else if (m_chuangjun->getValue() >= 2000) {
        isGameOver = true;
        failReason = "李自成率领闯军攻破北京，你自缢于煤山，大明灭亡";
    }
    else if (m_houjin->getValue() >= 2000) {
        isGameOver = true;
        failReason = "清军攻破山海关，入主中原，大明灭亡";
    }
    else if (m_minxin->getValue() <= 200) {
        isGameOver = true;
        failReason = "民心尽失，各地百姓纷纷起义，大明统治土崩瓦解";
    }

    if (isGameOver) {
        QMessageBox::critical(this, "游戏结束", QString("【大明灭亡】\n%1\n\n你最终没能改写明朝灭亡的命运，重开游戏再试一次吧！").arg(failReason));
        onRestartGame();
        return;
    }

    // 胜利判定（36个月到期）
    if (m_currentMonth > m_totalMonth) {
        QString winTitle = "";
        QString winContent = "";

        // 完美结局
        if (m_chuangjun->getValue() <= 200 && m_houjin->getValue() <= 500 &&
            m_guoku->getValue() >= 800 && m_minxin->getValue() >= 700) {
            winTitle = "【大明中兴】";
            winContent = "你用36个月的时间，平定了闯军叛乱，击退了后金入侵，国库充盈，民心安定，吏治清明，成功改写了明朝灭亡的命运，开创了大明中兴盛世！";
        }
        // 进阶结局
        else if (m_chuangjun->getValue() <= 500 && m_houjin->getValue() <= 800 &&
            m_minxin->getValue() + m_junxin->getValue() >= 1500) {
            winTitle = "【平定内忧，遏制外患】";
            winContent = "你成功遏制了闯军和后金的扩张，稳定了大明的统治，虽然没能彻底解决边患，但为大明争取了喘息的时间，改写了速亡的命运！";
        }
        // 基础结局
        else {
            winTitle = "【暂保大明】";
            winContent = "你坚守了36个月，保住了大明的核心疆土，虽然内忧外患仍在，但你成功延缓了明朝的灭亡，为后续的改革留下了机会！";
        }

        QMessageBox::information(this, "游戏胜利", QString("%1\n\n%2").arg(winTitle).arg(winContent));
        onRestartGame();
    }
}