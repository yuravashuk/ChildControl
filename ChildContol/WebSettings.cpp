#include "WebSettings.h"
#include "ui_WebSettings.h"

WebSettings::WebSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebSettings)
{
    ui->setupUi(this);

    ui->lstWeb->setStyleSheet("QListWidget{background-color:rgb(237, 242, 244); border: 1px solid rgb(228, 159, 92);}"
                      "QListWidget::item:selected{background-color:rgb(46,46,46); color:rgb(228, 159, 92); border: 0px;}"
                      "QListWidget::item:hover{background-color:rgb(46,46,46); color:rgb(228, 159, 92);border: 0px;}");
    ui->lstWeb->setGeometry(QRect(10,80,681,451));
    ui->lstWeb->setMovement(QListView::Movement::Static);
    ui->lstWeb->setFocusPolicy(Qt::FocusPolicy::NoFocus);

    ui->editWidget->setVisible(false);
    ui->editWidget->setGeometry(ui->lstWeb->geometry());

    //
    InitBoxes();

    // Create filepath
    AllocateFileNames();

    // load dumps
    LoadDumps();
}

WebSettings::~WebSettings()
{
    DeallocateFileNames();
    delete ui;
}

void WebSettings::InitBoxes()
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

void WebSettings::AllocateFileNames()
{
    // names for all days
    fNamesPath[0] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[0], GetSystemRoot());
    strcat(fNamesPath[0], "\\data\\0nms32web_dmp.bin");

    fNamesPath[1] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[1], GetSystemRoot());
    strcat(fNamesPath[1], "\\data\\1nms32web_dmp.bin");

    fNamesPath[2] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[2], GetSystemRoot());
    strcat(fNamesPath[2], "\\data\\2nms32web_dmp.bin");

    fNamesPath[3] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[3], GetSystemRoot());
    strcat(fNamesPath[3], "\\data\\3nms32web_dmp.bin");

    fNamesPath[4] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[4], GetSystemRoot());
    strcat(fNamesPath[4], "\\data\\4nms32web_dmp.bin");

    fNamesPath[5] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[5], GetSystemRoot());
    strcat(fNamesPath[5], "\\data\\5nms32web_dmp.bin");

    fNamesPath[6] = (char*)malloc(sizeof(char)* 300);
    strcpy(fNamesPath[6], GetSystemRoot());
    strcat(fNamesPath[6], "\\data\\6nms32web_dmp.bin");

    // hflags for all days
    fHflgPath[0] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[0], GetSystemRoot());
    strcat(fHflgPath[0], "\\data\\0hflg32web_dmp.bin");

    fHflgPath[1] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[1], GetSystemRoot());
    strcat(fHflgPath[1], "\\data\\1hflg32web_dmp.bin");

    fHflgPath[2] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[2], GetSystemRoot());
    strcat(fHflgPath[2], "\\data\\2hflg32web_dmp.bin");

    fHflgPath[3] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[3], GetSystemRoot());
    strcat(fHflgPath[3], "\\data\\3hflg32web_dmp.bin");

    fHflgPath[4] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[4], GetSystemRoot());
    strcat(fHflgPath[4], "\\data\\4hflg32web_dmp.bin");

    fHflgPath[5] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[5], GetSystemRoot());
    strcat(fHflgPath[5], "\\data\\5hflg32web_dmp.bin");

    fHflgPath[6] = (char*)malloc(sizeof(char)* 300);
    strcpy(fHflgPath[6], GetSystemRoot());
    strcat(fHflgPath[6], "\\data\\6hflg32web_dmp.bin");
}

void WebSettings::DeallocateFileNames()
{
    for (size_t i =0; i < 7; ++i)
    {
        if (fNamesPath[i]) free(fNamesPath[i]);
        if (fHflgPath[i]) free(fHflgPath[i]);
    }
}

void WebSettings::LoadDumps()
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
        ui->lstWeb->addItem(QString::fromStdString(_names.at(i).c_str()));
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

void WebSettings::on_btUnselectAll_clicked()
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

void WebSettings::on_btSelectAll_clicked()
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

void WebSettings::on_btBack_clicked()
{
    ui->editWidget->setVisible(false);
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->lstWeb->setVisible(true);
    ui->lstWeb->raise();
}

void WebSettings::on_btSave_clicked()
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
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    ui->lstWeb->setVisible(true);
    ui->lstWeb->raise();
}

void WebSettings::on_lstWeb_clicked(const QModelIndex &index)
{
     _selectedApp = ui->lstWeb->currentItem()->text().toStdString().c_str();
}

void WebSettings::on_pushButton_6_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Додати веб-сайт"),
                                             tr("Домен сайту (без www.):"), QLineEdit::Normal,
                                             "sample-site.com", &ok);
    if (ok && !text.isEmpty())
    {
        ui->lstWeb->addItem(text);
        _names.push_back(text.toStdString());
        for (size_t i = 0; i < 7; ++i)
        {
            _hFlgs[i].push_back(0);
        }
    }
}

void WebSettings::on_pushButton_7_clicked()
{
    QListWidgetItem* w = ui->lstWeb->currentItem();

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

void WebSettings::on_pushButton_8_clicked()
{
    QListWidgetItem* w = ui->lstWeb->currentItem();
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

        // hide panel
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
        ui->lstWeb->setVisible(false);
        ui->editWidget->setVisible(true);
        ui->editWidget->raise();
    }
    else
    {
        QMessageBox msg;
        msg.setText("Спочатку виберіть сайт!");
        msg.exec();
    }
}

void WebSettings::on_btSaveAll_clicked()
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

    msg.setText("Данні успішно збережені!\n"
                "Будь ласка перезавантажте комп'ютер.");
    msg.exec();
}
