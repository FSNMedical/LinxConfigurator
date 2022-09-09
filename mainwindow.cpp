#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFile"
//#include "windows.h"
#include <QStandardItemModel>

#define NumberOfMonitors 12
#define ConfigFileName "LINXConfig.txt"
#define MaxNumberOfCaptureOptions 6

#define VynetFileName "VyNet.CSV"

#define LOWEST_POSSIBLE_VYNET_DEVICE_INDEX 1

#define HIGHEST_POSSIBLE_VYNET_DEVICE_INDEX 16


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sMonName[1] = ui->Mon_lineEdit_1;
    sMonName[2] = ui->Mon_lineEdit_2;
    sMonName[3] = ui->Mon_lineEdit_3;
    sMonName[4] = ui->Mon_lineEdit_4;
    sMonName[5] = ui->Mon_lineEdit_5;
    sMonName[6] = ui->Mon_lineEdit_6;
    sMonName[7] = ui->Mon_lineEdit_7;
    sMonName[8] = ui->Mon_lineEdit_8;
    sMonName[9] = ui->Mon_lineEdit_9;
    sMonName[10] = ui->Mon_lineEdit_10;
    sMonName[11] = ui->Mon_lineEdit_11;
    sMonName[12] = ui->Mon_lineEdit_12;

    sSrcNameTop[1] = ui->SrcTop_lineEdit_1;
    sSrcNameTop[2] = ui->SrcTop_lineEdit_2;
    sSrcNameTop[3] = ui->SrcTop_lineEdit_3;
    sSrcNameTop[4] = ui->SrcTop_lineEdit_4;
    sSrcNameTop[5] = ui->SrcTop_lineEdit_5;
    sSrcNameTop[6] = ui->SrcTop_lineEdit_6;
    sSrcNameTop[7] = ui->SrcTop_lineEdit_7;
    sSrcNameTop[8] = ui->SrcTop_lineEdit_8;
    sSrcNameTop[9] = ui->SrcTop_lineEdit_9;
    sSrcNameTop[10] = ui->SrcTop_lineEdit_10;
    sSrcNameTop[11] = ui->SrcTop_lineEdit_11;
    sSrcNameTop[12] = ui->SrcTop_lineEdit_12;
    sSrcNameTop[13] = ui->SrcTop_lineEdit_13;
    sSrcNameTop[14] = ui->SrcTop_lineEdit_14;
    sSrcNameTop[15] = ui->SrcTop_lineEdit_15;
    sSrcNameTop[16] = ui->SrcTop_lineEdit_16;

    sSrcNameBot[1] = ui->SrcBot_lineEdit_1;
    sSrcNameBot[2] = ui->SrcBot_lineEdit_2;
    sSrcNameBot[3] = ui->SrcBot_lineEdit_3;
    sSrcNameBot[4] = ui->SrcBot_lineEdit_4;
    sSrcNameBot[5] = ui->SrcBot_lineEdit_5;
    sSrcNameBot[6] = ui->SrcBot_lineEdit_6;
    sSrcNameBot[7] = ui->SrcBot_lineEdit_7;
    sSrcNameBot[8] = ui->SrcBot_lineEdit_8;
    sSrcNameBot[9] = ui->SrcBot_lineEdit_9;
    sSrcNameBot[10] = ui->SrcBot_lineEdit_10;
    sSrcNameBot[11] = ui->SrcBot_lineEdit_11;
    sSrcNameBot[12] = ui->SrcBot_lineEdit_12;
    sSrcNameBot[13] = ui->SrcBot_lineEdit_13;
    sSrcNameBot[14] = ui->SrcBot_lineEdit_14;
    sSrcNameBot[15] = ui->SrcBot_lineEdit_15;
    sSrcNameBot[16] = ui->SrcBot_lineEdit_16;

    sRX_MAC[1] = ui->RX_MAC_1;
    sRX_MAC[2] = ui->RX_MAC_2;
    sRX_MAC[3] = ui->RX_MAC_3;
    sRX_MAC[4] = ui->RX_MAC_4;
    sRX_MAC[5] = ui->RX_MAC_5;
    sRX_MAC[6] = ui->RX_MAC_6;
    sRX_MAC[7] = ui->RX_MAC_7;
    sRX_MAC[8] = ui->RX_MAC_8;
    sRX_MAC[9] = ui->RX_MAC_9;
    sRX_MAC[10] = ui->RX_MAC_10;
    sRX_MAC[11] = ui->RX_MAC_11;
    sRX_MAC[12] = ui->RX_MAC_12;
    sRX_MAC[13] = ui->RX_MAC_13;
    sRX_MAC[14] = ui->RX_MAC_14;
    sRX_MAC[15] = ui->RX_MAC_15;
    sRX_MAC[16] = ui->RX_MAC_16;

    sTX_MAC[1] = ui->TX_MAC_1;
    sTX_MAC[2] = ui->TX_MAC_2;
    sTX_MAC[3] = ui->TX_MAC_3;
    sTX_MAC[4] = ui->TX_MAC_4;
    sTX_MAC[5] = ui->TX_MAC_5;
    sTX_MAC[6] = ui->TX_MAC_6;
    sTX_MAC[7] = ui->TX_MAC_7;
    sTX_MAC[8] = ui->TX_MAC_8;
    sTX_MAC[9] = ui->TX_MAC_9;
    sTX_MAC[10] = ui->TX_MAC_10;
    sTX_MAC[11] = ui->TX_MAC_11;
    sTX_MAC[12] = ui->TX_MAC_12;
    sTX_MAC[13] = ui->TX_MAC_13;
    sTX_MAC[14] = ui->TX_MAC_14;
    sTX_MAC[15] = ui->TX_MAC_15;
    sTX_MAC[16] = ui->TX_MAC_16;

    comboSrcType[1] =ui->comboBox;
    comboSrcType[2] =ui->comboBox_2;
    comboSrcType[3] =ui->comboBox_3;
    comboSrcType[4] =ui->comboBox_4;
    comboSrcType[5] =ui->comboBox_5;
    comboSrcType[6] =ui->comboBox_6;
    comboSrcType[7] =ui->comboBox_7;
    comboSrcType[8] =ui->comboBox_8;
    comboSrcType[9] =ui->comboBox_9;
    comboSrcType[10] =ui->comboBox_10;
    comboSrcType[11] =ui->comboBox_11;
    comboSrcType[12] =ui->comboBox_12;
    comboSrcType[13] =ui->comboBox_13;
    comboSrcType[14] =ui->comboBox_14;
    comboSrcType[15] =ui->comboBox_15;
    comboSrcType[16] =ui->comboBox_16;

    comboRXScaleType[1] =ui->RX_Scale_comboBox_1;
    comboRXScaleType[2] =ui->RX_Scale_comboBox_2;
    comboRXScaleType[3] =ui->RX_Scale_comboBox_3;
    comboRXScaleType[4] =ui->RX_Scale_comboBox_4;
    comboRXScaleType[5] =ui->RX_Scale_comboBox_5;
    comboRXScaleType[6] =ui->RX_Scale_comboBox_6;
    comboRXScaleType[7] =ui->RX_Scale_comboBox_7;
    comboRXScaleType[8] =ui->RX_Scale_comboBox_8;
    comboRXScaleType[9] =ui->RX_Scale_comboBox_9;
    comboRXScaleType[10] =ui->RX_Scale_comboBox_10;
    comboRXScaleType[11] =ui->RX_Scale_comboBox_11;
    comboRXScaleType[12] =ui->RX_Scale_comboBox_12;
    comboRXScaleType[13] =ui->RX_Scale_comboBox_13;
    comboRXScaleType[14] =ui->RX_Scale_comboBox_14;
    comboRXScaleType[15] =ui->RX_Scale_comboBox_15;
    comboRXScaleType[16] =ui->RX_Scale_comboBox_16;

    comboSrcMonType[1] = ui->MonTypecomboBox_1;
    comboSrcMonType[2] = ui->MonTypecomboBox_2;
    comboSrcMonType[3] = ui->MonTypecomboBox_3;
    comboSrcMonType[4] = ui->MonTypecomboBox_4;
    comboSrcMonType[5] = ui->MonTypecomboBox_5;
    comboSrcMonType[6] = ui->MonTypecomboBox_6;

    ui->buttonGroup->addButton(ui->radioButton,0);
    ui->buttonGroup->addButton(ui->radioButton_2,1);
    ui->buttonGroup->addButton(ui->radioButton_3,2);
    ui->buttonGroup->addButton(ui->radioButton_4,3);

    //ui->buttonGroup->addButton(ui->radioButton_5,0);
    //ui->buttonGroup->addButton(ui->radioButton_6,1);

    buttonGroup2 = new QButtonGroup();
    buttonGroup2->addButton(ui->radioButton_5,0);
    buttonGroup2->addButton(ui->radioButton_6,1);
    buttonGroup2->addButton(ui->radioButton_7,2);
    buttonGroup2->addButton(ui->radioButton_8,3);
    buttonGroup2->button(0)->setChecked(true);

    //Set file content array elements to default values
    m_sData[0] = "mon01,Monitor 1";
    m_sData[1] = "mon02,Monitor 2";
    m_sData[2] = "mon03,Monitor 3";
    m_sData[3] = "mon04,Monitor 4";
    m_sData[4] = "mon05,Monitor 5";
    m_sData[5] = "mon06,Monitor 6";
    m_sData[6] = "mon07,Monitor 7";
    m_sData[7] = "mon08,Monitor 8";
    m_sData[8] = "mon09,Monitor 9";
    m_sData[9] = "mon10,Monitor 10";
    m_sData[10] = "mon11,Monitor 11";
    m_sData[11] = "mon12,Monitor 12";
    m_sData[12] = "src01,,None,";
    m_sData[13] = "src02,,None,";
    m_sData[14] = "src03,,None,";
    m_sData[15] = "src04,,None,";
    m_sData[16] = "src05,,None,";
    m_sData[17] = "src06,,None,";
    m_sData[18] = "src07,,None,";
    m_sData[19] = "src08,,None,";
    m_sData[20] = "src09,,None,";
    m_sData[21] = "src10,,None,";
    m_sData[22] = "src11,,None,";
    m_sData[23] = "src12,,None,";
    m_sData[24] = "src13,,None,";
    m_sData[25] = "src14,,None,";
    m_sData[26] = "src15,,None,";
    m_sData[27] = "src16,,Test,Pattern";
    m_sData[28] = "enabl,0000000000000000";
    m_sData[29] = "zoom-,0000000000000000";
    m_sData[30] = "dstyp,000000";
    m_sData[31] = "audio,0";
    m_sData[32] = "codec,0";
    m_sData[33] = "dcss-,0";
    m_sData[34] = "ipod-,0";
    m_sData[35] = "skylt,0,0";
    //m_sData[36] = "slav7,0,0";
    //m_sData[37] = "slav8,0,0";
    m_sData[36] = "dsply,1";
    m_sData[37] = "serl#,Unassigned";
    m_sData[38] = "name-,OR-1";
    m_sData[39] = "passw,3699";
    m_sData[40] = "timeo,0";
    m_sData[41] = "quad-,0";
    m_sData[42] = "detec,1";
    m_sData[LNX_IDEX_43_ORPH] = "orph-,,"; //6.1 change "swtyp,0" to "orph-,,". Expand from 1 data field to 2 used to configure Orpheus.
    m_sData[LNX_IDEX_44_EMAIL] = "email,0";
    m_sData[LNX_IDEX_45_TYPSW] = "typsw,0";            // 2022-09-07 ---- IPS4000 support

    // HUH? dunno why the shift, but...
    for(int i=46; i > 0; i--)           // "   "    ---- 46, was 45
    {
        m_sData[i] = m_sData[i -1];
    }

    m_sData[0] = "";

    //Disable 700A Here
    int row = ui->CaptureCombo->findText("IPS700A");
    qobject_cast<QStandardItemModel*> (ui->CaptureCombo->model())->item(row)->setEnabled(false);
    //Disable 700A Here

    TryToReadConfig();

    ParseFile();

    ui->tabWidget->lower();

    ui->tabWidget->setCurrentIndex(0);//Show blank tab behing "always required controls"

    //ui->RX_MAC_1->setCursorPosition(0);

    m_RegExValidateMAC.setRegExp(QRegExp("^([0-9A-Fa-f]{2}){5}([0-9A-Fa-f]{2})$"));//Allow only the hex characters used to construct MAC address

    for(int i = LOWEST_POSSIBLE_VYNET_DEVICE_INDEX; i <= HIGHEST_POSSIBLE_VYNET_DEVICE_INDEX; i++)
    {
        sRX_MAC[i]->setValidator(&m_RegExValidateMAC);
        sTX_MAC[i]->setValidator(&m_RegExValidateMAC);
    }

    TryToReadVynetFile();
}

void MainWindow::TryToReadConfig()
{
    QFile myFi(ConfigFileName);
    if(myFi.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        return;

    for(int i = 1; i<46; i++)
    {
        m_sData[i] = myFi.readLine();
        m_sData[i].replace("\n","");
    }
}

void MainWindow::TryToReadVynetFile()
{
    QFile myFi(VynetFileName);
    if(myFi.open(QIODevice::ReadOnly | QIODevice::Text) == false)
        return;

    QString sTempInt;
    int iTemp;
    int iDex;

    iDex = 1;

    while (!myFi.atEnd()) {
        m_saVynetContents[iDex] = myFi.readLine();

        m_saVynetContents[iDex].remove("\r");
        m_saVynetContents[iDex].remove("\n");

        if(m_saVynetContents[iDex].left(2) == "TX")//iDex <= 16
        {
            sTempInt = m_saVynetContents[iDex].section(',',0,0);
            iTemp = sTempInt.right(2).toInt();

            if(iTemp < LOWEST_POSSIBLE_VYNET_DEVICE_INDEX || iTemp > HIGHEST_POSSIBLE_VYNET_DEVICE_INDEX)
                continue;

            sTX_MAC[iTemp]->setText(m_saVynetContents[iDex].section(',',1,1));
        }
        else if(m_saVynetContents[iDex].left(2) == "RX")
        {
            sTempInt = m_saVynetContents[iDex].section(',',0,0);
            iTemp = sTempInt.right(2).toInt();

            if(iTemp < LOWEST_POSSIBLE_VYNET_DEVICE_INDEX || iTemp > HIGHEST_POSSIBLE_VYNET_DEVICE_INDEX)
                continue;

            sRX_MAC[iTemp]->setText(m_saVynetContents[iDex].section(',',1,1));

            //comboRXScaleType[iTemp]->setCurrentText(m_saVynetContents[iDex].section(',',2,2));

        }

        ++iDex;
    }


    //return true;


}

void MainWindow::ParseFile()
{
   QString sTemp;

   for(int i = 1; i < NumberOfMonitors + 1; i++)
   {
       sTemp = StringWOToken(m_sData[i]);
       QStringList listLocal = sTemp.split(',');
       sMonName[i]->setText(listLocal.at(0));
   }

   //Move this logic below so Source configuration can override Monitor configuration
   //sTemp = StringWOToken(m_sData[31]);
   //for(int i = 0; i<6; i++)
   //    comboSrcMonType[i + 1]->setCurrentIndex(sTemp[i].digitValue());

   for(int i = 1; i < 17; i++)
   {

       sTemp = StringWOToken(m_sData[NumberOfMonitors + i]);
       QStringList listLocal = sTemp.split(',');

       //comboSrcType[i]->setCurrentText(listLocal.at(0));
       sSrcNameTop[i]->setText(listLocal.at(1));
       sSrcNameBot[i]->setText(listLocal.at(2));

   }

   //Move this logic down here so Source configuration can override Monitor configuration
   sTemp = StringWOToken(m_sData[31]);
   for(int i = 0; i<6; i++)
   {
       if(comboSrcMonType[i + 1]->isEnabled())
            comboSrcMonType[i + 1]->setCurrentIndex(sTemp[i].digitValue());
   }

   //Move this logic here so Source configuration can override Monitor congiguration

   ui->OrphStation->setEnabled(false);
   ui->OrpheusServer->setEnabled(false);

   sTemp = StringWOToken(m_sData[34]);

   if(sTemp[0].digitValue() >= 0 && sTemp[0].digitValue() <= MaxNumberOfCaptureOptions)
    ui->CaptureCombo->setCurrentIndex(sTemp[0].digitValue());

   sTemp = StringWOToken(m_sData[36]);

   if(sTemp.count(',') == 1)
   {
       //Set this (Light control 1)first it can be overridden by state of Light Control 1
       if(sTemp.section(',',1,1)[0].digitValue() >= 0 && sTemp.section(',',1,1)[0].digitValue() <= 3)
           buttonGroup2->button(sTemp.section(',',1,1)[0].digitValue())->setChecked(true);

       if(sTemp.section(',',0,0)[0].digitValue() >= 0 && sTemp.section(',',0,0)[0].digitValue() <= 3)
           ui->buttonGroup->button(sTemp.section(',',0,0)[0].digitValue())->click();
       else //If there is an invalid entry in 2 controller format the interface will show "0 Lights"
           ui->buttonGroup->button(0)->click();
   }
   else if(sTemp.count(',') == 0)//In case someone feeds in a legacy file in one controller format
   {
       if(sTemp[0].digitValue() >= 0 && sTemp[0].digitValue() <= 3)
           ui->buttonGroup->button(sTemp[0].digitValue())->click();
       else //If there is an invalid entry in a legacy file (that suppoorted only 1 controller) the interface will show "0 Lights"
           ui->buttonGroup->button(0)->click();
   }
   else//If there is an invalid entry that is not consistent with current or legacy format the interface will show "0 Lights"
       ui->buttonGroup->button(0)->click();

    ui->SerialNumlineEdit->setText(StringWOToken(m_sData[LNX_IDEX_37_SERL]));
    ui->SysNamelineEdit->setText(StringWOToken(m_sData[LNX_IDEX_38_NAME]));
    ui->PassWrdlineEdit->setText(StringWOToken(m_sData[LNX_IDEX_39_PASSW]));

    sTemp = m_sData[LNX_IDEX_43_ORPH].left(5);

    if(sTemp == "swtyp")
        m_sData[LNX_IDEX_43_ORPH] = "orph-,,";

    if(m_sData[LNX_IDEX_43_ORPH].count(',') == 2)
    {
        ui->OrphStation->setText(m_sData[LNX_IDEX_43_ORPH].section(',',1,1));
        ui->OrpheusServer->setText(m_sData[LNX_IDEX_43_ORPH].section(',',2,2));
    }

    //ui->SwitchIPAddr
}

QString MainWindow::StringWOToken(QString sVal)
{
    QString sTemp;
    sTemp = sVal;
    sTemp.remove(0,6);

    return sTemp;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox my;
    QString sTemp,sTemp2;
    QFile myFi(ConfigFileName);

    myFi.open(QIODevice::WriteOnly | QIODevice::Text);


    for(int i = 1; i < 13; i++)
    {
       sMonName[i]->setText(sMonName[i]->text().remove(","));
       m_sData[i].sprintf("mon%02i",i);
       m_sData[ i ] +=  "," +  sMonName[i]->text();
    }

    for(int i = 1; i < 17; i++)
    {
       sSrcNameTop[i]->setText(sSrcNameTop[i]->text().remove(","));
       sSrcNameBot[i]->setText(sSrcNameBot[i]->text().remove(","));
       m_sData[i + 12].sprintf("src%02i",i);
       m_sData[ i +12] +=  "," + comboSrcType[i]->currentText() + "," +  sSrcNameTop[i]->text() + "," + sSrcNameBot[i]->text();
    }

    sTemp = "dstyp,";

    for(int i = 1; i < 7; i++)
    {
        QString sLocal;
        sLocal.sprintf("%i",comboSrcMonType[i]->currentIndex());
        //sTemp2.number(comboSrcMonType[i]->currentIndex());
        sTemp = sTemp + sLocal;
    }

    m_sData[LNX_IDEX_30_DSTYP] = sTemp;

    //If saving a valid two light configuration, Codec should default to off.
    if((ui->buttonGroup->checkedId() > 0) && (buttonGroup2->checkedId() > 0))
        m_sData[33] = "codec,0";

    sTemp = "dcss-,";
    sTemp2.sprintf("%i",ui->CaptureCombo->currentIndex());

    m_sData[LNX_IDEX_33_DSCC] = sTemp + sTemp2;

    m_sData[LNX_IDEX_35_SKYLT] = "skylt," + ui->buttonGroup->checkedButton()->text() + "," + buttonGroup2->checkedButton()->text();

    ui->SerialNumlineEdit->setText(ui->SerialNumlineEdit->text().remove(","));
    m_sData[LNX_IDEX_37_SERL] = "serl#," + ui->SerialNumlineEdit->text();

    ui->SysNamelineEdit->setText(ui->SysNamelineEdit->text().remove(","));
    m_sData[LNX_IDEX_38_NAME] ="name-," + ui->SysNamelineEdit->text();

    ui->PassWrdlineEdit->setText(ui->PassWrdlineEdit->text().remove(","));
    m_sData[LNX_IDEX_39_PASSW] = "passw," + ui->PassWrdlineEdit->text();

    ui->OrphStation->setText(ui->OrphStation->text().remove(","));
    ui->OrpheusServer->setText(ui->OrpheusServer->text().remove(","));
    m_sData[LNX_IDEX_43_ORPH] = "orph-," + ui->OrphStation->text() + "," + ui->OrpheusServer->text();

    // 2022-09-07: support for IPS4000
    //ui->IP_addr->setText();
    m_sData[LNX_IDEX_45_TYPSW] = "typsw,," + ui->SwitchIPAddr->text();

    for(int i = 1; i < 46; i++)
    {
        myFi.write(m_sData[i].toUtf8());
        myFi.write("\n");
    }



    myFi.close();

    my.setText("File Saved");
    my.exec();

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(ui->comboBox->currentIndex() > 0)
        ui->CaptureCombo->setCurrentIndex(0);

    ProcessSrcTypeCombo(ui->comboBox, arg1);
}

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_2, arg1);
}



void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_3, arg1);
}

void MainWindow::ProcessSrcTypeCombo(QComboBox* pCurCombo,const QString &sSrcNm)
{
    QComboBox* pmyCombo;

    pmyCombo = mMap.value(sSrcNm.right(4));


    if(mMap.contains(sSrcNm.right(4)) && pmyCombo != pCurCombo)

    {

        if(pmyCombo->currentText().right(4) == sSrcNm.right(4))
        {
            pmyCombo->blockSignals(true);
            //pmyCombo->setCurrentText("");
            pmyCombo->setEditText("");
             pmyCombo->blockSignals(false);
        }

    }


    mMap.insert(pCurCombo->currentText().right(4),pCurCombo);

    //If SCAM4 is selected for any Source disable control for Monitor 4
    comboSrcMonType[4]->setEnabled(TypeIsNotSelectedForAnySrc("SCAM4"));

    //If SCAM5 is selected for any Source disable control for Monitor 5
    comboSrcMonType[5]->setEnabled(TypeIsNotSelectedForAnySrc("SCAM5"));

    //If SCAM6 is selected for any Source disable control for Monitor 6
    comboSrcMonType[6]->setEnabled(TypeIsNotSelectedForAnySrc("SCAM6"));

}

void MainWindow::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_4, arg1);
}

void MainWindow::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_5, arg1);
}

void MainWindow::on_comboBox_6_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_6, arg1);
}

void MainWindow::on_comboBox_7_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_7, arg1);
}

void MainWindow::on_comboBox_8_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_8, arg1);
}

void MainWindow::on_comboBox_9_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_9, arg1);
}

void MainWindow::on_comboBox_10_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_10, arg1);
}

void MainWindow::on_comboBox_11_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_11, arg1);
}

void MainWindow::on_comboBox_12_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_12, arg1);
}

void MainWindow::on_comboBox_13_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_13, arg1);
}

void MainWindow::on_comboBox_14_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_14, arg1);
}

void MainWindow::on_comboBox_15_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_15, arg1);
}

void MainWindow::on_comboBox_16_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_16, arg1);
}

void MainWindow::HideSaveLabel()
{

}

void MainWindow::on_pushButton_pressed()
{

}

void MainWindow::on_pushButton_released()
{

}

void MainWindow::on_CaptureCombo_currentIndexChanged(int index)
{
    if(index > 0)
        ui->comboBox->setCurrentIndex(0);

    if(index == 3 || index == 4)
    {
        ui->OrphStation->setEnabled(true);
        ui->OrpheusServer->setEnabled(true);

        ui->label_10->setText("Orpheus \nStation Name:");
        ui->label_11->setText("Orpheus \nServer hostname or ip address:");
    }
    else if(index == 5)
    {
        ui->OrphStation->setEnabled(false);
        ui->OrpheusServer->setEnabled(true);

        ui->label_10->setText("");
        ui->label_11->setText("IPS710A \nhostname or ip address:");
    }
    else if(index == 6)
    {
        ui->OrphStation->setEnabled(false);
        ui->OrpheusServer->setEnabled(true);

        ui->label_10->setText("");
        ui->label_11->setText("MedEx \nhostname or ip address:");
    }
    else
    {
        ui->OrphStation->setEnabled(false);
        ui->OrpheusServer->setEnabled(false);

        ui->label_10->setText("");
        ui->label_11->setText("");
    }
}

bool MainWindow::TypeIsNotSelectedForAnySrc(QString sType)
{
    for(int i = 1; i <= 16; i++)
    {
        if(comboSrcType[i]->currentText() == sType)
            return false;//Instance of Src type detected ergo it is false that this type is not selected
    }

    return true;    //Not found in Source combo test loop, ergo return true
}

void MainWindow::on_MonTypecomboBox_4_currentIndexChanged(const QString &arg1)
{
    bool bState;

    if(arg1 == "")
        bState = true;
    else
        bState = false;

    //Disable SCAM4 Here
    for(int i = 1; i<= 16; i++)
    {
    int row = comboSrcType[i]->findText("SCAM4");
    qobject_cast<QStandardItemModel*> (comboSrcType[i]->model())->item(row)->setEnabled(bState);
    }
    //Disable SCAM4 Here
}

void MainWindow::on_MonTypecomboBox_5_currentIndexChanged(const QString &arg1)
{
    bool bState;

    if(arg1 == "")
        bState = true;
    else
        bState = false;

    //Disable SCAM5 Here
    for(int i = 1; i<= 16; i++)
    {
    int row = comboSrcType[i]->findText("SCAM5");
    qobject_cast<QStandardItemModel*> (comboSrcType[i]->model())->item(row)->setEnabled(bState);
    }
    //Disable SCAM5 Here
}

void MainWindow::on_MonTypecomboBox_6_currentIndexChanged(const QString &arg1)
{
    bool bState;

    if(arg1 == "")
        bState = true;
    else
        bState = false;

    //Disable SCAM6 Here
    for(int i = 1; i<= 16; i++)
    {
    int row = comboSrcType[i]->findText("SCAM6");
    qobject_cast<QStandardItemModel*> (comboSrcType[i]->model())->item(row)->setEnabled(bState);
    }
    //Disable SCAM6 Here
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
        ui->tabWidget->raise();
    else
        ui->tabWidget->lower();

    //ui->tabWidget->
}

void MainWindow::on_pushButton_2_clicked()
{
    QFile myFi(VynetFileName);


    myFi.open(QIODevice::WriteOnly | QIODevice::Text);

    for(int i = 1; i < 17; i++)
    {
       QString sTemp;

       sTemp.sprintf("TX%02i",i);

       sTemp = sTemp + "," + sTX_MAC[i]->text() + ",\n";

       myFi.write(sTemp.toUtf8());
    }

    for(int i = 1; i < 17; i++)
    {
       QString sTemp;
       //sMonName[i]->setText(sMonName[i]->text().remove(","));

       sTemp.sprintf("RX%02i",i);

       if(sRX_MAC[i]->text() != "")
        sTemp = sTemp + "," + sRX_MAC[i]->text() + ","+ comboRXScaleType[i]->currentText() + "\n";
       else
        sTemp = sTemp + ",,\n";

       myFi.write(sTemp.toUtf8());
    }

}

void MainWindow::on_radioButton_clicked()
{
    buttonGroup2->button(0)->setChecked(true);

    ui->groupBox_2->hide();
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->groupBox_2->show();
}

void MainWindow::on_radioButton_3_clicked()
{
   ui->groupBox_2->show();
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->groupBox_2->show();
}

void MainWindow::on_SwitchCombo_currentIndexChanged(int index)
{
    if(index == 0)
    {
        // do nothing
    }
    if(index == 1)
    {
        // for the IPS4000 switch
        ui->IP_addr->setText("IP Address:");
        //ui->IPADDRLineEdit->
    }
    if(index == 2)
    {
        // Opticis
    }
    if(index == 3)
    {
        // Ophit
    }
}


