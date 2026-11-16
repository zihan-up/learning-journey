#ifndef LINE_H_
#define LINE_H_

class Line{
public:
    Line(int x1, int y1, int x2, int y2);
    ~Line();
    //调用的是_impl->printLine();

    void printLine();

private:
    class LineImpl;
    LineImpl * _impl;

};

#endif
