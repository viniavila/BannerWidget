#ifndef BANNERWIDGET_H
#define BANNERWIDGET_H

#include <QWidget>

class BannerWidgetPrivate;

class BannerWidget : public QWidget {
    Q_OBJECT
    Q_DECLARE_PRIVATE(BannerWidget)
public:
    enum Color {
        Normal,
        Inverted,
        Information,
        Warning,
        Critical
    };

    static BannerWidget* normal(const QString& message, bool animated, int timeout, QWidget *parent = nullptr);
    static BannerWidget* inverted(const QString& message, bool animated, int timeout, QWidget *parent = nullptr);
    static BannerWidget* information(const QString& message, bool animated, int timeout, QWidget *parent = nullptr);
    static BannerWidget* warning(const QString& message, bool animated, int timeout, QWidget *parent = nullptr);
    static BannerWidget* critical(const QString& message, bool animated, int timeout, QWidget *parent = nullptr);
    virtual ~BannerWidget();

protected:
    void paintEvent(QPaintEvent*);
    bool eventFilter(QObject *watched, QEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
    void closeEvent(QCloseEvent*);

private:
    explicit BannerWidget(Color color, const QString& message, bool animated, int timeout, QWidget *parent = nullptr);
    BannerWidgetPrivate * const d_ptr;
};

#endif // BANNERWIDGET_H
