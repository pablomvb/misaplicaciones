#include "iostream.h"

IOStream::IOStream()
{
    input = new QTextStream(stdin);
    //out = new QTextStream(stdout);
}

QString IOStream::read()
{
    return input->readAll();
}

QString IOStream::readLine()
{
    return input->readLine();
}

int IOStream::readInt()
{
    return input->readLine().toInt();
}

void IOStream::write(QString str)
{
    QTextStream out(stdout);
    out<<str;
    out.flush();
}

void IOStream::writeLine(QString str)
{
    QTextStream out(stdout);
    str.append("\n");
    out<<str;
    out.flush();
}
