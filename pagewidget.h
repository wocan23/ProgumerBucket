#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QToolBar>
#include <QLineEdit>

class PageWidget : public QToolBar
{
    Q_OBJECT
public:
    explicit PageWidget(int totalNum, int pageSize = 10, int currentPage = 1);

signals:
    void to(int page, int pageSize);

public slots:
    void toPage();
    void nextPage();
    void lastPage();
    void toEndPage();
    void toStartPage();
    void changeSize();

private:
    int totalPage;
    int currentPage;
    int pageSize;
    int totalNum;

    QLineEdit * cpage;

};

#endif // PAGEWIDGET_H
