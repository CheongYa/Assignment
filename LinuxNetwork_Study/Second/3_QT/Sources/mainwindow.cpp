// 검색 기능과 정렬하는 부분까지 구현한 상태. 단, 정렬이 1초마다 갱신되는 탓에 풀림

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // DB 연결
    DB_Connection = QSqlDatabase::addDatabase("QSQLITE");
    // 현재 QT가 있는 경로에 있는 people.db에 접속
    DB_Connection.setDatabaseName("/home/roo/main/main.db");

    // DB 연결 예외처리
    if (!DB_Connection.open())
    {
        qDebug() << "DB에 연결할 수 없습니다.";
        qDebug() << "에러 : " << DB_Connection.lastError();
        exit(1);
    }
    else
    {
        qDebug() << "DB와 연결하였습니다.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// clear 버튼 기능
void MainWindow::on_pushButton_Clear_clicked()
{
    // table 위젯 정리 (행, 열, 헤더 초기화)
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    ColumnHeader.clear();

    // 검색 및 체크박스 정리
    ui->lineEdit_Search->clear();
    ui->checkBox_ExactlyMatch->setChecked(false);

    // comboBox 테이블 변환
    tableName = "테이블을 선택해주세요";
    ui->comboBox_Table->setCurrentText("테이블을 선택해주세요");
}

// 검색 기능
void MainWindow::on_pushButton_Search_clicked()
{
    // 검색어를 담을 리스트
    QList<QTableWidgetItem*> searchItems;

    // 단어 입력하지 않ㅇ르 시, 테이블 내용 전체를 보여줌
    if(ui->lineEdit_Search->text().isEmpty())
    {
        for(int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            // 숨긴 보여줌
            if(ui->tableWidget->isRowHidden(i))
            {
                ui->tableWidget->showRow(i);
            }
        }
        return;
    }
    // 체크박스 "ExactlyMatch"가 체크되었을 때는 정확한 일치로 검색, 그렇지 않으면 포함된 내용으로 검색
    ui->checkBox_ExactlyMatch->checkState()==Qt::Checked?searchItems=ui->tableWidget->findItems(ui->lineEdit_Search->text(),Qt::MatchExactly|Qt::MatchRecursive):
            searchItems=ui->tableWidget->findItems(ui->lineEdit_Search->text(),Qt::MatchContains|Qt::MatchRecursive);

    // 찾은 아이템이 하나라도 있다면
    if(searchItems.count()>0)
    {
        // 테이블의 모든 행을 숨김
        for(int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->hideRow(i);
        }
        // 찾은 각 아이템의 행을 보여줌
        for(int i=0; i<searchItems.count(); i++)
        {
            ui->tableWidget->showRow(searchItems.at(i)->row());
        }
    }
    else // 찾은 아이템이 없다면, 테이블 내용 전체를 숨김
    {
        for(int i=0; i<ui->tableWidget->rowCount(); i++)
        {
            ui->tableWidget->hideRow(i);
        }
    }
}

// 테이블 선택 박스 기능
void MainWindow::on_comboBox_Table_activated(const QString &arg1)
{
    // 매개변수로 보내줘도 괜찮지만, timer를 사용하기 위해서는 매개변수를 사용하지 않는게 좋기 때문에 변수를 하나 생성.
    tableName = arg1;

    // 기존 table 위젯 정리 (행, 열, 헤더 초기화)
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    ColumnHeader.clear();

    writeLogFile();
    updateTableAndCombobox();

    // 정렬 부분
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(slot_table_clicked(int)));

    showInformation();
    restartTimer(1000, SLOT(showInformation()));
}

// 동작 로그 기능
void MainWindow::writeLogFile()
{
    // 로그 앞부분 년월일 시분초 부분
    QString time_format = "yyyy-MM-dd HH:mm:ss";
    QDateTime a = QDateTime::currentDateTime();
    QString as = a.toString(time_format);

    // txt 파일에 log 남기는 부분
    QFile File("/home/roo/main/log.txt");
    File.open(QFile::WriteOnly | QFile::Append | QFile::Text);

    QTextStream SaveFile(&File);

    // 한글 깨짐 현상이 발생. 이를 고치기 위해 codec 별도 구성.
    QTextCodec *codec = QTextCodec::codecForLocale();
    QString name = "[" + as + "] " + tableName + "를 조회하였습니다. #QT\n";

    // 8Bit로 별도로 컴파일.
    SaveFile << codec->toUnicode(name.toLocal8Bit());

    // 파일닫기
    File.close();
}

// 정보 별 테이블 상단바 기능
void MainWindow::updateTableAndCombobox()
{
    if (tableName == "deb_table" || tableName == "rpm_table")
    {
        // table 위젯의 헤더 생성 및 설정
        ui->tableWidget->setColumnCount(4);
        ColumnHeader << "SW 정보명" << "SW 버전" << "SW 설치날짜" << "DB 저장 시간";
        ui->tableWidget->setHorizontalHeaderLabels(ColumnHeader);
    }
    else if (tableName == "os_table")
    {
        // table 위젯의 헤더 생성 및 설정
        ui->tableWidget->setColumnCount(3);
        ColumnHeader << "OS 정보명" << "OS 정보 내용" <<"DB 저장 시간";
        ui->tableWidget->setHorizontalHeaderLabels(ColumnHeader);
    }
    else if (tableName == "cpu_table")
    {
        // table 위젯의 헤더 생성 및 설정
        ui->tableWidget->setColumnCount(4);
        ColumnHeader << "CPU 정보명" << "CPU 정보 내용" << "Processor 번호" <<"DB 저장 시간";
        ui->tableWidget->setHorizontalHeaderLabels(ColumnHeader);
    }
    else if (tableName == "nic_table")
    {
        // table 위젯의 헤더 생성 및 설정
        ui->tableWidget->setColumnCount(5);
        ColumnHeader << "NIC 정보명" << "운영 상태" << "속도" << "MAC 주소" << "DB 저장 시간";
        ui->tableWidget->setHorizontalHeaderLabels(ColumnHeader);
    }
    else if (tableName == "memory_table")
    {
        // table 위젯의 헤더 생성 및 설정
        ui->tableWidget->setColumnCount(3);
        ColumnHeader << "Memory 정보명" << "Memory 정보 내용" <<"DB 저장 시간";
        ui->tableWidget->setHorizontalHeaderLabels(ColumnHeader);
    }
}

// 정렬 기능
void MainWindow::slot_table_clicked(int column)
{
    ui->tableWidget->sortByColumn(column, Qt::AscendingOrder);
}

// 테이블에 조회 기능
void MainWindow::showInformation()
{
    // DB 접근
    DB_Connection.open();
    QSqlDatabase::database().transaction();

    QSqlQuery QueryLoadData(DB_Connection);
    if(!QueryLoadData.prepare("SELECT * FROM " + tableName))
    {
        // table 위젯 정리 (행, 열, 헤더 초기화)
        ui->tableWidget->setRowCount(0);
        ui->tableWidget->setColumnCount(0);
        ColumnHeader.clear();

        ui->lineEdit_Search->clear();

        updateTableAndCombobox();
    }

    if (QueryLoadData.exec())
    {
        int NumberOfRowsToDisplay = 0;
        while (QueryLoadData.next())
        {
            NumberOfRowsToDisplay += 1;
        }

        ui->tableWidget->setRowCount(NumberOfRowsToDisplay);
        // 첫 번째 레코드로 이동
        QueryLoadData.seek(-1);

        int RowNumber = 0;
        while (QueryLoadData.next())
        {
            if (tableName == "deb_table" || tableName == "rpm_table")
            {
                ui->tableWidget->setItem(RowNumber, 0, new QTableWidgetItem(QString(QueryLoadData.value("name").toString())));
                ui->tableWidget->setItem(RowNumber, 1, new QTableWidgetItem(QString(QueryLoadData.value("version").toString())));
                ui->tableWidget->setItem(RowNumber, 2, new QTableWidgetItem(QString(QueryLoadData.value("install_date").toString())));
                ui->tableWidget->setItem(RowNumber, 3, new QTableWidgetItem(QString(QueryLoadData.value("create_at").toString())));
                RowNumber += 1;
            }
            else if (tableName == "os_table")
            {
                ui->tableWidget->setItem(RowNumber, 0, new QTableWidgetItem(QString(QueryLoadData.value("name").toString())));
                ui->tableWidget->setItem(RowNumber, 1, new QTableWidgetItem(QString(QueryLoadData.value("detail").toString())));
                ui->tableWidget->setItem(RowNumber, 2, new QTableWidgetItem(QString(QueryLoadData.value("create_at").toString())));
                RowNumber += 1;
            }
            else if (tableName == "cpu_table")
            {
                ui->tableWidget->setItem(RowNumber, 0, new QTableWidgetItem(QString(QueryLoadData.value("name").toString())));
                ui->tableWidget->setItem(RowNumber, 1, new QTableWidgetItem(QString(QueryLoadData.value("detail").toString())));
                ui->tableWidget->setItem(RowNumber, 2, new QTableWidgetItem(QString(QueryLoadData.value("processor").toString())));
                ui->tableWidget->setItem(RowNumber, 3, new QTableWidgetItem(QString(QueryLoadData.value("create_at").toString())));
                RowNumber += 1;
            }
            else if (tableName == "nic_table")
            {
                ui->tableWidget->setItem(RowNumber, 0, new QTableWidgetItem(QString(QueryLoadData.value("interface").toString())));
                ui->tableWidget->setItem(RowNumber, 1, new QTableWidgetItem(QString(QueryLoadData.value("operation_state").toString())));
                ui->tableWidget->setItem(RowNumber, 2, new QTableWidgetItem(QString(QueryLoadData.value("speed").toString())));
                ui->tableWidget->setItem(RowNumber, 3, new QTableWidgetItem(QString(QueryLoadData.value("mac_address").toString())));
                ui->tableWidget->setItem(RowNumber, 4, new QTableWidgetItem(QString(QueryLoadData.value("create_at").toString())));
                RowNumber += 1;
            }
            else if (tableName == "memory_table")
            {
                ui->tableWidget->setItem(RowNumber, 0, new QTableWidgetItem(QString(QueryLoadData.value("name").toString())));
                ui->tableWidget->setItem(RowNumber, 1, new QTableWidgetItem(QString(QueryLoadData.value("detail").toString())));
                ui->tableWidget->setItem(RowNumber, 2, new QTableWidgetItem(QString(QueryLoadData.value("create_at").toString())));
                RowNumber += 1;
            }
        }
    }
    // tablewidget의 컬럼 텍스트 크기를 글자에 맞춤
    //ui->tableWidget->resizeColumnsToContents();
    setColumnsWidth();

    QSqlDatabase::database().commit();
    DB_Connection.close();
}

// 타이머 기능
void MainWindow::restartTimer(int interval, const char *slotFunction)
{
    // 중복 타이머 제거 부분
    if (m_Timer && m_Timer->isActive())
    {
        m_Timer->stop(); // 이미 실행 중인 타이머가 있다면 중지
        delete m_Timer;  // 타이머 삭제
        m_Timer = nullptr; // nullptr로 설정
    }

    m_Timer = new QTimer(this);
    connect(m_Timer, SIGNAL(timeout()), this, slotFunction);
    m_Timer->start(interval); // 현재 1초(1000)마다 반복
}

// 컬럼의 너비 기능
void MainWindow::setColumnsWidth()
{
    if (tableName == "deb_table" || tableName == "rpm_table")
    {
        ui->tableWidget->setColumnWidth(0, 250);
        ui->tableWidget->setColumnWidth(1, 250);
        ui->tableWidget->setColumnWidth(2, 250);
        ui->tableWidget->setColumnWidth(3, 250);
    }
    else if (tableName == "cpu_table")
    {
        ui->tableWidget->setColumnWidth(0, 200);
        ui->tableWidget->setColumnWidth(1, 450);
        ui->tableWidget->setColumnWidth(2, 150);
        ui->tableWidget->setColumnWidth(3, 200);
    }
    else if (tableName == "nic_table")
    {
        ui->tableWidget->setColumnWidth(0, 200);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2, 200);
        ui->tableWidget->setColumnWidth(3, 200);
        ui->tableWidget->setColumnWidth(4, 200);
    }
    else if (tableName == "os_table" || tableName == "memory_table")
    {
        ui->tableWidget->setColumnWidth(0, 300);
        ui->tableWidget->setColumnWidth(1, 450);
        ui->tableWidget->setColumnWidth(2, 250);
    }
}
