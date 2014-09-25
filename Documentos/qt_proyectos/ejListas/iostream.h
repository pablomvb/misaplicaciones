#ifndef IOSTREAM_H
#define IOSTREAM_H

#include <QTextStream>

class IOStream
{
    QTextStream* input;
    //QTextStream* out;
public:
    IOStream();
    QString read();
    QString readLine();
    int readInt();
    void write(QString str);
    void writeLine(QString str);
};

#endif // IOSTREAM_H
