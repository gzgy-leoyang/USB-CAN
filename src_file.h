#ifndef SRC_FILE_H
#define SRC_FILE_H

#include <QObject>

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStringList>
#include <QDir>

#include <QRegExp>
#include <QDirIterator>

class Src_line : public QObject
{
    Q_OBJECT
public:
    Src_line(QObject *parent = 0);

    int type;
    int lenght;
    int addr;   // 注意，64位和32位电脑上的长度不同，如果是 4字节长度的地址，是否会溢出
    int sum;
    QByteArray codes;

signals:

public slots:
};

class Src_file : public QObject
{
    Q_OBJECT
public:
    explicit Src_file(QObject *parent = 0);
    int extraFile( const QString &filename );
    QList<Src_line*> lines;
private:
    int asciiArrayToHexInt(QByteArray ba);
    int asciiArrayToDecInt(QByteArray ba);

signals:

public slots:
};



#endif // SRC_FILE_H
