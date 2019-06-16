#include "AppSettings.h"
#include "ui_AppSettings.h"

AppSettings::AppSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppSettings)
{
    ui->setupUi(this);

    ui->lstProc->setStyleSheet("QListWidget{background-color:rgb(237, 242, 244); border: 1px solid rgb(228, 159, 92);}"
                      "QListWidget::item:selected{background-color:rgb(46,46,46); color:rgb(228, 159, 92); border: 0px;}"
                      "QListWidget::item:hover{background-color:rgb(46,46,46); color:rgb(228, 159, 92);border: 0px;}");

    ui->lstProc->setGeometry(QRect(10,80,681,451));
    ui->lstProc->setMovement(QListView::Movement::Static);
    ui->lstProc->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    ui->editWidget->setVisible(false);
    ui->editWidget->setGeometry(ui->lstProc->geometry());

    InitBoxes();

    // Create filepath
    AllocateFileNames();

    // load dumps
    LoadDumps();

    //InitSocket();
}

AppSettings::~AppSettings()
{
    DeallocateFileNames();
    //DestroySocket();
    delete ui;
}

void AppSettings::InitBoxes()
{
    int z = 110;
    for (size_t i = 0; i < 24; ++i )
    {
        _day1boxes[i] = new QCheckBox(ui->editWidget);
        _day1boxes[i]->setGeometry(QRect(z,110,16,19));

        _day2boxes[i] = new QCheckBox(ui->editWidget);
        _day2boxes[i]->setGeometry(QRect(z,130,16,19));

        _day3boxes[i] = new QCheckBox(ui->editWidget);
        _day3boxes[i]->setGeometry(QRect(z,150,16,19));

        _day4boxes[i] = new QCheckBox(ui->editWidget);
        _day4boxes[i]->setGeometry(QRect(z,170,16,19));

        _day5boxes[i] = new QCheckBox(ui->editWidget);
        _day5boxes[i]->setGeometry(QRect(z,190,16,19));

        _day6boxes[i] = new QCheckBox(ui->editWidget);
        _day6boxes[i]->setGeometry(QRect(z,210,16,19));

        _day7boxes[i] = new QCheckBox(ui->editWidget);
        _day7boxes[i]->setGeometry(QRect(z,230,16,19));

        z += 20;
    }
}

void AppSettings::LoadDumps()
{
    ProcessPool pool;
    size_t sz;

    // load names for all days
    if ((pool._names = _procNamesDmp.LoadArray(fNamesPath[0], &sz)) != nullptr)
    {
        for (size_t i = 0; i < sz; ++i)
        {
            QString s = QString::fromLatin1(pool._names[i].c_str(), strlen(pool._names[i].c_str()) );
            _names.push_back(s.toStdString());
        }
    }

    // show names
    for (size_t i = 0; i < _names.size(); ++i)
    {
        ui->lstProc->addItem(QString::fromStdString(_names.at(i).c_str()));
    }

    // load array of int (Data dumper don't work for std::vector<int> loading)
    FILE* fp;
    for (size_t i = 0; i < 7; ++i)
    {
        fp = fopen(fHflgPath[i], "rb");
        if (fp)
        {
            fread(&sz, sizeof(size_t), 1, fp);
            std::vector<int> o(sz);
            fread( (char*)&o[0], sz , sizeof( int ), fp );
            for (size_t j = 0; j < sz; ++j)
            {
                _hFlgs[i].push_back( o[j] );
            }
        }
    }

    _procNamesDmp.Free();
    _procHflgDmp.Free();
}

bool AppSettings::InitSocket()
{
#if PLATFORM == PLATFORM_WINDOWS
    WSADATA WsaData;
    if (WSAStartup(MAKEWORD(2, 2), &WsaData) != NO_ERROR)
    {
        printf("Faild to initialize wsa startup!\n");
    }
#else
#endif

    struct sockaddr_in _address;

    // create listener socket commands from manager
    _socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_socket < 0)
    {
        return false;
    }

    // setup address struct params
    _address.sin_family = AF_INET;
    _address.sin_port   = htons(1234);
    _address.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // local machine
    if (::connect(_socket, (struct sockaddr*)&_address, sizeof(_address)) < 0)
    {
        return false;
    }
}

void AppSettings::DestroySocket()
{
#if PLATFORM == PLATFORM_WINDOWS
    ::closesocket(_socket);
    WSACleanup();
#else
    ::close(_socket);
#endif
}

bool AppSettings::SendMessageToService()
{
    char buffer[5];
    char message[5] = "UPDD"; // Update data
    ::send(_socket, message, sizeof(message), 0);

    ::recv(_socket, buffer, sizeof(buffer), 0);
    if (!strcmp(buffer, "done"))
        return true;

    return false;
}

void AppSettings::on_btEdit_clicked()
{
    QListWidgetItem* w = ui->lstProc->currentItem();
    if (w)
    {
        for (size_t i = 0; i < _names.size(); ++i)
        {
            if (_selectedApp.toStdString() == _names[i])
            {
                int bit1 = _hFlgs[1].at(i); // first day flag of i process
                int bit2 = _hFlgs[2].at(i); // first day flag of i process
                int bit3 = _hFlgs[3].at(i); // first day flag of i process
                int bit4 = _hFlgs[4].at(i); // first day flag of i process
                int bit5 = _hFlgs[5].at(i); // first day flag of i process
                int bit6 = _hFlgs[6].at(i); // first day flag of i process
                int bit7 = _hFlgs[0].at(i); // first day flag of i process

                for (int j = 0; j < 24; ++j)
                {
                    _day1boxes[j]->setChecked(GetBitInInt(bit1, j));
                    _day2boxes[j]->setChecked(GetBitInInt(bit2, j));
                    _day3boxes[j]->setChecked(GetBitInInt(bit3, j));
                    _day4boxes[j]->setChecked(GetBitInInt(bit4, j));
                    _day5boxes[j]->setChecked(GetBitInInt(bit5, j));
                    _day6boxes[j]->setChecked(GetBitInInt(bit6, j));
                    _day7boxes[j]->setChecked(GetBitInInt(bit7, j));
                }
            }
        }

        ui->btAdd->setEnabled(false);
        ui->btEdit->setEnabled(false);
        ui->btRemove->setEnabled(false);
        ui->lstProc->setVisible(false);
        ui->editWidget->setVisible(true);
        ui->editWidget->raise();
    }
    else
    {
        QMessageBox msg;
        msg.setText("Спочатку виберіть програму!");
        msg.exec();
    }
}

void AppSettings::on_btAdd_clicked()
{
    QString fname = QFileDialog::getOpenFileName(this, "Додати програму", "", "All files (*.*)");
    QFileInfo qf(fname);

    ui->lstProc->addItem(qf.fileName());
    _names.push_back(qf.fileName().toStdString());

    for (size_t i = 0; i < 7; ++i)
    {
        _hFlgs[i].push_back(0);
    }
}

void AppSettings::on_btBack_clicked()
{
    ui->editWidget->setVisible(false);
    ui->btAdd->setEnabled(true);
    ui->btEdit->setEnabled(true);
    ui->btRemove->setEnabled(true);
    ui->lstProc->setVisible(true);
    ui->lstProc->raise();
}

void AppSettings::on_btSave_clicked()
{
    for (size_t i = 0; i < _names.size(); ++i)
    {
        if (_selectedApp.toStdString() == _names[i])
        {
            for (int j = 0; j < 24; ++j)
            {
                if (_day7boxes[j]->isChecked())
                    _hFlgs[0].at(i) = SetBitInInt(_hFlgs[0].at(i), j);
                else
                    _hFlgs[0].at(i) = UnsetBitInInt(_hFlgs[0].at(i), j);

                if (_day1boxes[j]->isChecked())
                    _hFlgs[1].at(i) = SetBitInInt(_hFlgs[1].at(i), j);
                else
                    _hFlgs[1].at(i) = UnsetBitInInt(_hFlgs[1].at(i), j);

                if (_day2boxes[j]->isChecked())
                    _hFlgs[2].at(i) = SetBitInInt(_hFlgs[2].at(i), j);
                else
                    _hFlgs[2].at(i) = UnsetBitInInt(_hFlgs[2].at(i), j);

                if (_day3boxes[j]->isChecked())
                    _hFlgs[3].at(i) = SetBitInInt(_hFlgs[3].at(i), j);
                else
                    _hFlgs[3].at(i) = UnsetBitInInt(_hFlgs[3].at(i), j);

                if (_day4boxes[j]->isChecked())
                    _hFlgs[4].at(i) = SetBitInInt(_hFlgs[4].at(i), j);
                else
                    _hFlgs[4].at(i) = UnsetBitInInt(_hFlgs[4].at(i), j);

                if (_day5boxes[j]->isChecked())
                    _hFlgs[5].at(i) = SetBitInInt(_hFlgs[5].at(i), j);
                else
                    _hFlgs[5].at(i) = UnsetBitInInt(_hFlgs[5].at(i), j);

                if (_day6boxes[j]->isChecked())
                    _hFlgs[6].at(i) = SetBitInInt(_hFlgs[6].at(i), j);
                else
                    _hFlgs[6].at(i) = UnsetBitInInt(_hFlgs[6].at(i), j);
            }
        }
    }

    // hide panel
    ui->editWidget->setVisible(false);
    ui->btAdd->setEnabled(true);
    ui->btRemove->setEnabled(true);
    ui->btEdit->setEnabled(true);
    ui->lstProc->setVisible(true);
    ui->lstProc->raise();
}

void AppSettings::on_lstProc_clicked(const QModelIndex &index)
{
    _selectedApp = ui->lstProc->currentItem()->text().toStdString().c_str();
}

void AppSettings::on_btRemove_clicked()
{
    QListWidgetItem* w = ui->lstProc->currentItem();

    for (size_t i = 0; i < _names.size(); ++i)
    {
        if (_names[i] == w->text().toStdString())
        {
           _names.erase( _names.begin() + i);
           _hFlgs[0].erase( _hFlgs[0].begin() + i );
           _hFlgs[1].erase( _hFlgs[1].begin() + i );
           _hFlgs[2].erase( _hFlgs[2].begin() + i );
           _hFlgs[3].erase( _hFlgs[3].begin() + i );
           _hFlgs[4].erase( _hFlgs[4].begin() + i );
           _hFlgs[5].erase( _hFlgs[5].begin() + i );
           _hFlgs[6].erase( _hFlgs[6].begin() + i );
        }
    }

    delete w;
}

void AppSettings::on_btSelectAll_clicked()
{
    for (size_t i = 0; i < 24; ++i )
    {
        _day1boxes[i]->setChecked(true);
        _day2boxes[i]->setChecked(true);
        _day3boxes[i]->setChecked(true);
        _day4boxes[i]->setChecked(true);
        _day5boxes[i]->setChecked(true);
        _day6boxes[i]->setChecked(true);
        _day7boxes[i]->setChecked(true);
    }
}

void AppSettings::on_btUnselectAll_clicked()
{
    for (size_t i = 0; i < 24; ++i )
    {
        _day1boxes[i]->setChecked(false);
        _day2boxes[i]->setChecked(false);
        _day3boxes[i]->setChecked(false);
        _day4boxes[i]->setChecked(false);
        _day5boxes[i]->setChecked(false);
        _day6boxes[i]->setChecked(false);
        _day7boxes[i]->setChecked(false);
    }
}

void AppSettings::on_btSaveAll_clicked()
{
    QMessageBox msg;

    ProcessPool procPool;
    DataDumper<std::string, 0> nDmp;
    DataDumper<int, 0> hDmp;

    procPool._names =  nDmp.Create(_names.size());    // 1 day names
    procPool._hFlags = hDmp.Create(_names.size());    // 1 day hflags

    for (size_t k = 0; k < 7; ++k)
    {
        for (size_t i=0; i < _names.size(); ++i)
        {
            procPool._names[i] = std::string(_names[i].c_str());
            memcpy(&procPool._hFlags[i], &_hFlgs[k].at(i), sizeof(int));
        }

        // save 1st day dump
        nDmp.SaveArray(fNamesPath[k]);
        hDmp.Save(fHflgPath[k]);
    }

    //SendMessageToService();

    msg.setText("Данні успішно збережені!\n"
                "Будь ласка перезавантажте комп'ютер.");
    msg.exec();
}

void AppSettings::AllocateFileNames()
{
    // names for all days
    fNamesPath[0] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[0], GetSystemRoot());
    strcat(fNamesPath[0], "\\data\\0nms32prc_dmp.bin");

    fNamesPath[1] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[1], GetSystemRoot());
    strcat(fNamesPath[1], "\\data\\1nms32prc_dmp.bin");

    fNamesPath[2] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[2], GetSystemRoot());
    strcat(fNamesPath[2], "\\data\\2nms32prc_dmp.bin");

    fNamesPath[3] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[3], GetSystemRoot());
    strcat(fNamesPath[3], "\\data\\3nms32prc_dmp.bin");

    fNamesPath[4] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[4], GetSystemRoot());
    strcat(fNamesPath[4], "\\data\\4nms32prc_dmp.bin");

    fNamesPath[5] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[5], GetSystemRoot());
    strcat(fNamesPath[5], "\\data\\5nms32prc_dmp.bin");

    fNamesPath[6] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[6], GetSystemRoot());
    strcat(fNamesPath[6], "\\data\\6nms32prc_dmp.bin");

    // hflags for all days
    fHflgPath[0] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[0], GetSystemRoot());
    strcat(fHflgPath[0], "\\data\\0hflg32prc_dmp.bin");

    fHflgPath[1] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[1], GetSystemRoot());
    strcat(fHflgPath[1], "\\data\\1hflg32prc_dmp.bin");

    fHflgPath[2] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[2], GetSystemRoot());
    strcat(fHflgPath[2], "\\data\\2hflg32prc_dmp.bin");

    fHflgPath[3] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[3], GetSystemRoot());
    strcat(fHflgPath[3], "\\data\\3hflg32prc_dmp.bin");

    fHflgPath[4] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[4], GetSystemRoot());
    strcat(fHflgPath[4], "\\data\\4hflg32prc_dmp.bin");

    fHflgPath[5] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[5], GetSystemRoot());
    strcat(fHflgPath[5], "\\data\\5hflg32prc_dmp.bin");

    fHflgPath[6] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[6], GetSystemRoot());
    strcat(fHflgPath[6], "\\data\\6hflg32prc_dmp.bin");
}

void AppSettings::DeallocateFileNames()
{
    for (size_t i =0; i < 7; ++i)
    {
        if (fNamesPath[i]) free(fNamesPath[i]);
        if (fHflgPath[i]) free(fHflgPath[i]);
    }
}


