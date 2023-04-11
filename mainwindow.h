#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMap>
#include <QComboBox>
#include <QButtonGroup>

#define VYNET_CONTENTS_LENGTH   60 //VYNET

// Defines to mark the entries in the LINXConfig.txt file
#define LNX_IDEX_00_MN1   (0) //mon01,Monitor 1
#define LNX_IDEX_01_MN2   (1) //mon02,Monitor 2
#define LNX_IDEX_02_MN3   (2) //mon03,Monitor 3
#define LNX_IDEX_03_MN4   (3) //mon04,Monitor 4
#define LNX_IDEX_04_MN5   (4) //mon05,Monitor 5
#define LNX_IDEX_05_MN6   (5) //mon06,Monitor 6
#define LNX_IDEX_06_MN7   (6)//mon07,Monitor 7
#define LNX_IDEX_07_MN8   (7)//mon08,Monitor 8
#define LNX_IDEX_08_MN9   (8)//mon09,Monitor 9
#define LNX_IDEX_09_MN10  (9)//mon10,Monitor 10
#define LNX_IDEX_10_MN11  (10)//mon11,Monitor 11
#define LNX_IDEX_11_MN12  (11)//mon12,Monitor 12
#define LNX_IDEX_12_SR1   (12)//src01,,None,
#define LNX_IDEX_13_SR2   (13)//src02,,None,
#define LNX_IDEX_14_SR3   (14)//src03,,None,
#define LNX_IDEX_15_SR4   (15)//src04,,None,
#define LNX_IDEX_16_SR5   (16)//src05,,None,
#define LNX_IDEX_17_SR6   (17)//src06,,None,
#define LNX_IDEX_18_SR7   (18)//src07,,None,
#define LNX_IDEX_19_SR8   (19)//src08,,None,
#define LNX_IDEX_20_SR9   (20)//src09,,None,
#define LNX_IDEX_21_SR10  (21) //src10,,None,
#define LNX_IDEX_22_SR11  (22) //src11,,None,
#define LNX_IDEX_23_SR12  (23) //src12,,None,
#define LNX_IDEX_24_SR13  (24) //src13,,None,
#define LNX_IDEX_25_SR14  (25) //src14,,None,
#define LNX_IDEX_26_SR15  (26) //src15,,None,
#define LNX_IDEX_27_SR16  (27) //src16,,Test,Pattern
#define LNX_IDEX_28_ENAB  (28) //enabl,0000000000000000
#define LNX_IDEX_29_ZOOM  (29) //zoom-,0000000000000000
#define LNX_IDEX_30_DSTYP (30) //dstyp,000000
#define LNX_IDEX_31_AUDIO (31) //audio,0
#define LNX_IDEX_32_CODEC (32) //codec,0
#define LNX_IDEX_33_DSCC  (33) //dcss-,3
#define LNX_IDEX_34_IPOD  (34)//ipod-,0
#define LNX_IDEX_35_SKYLT (35)//skylt,0,0
#define LNX_IDEX_36_DSPLY (36) //dsply,1
#define LNX_IDEX_37_SERL  (37) //serl#,Unassigned
#define LNX_IDEX_38_NAME  (38) //name-,OR-1
#define LNX_IDEX_39_PASSW (39) //passw,3699
#define LNX_IDEX_40_TIMEO (40) //timeo,0
#define LNX_IDEX_41_QUAD  (41) //quad-,0
#define LNX_IDEX_42_DETEC (42) //detec,1
#define LNX_IDEX_43_ORPH  (43) //orph-,choochoo,192.168.200.123
#define LNX_IDEX_44_EMAIL (44) //email,0
#define LNX_IDEX_45_TYPSW (45) //typsw,4,192.168.200.170

enum TYPE_OF_SWITCH{
    TYPE_SWITCH_NONE = 0,
    TYPE_SWITCH_OPHIT,      // 1
    TYPE_SWITCH_OPTICIS,    // 2
    TYPE_SWITCH_VYNET,      // 3
    TYPE_SWITCH_IPS4000     // 4        // 2021-12-13
};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

   // Use comboBox for Source type
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_comboBox_5_currentIndexChanged(const QString &arg1);

    void on_comboBox_6_currentIndexChanged(const QString &arg1);

    void on_comboBox_7_currentIndexChanged(const QString &arg1);

    void on_comboBox_8_currentIndexChanged(const QString &arg1);

    void on_comboBox_9_currentIndexChanged(const QString &arg1);

    void on_comboBox_10_currentIndexChanged(const QString &arg1);

    void on_comboBox_11_currentIndexChanged(const QString &arg1);

    void on_comboBox_12_currentIndexChanged(const QString &arg1);

    void on_comboBox_13_currentIndexChanged(const QString &arg1);

    void on_comboBox_14_currentIndexChanged(const QString &arg1);

    void on_comboBox_15_currentIndexChanged(const QString &arg1);

    void on_comboBox_16_currentIndexChanged(const QString &arg1);

    void HideSaveLabel();

    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_CaptureCombo_currentIndexChanged(int index);

    void on_MonTypecomboBox_4_currentIndexChanged(const QString &arg1);

    void on_MonTypecomboBox_5_currentIndexChanged(const QString &arg1);

    void on_MonTypecomboBox_6_currentIndexChanged(const QString &arg1);

    void on_tabWidget_currentChanged(int index);

    void on_pushButton_2_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();


    void on_SwitchCombo_currentIndexChanged(int index);

    //void on_IP_addr_linkActivated(const QString &link);

    //void on_OrphStation_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QLineEdit* sMonName[13];

    QLineEdit* sSrcNameTop[17];
    QLineEdit* sSrcNameBot[17];

    QLineEdit* sRX_MAC[17];

    QLineEdit* sTX_MAC[17];

    QComboBox* comboSrcType[17];

    QComboBox* comboSrcMonType[7];

    QComboBox* comboRXScaleType[17];

    QString m_sData[47];                // add on typsw

    QMap<QString,QComboBox*> mMap;

    void ProcessSrcTypeCombo(QComboBox* pCurCombo,const QString &sSrcNm);

    void TryToReadConfig();

    void ParseFile();

    QString StringWOToken(QString sVal);

    bool TypeIsNotSelectedForAnySrc(QString sType);

    void TryToReadVynetFile();

    QString m_saVynetContents[VYNET_CONTENTS_LENGTH];

    QRegExpValidator m_RegExValidateMAC;

    QButtonGroup *buttonGroup2;

    int     m_nSwitchNum;
};

#endif // MAINWINDOW_H
