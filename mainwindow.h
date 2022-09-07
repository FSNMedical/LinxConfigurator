#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMap>
#include <QComboBox>
#include <QButtonGroup>

#define VYNET_CONTENTS_LENGTH   60 //VYNET

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

    void on_IP_addr_linkActivated(const QString &link);

    void on_OrphStation_textChanged(const QString &arg1);

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
};

#endif // MAINWINDOW_H
