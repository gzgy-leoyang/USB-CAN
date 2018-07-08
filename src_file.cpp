#include "src_file.h"
#include <QtMath>

Src_file::Src_file(QObject *parent) : QObject(parent)
{

}

int Src_file::asciiArrayToHexInt(QByteArray ba){
    int len = ba.length();
    int temp = 0 ;
    int res = 0;
    foreach (QChar c,ba) {
        char cc = c.toLatin1();
        if (cc > 0x29 && cc<0x3A){
            temp = cc - '0';
        } else if ( cc > 0x40 && cc < 0x5B ){
            temp = cc - 'A' + 0x0A;
        }
        res |= temp << (4*len - 4) ;
        len--;
    }
    return res;
}

int Src_file::asciiArrayToDecInt(QByteArray ba){
    int len = ba.length();
    int temp = 0 ;
    int res = 0;
    foreach (QChar c,ba) {
        char cc = c.toLatin1();
        if (cc > 0x30 && cc<0x39){
            temp = cc - '0';
        } else if ( cc>0x41 && cc<0x5A ){
            temp = cc - 'A' + 0x0A;
        }
        res += temp * qPow(10,len-1);
        len--;
    }
    return res;
}

int Src_file::extraFile( const QString &filename ){
    int lineCounter = 0;

    QFile f(filename);
    if( f.exists()){
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)){
            return -1;
        } else {
            /// 获取文件内容，逐一分析每行的内容
            QTextStream in(&f);
            // 进入文件
            while (!in.atEnd()){
                // 文件内逐行检查
                lineCounter++;
                QString str = in.readLine();
                QByteArray ba = str.toLatin1();

                if ( ba[0] == 'S' ){
                    int code_start_pos = 0;
                    int code_lenght = 0;
                    Src_line* line = new Src_line(this);
                    line->type = asciiArrayToHexInt(ba.mid(1,1));
                    line->lenght = asciiArrayToHexInt(ba.mid(2,2));

                    if ( line->type>0 && line->type < 4){
                        switch(line->type){
                        case 1:
                            line->addr = asciiArrayToHexInt(ba.mid(4,4));
                            code_start_pos = 8;
                            code_lenght = (line->lenght - 3)*2;
                            break;
                        case 2:
                            line->addr = asciiArrayToHexInt(ba.mid(4,6));
                            code_start_pos = 10;
                            code_lenght = (line->lenght - 4)*2;
                            break;
                        case 3:
                            line->addr = asciiArrayToHexInt(ba.mid(4,8));
                            code_start_pos = 12;
                            code_lenght = (line->lenght - 5)*2;
                            break;
                        }
                    }

                    lines.append(line);
                    qDebug()<<line->type<<line->lenght<<line->addr;
                }
            }
        }
        return 0;
    } else {
        return -1;
    }
}

Src_line::Src_line(QObject *parent) : QObject(parent)
{
    type = 0;
    lenght =0;
    addr = 0;
    sum = 0 ;
}
