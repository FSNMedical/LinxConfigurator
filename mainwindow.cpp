//
// mainwindow.cpp
//
// LinxConfigurator.cpp
//
// 2022-10-27 Considerable changes:
//  1. Moved this to Linux, mostly because it was of the inability to consistently
//     building a statically linked executable under Windows.
//  2. There was a very bad and dangerous habit of using magic number instead of
//     #define'd constants. There was even a complete list of #define'd constants
//     (prefix LNX_IDEX_), but that wasn't used. That habit inadvertently caused
//     problems when new line entries were changed/added/deleted. The code was
//     changed considerably in order to sync it back up with the named constants.
//
// Lots of work will be needed in order to really clean this up.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QFile"

#include <QStandardItemModel>

// We SHOULD take out Vynet references if we are NOT going to support it
#define VynetFileName "VyNet.CSV"
#define LOWEST_POSSIBLE_VYNET_DEVICE_INDEX 1
#define HIGHEST_POSSIBLE_VYNET_DEVICE_INDEX 16

const char *sysGenXDir = "/.GenX/";         //! \var  All configuration files are located HERE
const char *ConfigFileName = "LINXConfig.txt";

#define DefaultIPAddress     "192.168.0.170"

#define     DBG_CFG

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
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

    buttonGroup2 = new QButtonGroup();
    buttonGroup2->addButton(ui->radioButton_5,0);
    buttonGroup2->addButton(ui->radioButton_6,1);
    buttonGroup2->addButton(ui->radioButton_7,2);
    buttonGroup2->addButton(ui->radioButton_8,3);
    buttonGroup2->button(0)->setChecked(true);


    // wehn user puts in new IP address for switch
    // BUG in Qt API: No such a signal "textEdited"
    //connect(ui->SwitchIPAddr,SIGNAL(textEdited(QString)),this, SLOT(on_new_IPaddr(QString)));

    //Disable 700A Here
    int row = ui->CaptureCombo->findText("IPS700A");
    qobject_cast<QStandardItemModel*> (ui->CaptureCombo->model())->item(row)->setEnabled(false);
    //Disable 700A Here

    bool    bStatus = TryToReadConfig();
    if(bStatus == false)
    {
        // corrupt or missing
        m_bExistingCfgFile = false;
        printf("Could not find LINXConfig.txt file, so must fill in defaults\n");
        FillInDefaults();
        // fill in the defaults for the IPS4000 if no original linxcfg
        ui->SwitchCombo->setCurrentText("IPS4000");
        m_sSwitchIPAddr = DefaultIPAddress;
        ui->SwitchIPAddr->setText(m_sSwitchIPAddr);     // fill in the default IP addr
    }
    else
    {
        m_bExistingCfgFile = true;
    }

    ParseFile();

    ui->tabWidget->lower();
    ui->tabWidget->setCurrentIndex(0);//Show blank tab behing "always required controls"

    m_RegExValidateMAC.setRegExp(QRegExp("^([0-9A-Fa-f]{2}){5}([0-9A-Fa-f]{2})$"));//Allow only the hex characters used to construct MAC address

    for(int i = LOWEST_POSSIBLE_VYNET_DEVICE_INDEX; i <= HIGHEST_POSSIBLE_VYNET_DEVICE_INDEX; i++)
    {
        sRX_MAC[i]->setValidator(&m_RegExValidateMAC);
        sTX_MAC[i]->setValidator(&m_RegExValidateMAC);
    }

}

// ----------------------------------------------------------------------------
//
// TODO: I have to get rid of this Pascalism - the index starting at 1 - it has
// caused nothing but grief
//
bool MainWindow::TryToReadConfig()
{
    printf("TryToReadConfig ***   \n");

    // Form the complete pathname.
    char    *h_path = getenv("HOME");
    QString dirCheck = QString::fromUtf8(h_path) + sysGenXDir;
    if(QDir(dirCheck).exists() == false)
    {
        printf("Error! cannot find the .GenX folder!\n");
        return false;
    }
    QString fullpath = dirCheck + ConfigFileName;
    QFile myFi(fullpath);
    if(myFi.open(QIODevice::ReadWrite | QIODevice::Text) == false)
    {
        printf("Error! cannot find the LINXConfig.txt!\n");
        printf("\t Error = %s\n", strerror(errno));
        return false;
    }

    for(int i = 0; i<N_LNX_IDEX_MAX; i++)
    {
        if(myFi.atEnd())
        {
            std::cout << "Error in reading config file - we're at a premature end!\n";
            return false;
        }
        m_sData[i] = myFi.readLine();
        m_sData[i].replace("\n","");        // strip out the newline. parsing requires that.

        //   printf(" line read in = %s\n", m_sData[i].toStdString().c_str());

        // WE MUST do a basic sanity check in the event that the file has been
        // incorrectly edited!!! Throw this away if error

        if(i >= LNX_IDEX_00_MN1 && i <= LNX_IDEX_11_MN12)
        {
            // check for "mon"
            if(m_sData[i].startsWith(("mon")) == false)
            {
                printf("Tossing cfg file - bad config file!\n");
                return false;
            }
        }
        if(i >= LNX_IDEX_12_SR1 && i <= LNX_IDEX_27_SR16)
        {
            // check for "src"
            if(m_sData[i].startsWith(("src")) == false)
            {
                printf("Tossing cfg file - bad config file!\n");
                return false;
            }
        }
        if(i == LNX_IDEX_28_ENAB)
        {
            if(m_sData[i].startsWith("enab") == false)
            {
                printf("Tossing cfg file - bad config file!\n");
                return false;
            }
        }
        if(i == LNX_IDEX_45_TYPSW)
        {
            if(m_sData[i].startsWith("typsw") == false)
            {
                printf("Tossing cfg file - bad config file!\n");
                return false;
            }

            // There is a switch --- check for validity, fill in IP address

            QString sTempInt = m_sData[i].section(',',1,1);

            int iTemp = sTempInt.right(1).toInt();

            // Get the Switch number from the linx config file
            switch(iTemp)
            {
            case    TYPE_SWITCH_NONE:
            case    TYPE_SWITCH_OPHIT:
            case    TYPE_SWITCH_OPTICIS:
            case    TYPE_SWITCH_IPS4000:
                m_nSwitchNum = iTemp;
                // Fill in the Switch IP
                m_sSwitchIPAddr = m_sData[i].section(',',2,2);
                printf("Found switch info: switch = %d, IP addr = %s\n ",
                       m_nSwitchNum, m_sSwitchIPAddr.toStdString().c_str());

                // ugly way of finding the combobox index.. will fix
                int cIdx;
                switch(m_nSwitchNum)
                {
                    case    TYPE_SWITCH_NONE:
                    default:
                        std::cout << "\t found TYPE_SWITCH_NONE\n";
                        cIdx = 0;
                        break;
                    case    TYPE_SWITCH_IPS4000:
                        std::cout << "\t found TYPE_SWITCH_IPS4000\n";
                        ui->SwitchIPAddr->setText(m_sSwitchIPAddr); // set the Switch IP address
                        cIdx = 1;
                        break;
                    case    TYPE_SWITCH_OPTICIS:
                        std::cout << "\t found TYPE_SWITCH_OPTICIS\n";
                        cIdx = 2;
                        break;
                    case    TYPE_SWITCH_OPHIT:
                        std::cout << "\t found TYPE_SWITCH_OPHIT\n";
                        cIdx = 3;
                        break;
                }

                ui->SwitchCombo->setCurrentIndex(m_nSwitchNum);
                if(cIdx == 1)
                {
                    ui->SwitchCombo->setCurrentText("IPS4000");
                }
                break;
            default:
                printf("Tossing cfg file - bad config file!\n");
                return false;
            }
        }
    }
    return true;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void    MainWindow::FillInDefaults()
{
    printf("FillInDefaults \n");

    // Monitors:
    m_sData[LNX_IDEX_00_MN1] = "mon01,Monitor 1";
    m_sData[LNX_IDEX_01_MN2] = "mon02,Monitor 2";
    m_sData[LNX_IDEX_02_MN3] = "mon03,Monitor 3";
    m_sData[LNX_IDEX_03_MN4] = "mon04,Monitor 4";
    m_sData[LNX_IDEX_04_MN5] = "mon05,Monitor 5";
    m_sData[LNX_IDEX_05_MN6] = "mon06,Monitor 6";
    m_sData[LNX_IDEX_06_MN7] = "mon07,Monitor 7";
    m_sData[LNX_IDEX_07_MN8] = "mon08,Monitor 8";
    m_sData[LNX_IDEX_08_MN9] = "mon09,Monitor 9";
    m_sData[LNX_IDEX_09_MN10] = "mon10,Monitor 10";
    m_sData[LNX_IDEX_10_MN11] = "mon11,Monitor 11";
    m_sData[LNX_IDEX_11_MN12] = "mon12,Monitor 12";

    // Sources
    m_sData[LNX_IDEX_12_SR1]  = "src01,,None,";
    m_sData[LNX_IDEX_13_SR2]  = "src02,,None,";
    m_sData[LNX_IDEX_14_SR3]  = "src03,,None,";
    m_sData[LNX_IDEX_15_SR4]  = "src04,,None,";
    m_sData[LNX_IDEX_16_SR5]  = "src05,,None,";
    m_sData[LNX_IDEX_17_SR6]  = "src06,,None,";
    m_sData[LNX_IDEX_18_SR7]  = "src07,,None,";
    m_sData[LNX_IDEX_19_SR8]  = "src08,,None,";
    m_sData[LNX_IDEX_20_SR9]  = "src09,,None,";
    m_sData[LNX_IDEX_21_SR10] = "src10,,None,";
    m_sData[LNX_IDEX_22_SR11] = "src11,,None,";
    m_sData[LNX_IDEX_23_SR12] = "src12,,None,";
    m_sData[LNX_IDEX_24_SR13] = "src13,,None,";
    m_sData[LNX_IDEX_25_SR14] = "src14,,None,";
    m_sData[LNX_IDEX_26_SR15] = "src15,,None,";
    m_sData[LNX_IDEX_27_SR16] = "src16,,Test,Pattern";

    m_sData[LNX_IDEX_28_ENAB] = "enabl,0000000000000000";
    m_sData[LNX_IDEX_29_ZOOM] = "zoom-,0000000000000000";
    m_sData[LNX_IDEX_30_DSTYP] = "dstyp,000000";
    m_sData[LNX_IDEX_31_AUDIO] = "audio,0";
    m_sData[LNX_IDEX_32_CODEC] = "codec,0";
    m_sData[LNX_IDEX_33_DSCC] = "dcss-,0";
    m_sData[LNX_IDEX_34_IPOD] = "ipod-,0";
    m_sData[LNX_IDEX_35_SKYLT] = "skylt,0,0";
    m_sData[LNX_IDEX_36_DSPLY] = "dsply,1";
    m_sData[LNX_IDEX_37_SERL] = "serl#,Unassigned";
    m_sData[LNX_IDEX_38_NAME] = "name-,OR-1";
    m_sData[LNX_IDEX_39_PASSW] = "passw,3699";
    m_sData[LNX_IDEX_40_TIMEO] = "timeo,0";
    m_sData[LNX_IDEX_41_QUAD] = "quad-,1";              // Must have this set! Backpages don't work correctly otherwise.
    m_sData[LNX_IDEX_42_DETEC] = "detec,1";

    m_sData[LNX_IDEX_43_ORPH] = "orph-,,";          //6.1 change "swtyp,0" to "orph-,,". Expand from 1 data field to 2 used to configure Orpheus.
    m_sData[LNX_IDEX_44_EMAIL] = "email,0";
    m_sData[LNX_IDEX_45_TYPSW] = "typsw,4," + QString(DefaultIPAddress);            // 2022-09-07 ---- IPS4000 support  0 means no switch

}

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
void MainWindow::ParseFile()
{
    QString sTemp;

    std::cout << "ParseFile:\n" << std::flush;
    std::cout << " ** doing monitors\n" << std::flush;

    QString sTempSwName;

    for(int i = 1; i <= NumberOfMonitors; i++)
    {
        // jeez, another off-by-one --- fix by -1
        //
        sTemp = StringWOToken(m_sData[i-1]);
        //printf(" sTemp = %s\n", sTemp.toStdString().c_str());

        QStringList listLocal = sTemp.split(',');
        if(listLocal.isEmpty())
        {
            printf(" listLocal is Empty! skipping\n");
            break;
        }
        sMonName[i]->setText(listLocal.at(0));
        //std::cout << "\t ** sMonName for " << i << " = " << sMonName[i]->text().toStdString() << "\n" << std::flush;
    }

    //std::cout << " ** doing sources\n" << std::flush;

    for(int i = 1; i <= MaxNumberOfSources; i++)
    {

        // jeez, another off-by-one --- fix by -1
        //
        sTemp = StringWOToken(m_sData[(NumberOfMonitors-1) + i]);
        //printf(" sTemp = %s\n", sTemp.toStdString().c_str());
        QStringList listLocal = sTemp.split(',');
        if(listLocal.isEmpty())
        {
            printf(" listLocal is Empty! skipping\n");
            break;
        }

        //comboSrcType[i]->setCurrentText(listLocal.at(0));
        sSrcNameTop[i]->setText(listLocal.at(1));
        sSrcNameBot[i]->setText(listLocal.at(2));
        //std::cout << "\t ** sSrcNameTop for " << i << " = " << sSrcNameTop[i]->text().toStdString() << "\n";
        //std::cout << "\t ** sSrcNameBot for " << i << " = " << sSrcNameBot[i]->text().toStdString() << "\n";

    }


    //Move this logic down here so Source configuration can override Monitor configuration
    // HUH?? What is 31 in this case??? SHIT!
    //sTemp = StringWOToken(m_sData[31]);
    sTemp = StringWOToken(m_sData[LNX_IDEX_30_DSTYP]);
    for(int i = 0; i<6; i++)
    {
        if(comboSrcMonType[i + 1]->isEnabled())
            comboSrcMonType[i + 1]->setCurrentIndex(sTemp[i].digitValue());
    }

    //Move this logic here so Source configuration can override Monitor congiguration

    ui->OrphStation->setEnabled(false);
    ui->OrpheusServer->setEnabled(false);

    //printf(" about to do the bizarre thiing on line 34... ??\n");

    // HUH?? What is 34 in this case??? SHIT!
    sTemp = StringWOToken(m_sData[34]);

    if(sTemp[0].digitValue() >= 0 && sTemp[0].digitValue() <= MaxNumberOfCaptureOptions)
        ui->CaptureCombo->setCurrentIndex(sTemp[0].digitValue());

    // What is number 36 supposed to be?
    //  THIS is the reason using named constants!
    //  36 is supposed to be dsply, but that could have changed
    //printf(" about to do the bizarre thiing on line 36... ??\n");
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

    // We do need to parse the Switch Type statement
    /*
    enum TYPE_OF_SWITCH{
        TYPE_SWITCH_NONE = 0,
        TYPE_SWITCH_OPHIT,      // 1
        TYPE_SWITCH_OPTICIS,    // 2
        TYPE_SWITCH_VYNET,      // 3
        TYPE_SWITCH_IPS4000     // 4        // 2021-12-13
    };
     */
    if(m_sData[LNX_IDEX_45_TYPSW].count(',') == 2)
    {
        int     nSwitchNum;
        QString qsSwitchName;
        // print diag message
        std::cout << "\t--> Switch statement, 2 sections found\n";
        //ui->SwitchCombo->set
        nSwitchNum = m_sData[LNX_IDEX_45_TYPSW].section(',',1,1).toInt();
        switch(nSwitchNum)
        {
            case TYPE_SWITCH_NONE:      qsSwitchName =""; break;
            case TYPE_SWITCH_OPHIT:     qsSwitchName = "Ophit"; break;
            case TYPE_SWITCH_OPTICIS:   qsSwitchName = "Opticis"; break;
            case TYPE_SWITCH_VYNET:     qsSwitchName = "Vynet"; break;
            case TYPE_SWITCH_IPS4000:   qsSwitchName = "IPS4000"; break;
        }

        ui->SwitchCombo->setCurrentText(qsSwitchName);
    }


    std::cout << "End of ParseFile.\n";

}

// ----------------------------------------------------------------------------
// HUH??? What does this?
// ----------------------------------------------------------------------------
QString MainWindow::StringWOToken(QString sVal)
{
    int     sz;
    sz = sVal.length();
    //std::cout << "StringWOToken sVal = " << sVal.toStdString() << " sz = " << sz << " \n" << std::flush;

    //printf(" Qstring sVal = %s, length = %d \n",sVal.toStdString().c_str(),sz );

    QString sTemp;
    if(sz >= 6)
    {
        sTemp = sVal;
        sTemp.remove(0,6);
    }
    else
    {
        printf(" Could not do op since string too small!\n");
    }

    return sTemp;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

// ----------------------------------------------------------------------------
// This will output the data to the LINXConfig.txt file
// ----------------------------------------------------------------------------
void MainWindow::on_pushButton_clicked()
{
    QMessageBox my;
    QString sTemp,sTemp2;


    // Form the complete pathname.
    char    *h_path = getenv("HOME");
    QString dirCheck = QString::fromUtf8(h_path) + sysGenXDir;
    if(QDir(dirCheck).exists() == false)
    {
        printf("Error! cannot find the .GenX folder!\n");
        return;
    }
    QString fullpath = dirCheck + ConfigFileName;

 #ifdef DBG_CFG
    printf("fullpath = %s\n",fullpath.toStdString().c_str());
 #endif

    QFile myFi(fullpath);
    if(myFi.open(QIODevice::ReadWrite | QIODevice::Text) == false)
    {
        printf("Error! cannot find the LINXConfig.txt!\n");
        printf("\t Error = %s\n", strerror(errno));
        return;
    }


    //myFi.open(QIODevice::WriteOnly | QIODevice::Text);

    for(int i = 1; i <= NumberOfMonitors; i++)
    {
       sMonName[i]->setText(sMonName[i]->text().remove(","));
       m_sData[i-1].sprintf("mon%02i",i);
       m_sData[ i-1 ] +=  "," +  sMonName[i]->text();
    }

    for(int i = 1; i <= MaxNumberOfSources; i++)
    {
       sSrcNameTop[i]->setText(sSrcNameTop[i]->text().remove(","));
       sSrcNameBot[i]->setText(sSrcNameBot[i]->text().remove(","));
       m_sData[i + NumberOfMonitors-1].sprintf("src%02i",i);
       m_sData[i + NumberOfMonitors-1] +=  "," + comboSrcType[i]->currentText() +
                           "," +  sSrcNameTop[i]->text() +
                           "," + sSrcNameBot[i]->text();
       //std::cout << "SRC i=" << i << " : " << m_sData[i + NumberOfMonitors-1].toStdString() << "\n" << std::flush;
    }

    // Missing: ENAB (enabl) & ZOOM
    // Just copy these over because they were forgotten
    // sanity check: is the following overwriting the last src??? comment out for grins.
    //m_sData[LNX_IDEX_28_ENAB] = "enabl,0000000000000000";
    m_sData[LNX_IDEX_29_ZOOM] = "zoom-,0000000000000000";


    sTemp = "dstyp,";

    for(int i = 1; i <= MaxNumberOfCaptureOptions; i++)
    {
        QString sLocal;
        sLocal.sprintf("%i",comboSrcMonType[i]->currentIndex());
        sTemp = sTemp + sLocal;
    }

    m_sData[LNX_IDEX_30_DSTYP] = sTemp;

    // Missing : 31 (AUDIO) and 32 (CODEC)
    // Just copy these over because they were forgotten
    m_sData[LNX_IDEX_31_AUDIO] = "audio,0";
    m_sData[LNX_IDEX_32_CODEC] = "codec,0";

    //If saving a valid two light configuration, Codec should default to off.
    if((ui->buttonGroup->checkedId() > 0) && (buttonGroup2->checkedId() > 0))
        m_sData[33] = "codec,0";

    sTemp = "dcss-,";
    sTemp2.sprintf("%i",ui->CaptureCombo->currentIndex());

    m_sData[LNX_IDEX_33_DSCC] = sTemp + sTemp2;

    // Where is 34???
    // Missing: 34 (IPOD) --- just copy over
    m_sData[LNX_IDEX_34_IPOD] = "ipod-,0";

    m_sData[LNX_IDEX_35_SKYLT] = "skylt," + ui->buttonGroup->checkedButton()->text() + "," + buttonGroup2->checkedButton()->text();

    // Where is 36??
    // Missing - just copy over to here
    m_sData[LNX_IDEX_36_DSPLY] = "dsply,1";


    ui->SerialNumlineEdit->setText(ui->SerialNumlineEdit->text().remove(","));
    m_sData[LNX_IDEX_37_SERL] = "serl#," + ui->SerialNumlineEdit->text();

    ui->SysNamelineEdit->setText(ui->SysNamelineEdit->text().remove(","));
    m_sData[LNX_IDEX_38_NAME] ="name-," + ui->SysNamelineEdit->text();

    ui->PassWrdlineEdit->setText(ui->PassWrdlineEdit->text().remove(","));
    m_sData[LNX_IDEX_39_PASSW] = "passw," + ui->PassWrdlineEdit->text();

    // Where is 40, 41, 42 ???????
    // Missing --- just copy over
    m_sData[LNX_IDEX_40_TIMEO] = "timeo,0";
    m_sData[LNX_IDEX_41_QUAD] = "quad-,1";              // always set!
    m_sData[LNX_IDEX_42_DETEC] = "detec,1";

    ui->OrphStation->setText(ui->OrphStation->text().remove(","));
    ui->OrpheusServer->setText(ui->OrpheusServer->text().remove(","));
    m_sData[LNX_IDEX_43_ORPH] = "orph-," + ui->OrphStation->text() + "," + ui->OrpheusServer->text();

    // ??? email line is missing --- maybe i need to just specify here?
    m_sData[LNX_IDEX_44_EMAIL] = "email,,";

    // 2022-09-07: support for IPS4000

    // We need to pick up any possible changes to the IP address from the GUI!
    m_sSwitchIPAddr = ui->SwitchIPAddr->text();
    if(m_nSwitchNum == TYPE_SWITCH_IPS4000)
    {
        m_sData[LNX_IDEX_45_TYPSW] = "typsw," + QString::number(m_nSwitchNum) + "," + m_sSwitchIPAddr;
    }
    else
    {
        m_sData[LNX_IDEX_45_TYPSW] = "typsw," + QString::number(m_nSwitchNum);
    }

    for(int i = 1; i <= N_LNX_IDEX_MAX; i++)
    {
        int stat, test = 0;
        if(i == N_LNX_IDEX_45_TYPSW)
        {
            // the problem with the weird extra line occurs at the end of the file
            test = 1;               // trigger breakpoint here

        }
        QString     mmm = m_sData[i-1] + "\n";
        QByteArray qa = mmm.toUtf8();
        stat = myFi.write(qa);

        std::cout << "***  " << m_sData[i-1].toStdString()
                << "\n" << std::flush;
    }

    myFi.close();

    my.setText("File Saved");
    my.exec();

}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    // WHY are we doing this?
    if(ui->comboBox->currentIndex() > 0)
    {
        ui->CaptureCombo->setCurrentIndex(0);
    }

    ProcessSrcTypeCombo(ui->comboBox, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_2, arg1);
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_3, arg1);
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_4, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_5, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_6_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_6, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_7_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_7, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_8_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_8, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_9_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_9, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_10_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_10, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_11_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_11, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_12_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_12, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_13_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_13, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_14_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_14, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_15_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_15, arg1);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_comboBox_16_currentIndexChanged(const QString &arg1)
{
    ProcessSrcTypeCombo(ui->comboBox_16, arg1);
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_CaptureCombo_currentIndexChanged(int index)
{
    std::cout << "on_CaptureCombo_currentIndexChanged    index=" << index << "\n";
    if(index > 0)                           // HUH??? Why??
    {
        ui->comboBox->setCurrentIndex(0);
    }
    else
    {
        ui->comboBox->setCurrentIndex(index);
    }

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

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
bool MainWindow::TypeIsNotSelectedForAnySrc(QString sType)
{
    for(int i = 1; i <= 16; i++)
    {
        if(comboSrcType[i]->currentText() == sType)
            return false;//Instance of Src type detected ergo it is false that this type is not selected
    }

    return true;    //Not found in Source combo test loop, ergo return true
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
        ui->tabWidget->raise();
    else
        ui->tabWidget->lower();

    //ui->tabWidget->
}


// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_radioButton_clicked()
{
    buttonGroup2->button(0)->setChecked(true);

    ui->groupBox_2->hide();
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_radioButton_2_clicked()
{
    ui->groupBox_2->show();
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_radioButton_3_clicked()
{
   ui->groupBox_2->show();
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_radioButton_4_clicked()
{
    ui->groupBox_2->show();
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
void MainWindow::on_SwitchCombo_currentIndexChanged(int index)
{
    if(index == 0)
    {
        // do nothing
        m_nSwitchNum = TYPE_SWITCH_NONE;
        m_sSwitchIPAddr ="";                    // clear out if not I4K
    }
    if(index == 1)
    {
        // for the IPS4000 switch
        //ui->IP_addr->setText("IP Address:");
        if(m_nSwitchNum != TYPE_SWITCH_IPS4000)
        {
            // file in the default IP address for the field
            ui->SwitchIPAddr->setText(DefaultIPAddress);
            m_sSwitchIPAddr = DefaultIPAddress;
        }
        m_nSwitchNum = TYPE_SWITCH_IPS4000;
    }
    if(index == 2)
    {
        // Opticis
        m_nSwitchNum = TYPE_SWITCH_OPTICIS;
        m_sSwitchIPAddr = "";                    // clear out if not I4K
    }
    if(index == 3)
    {
        // Ophit
        m_nSwitchNum = TYPE_SWITCH_OPHIT;
        m_sSwitchIPAddr = "";                    // clear out if not I4K
    }
}

// Moving VyNet items down here, since we are not really using this now...

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
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

// ----------------------------------------------------------------------------
/*
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

       sTemp.sprintf("RX%02i",i);

       if(sRX_MAC[i]->text() != "")
        sTemp = sTemp + "," + sRX_MAC[i]->text() + ","+ comboRXScaleType[i]->currentText() + "\n";
       else
        sTemp = sTemp + ",,\n";

       myFi.write(sTemp.toUtf8());
    }

}
 */

// The following are currently disabled - don't know what they were supposed to be,
// but leaving in here, commented out
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
//void MainWindow::on_pushButton_pressed()
//{
//
//}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
//void MainWindow::on_pushButton_released()
//{
//
//}
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
//void MainWindow::HideSaveLabel()
//{
//
//}

