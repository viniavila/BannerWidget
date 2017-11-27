#include "BannerWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStaticText>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

class BannerWidgetPrivate {
    Q_DECLARE_PUBLIC(BannerWidget)
public:
    BannerWidget * const q_ptr;
    QList<QColor> bgColors;
    QList<QColor> fgColors;
    QRectF closeButtonRect;
    QPointF textPos;
    float height;
    QString message;
    bool isAnimated;
    int timeout;
    BannerWidget::Color selectedColor;
    QPixmap pixmap;
    QPointF pixmapPos;

    BannerWidgetPrivate(BannerWidget * parent) :
        q_ptr(parent),
        bgColors{Qt::white, Qt::black, "#d9edf7", "#fcf8e3", "#fce5d5"},
        fgColors{Qt::black, Qt::white, "#688fc0", "#c09853", "#e1575f"}
    {
    }

    QPolygonF cross_picture() {
        float x = q_ptr->parentWidget()->width() - 0.7*height;
        float y = 0.3*height;
        float s = 0.4*height;
        float qs = s/6.0;
        closeButtonRect = QRectF(x, y, s, s);
        QPolygonF p;
        p.append(QPointF(x,y+qs));
        p.append(QPointF(x+qs,y));
        p.append(QPointF(x+3*qs, y+2*qs));
        p.append(QPointF(x+5*qs, y));
        p.append(QPointF(x+6*qs,y+qs));
        p.append(QPointF(x+4*qs,y+3*qs));
        p.append(QPointF(x+6*qs,y+5*qs));
        p.append(QPointF(x+5*qs,y+6*qs));
        p.append(QPointF(x+3*qs,y+4*qs));
        p.append(QPointF(x+qs,y+6*qs));
        p.append(QPointF(x,y+5*qs));
        p.append(QPointF(x+2*qs,y+3*qs));
        return p;
    }

    QStaticText static_text() {
        QStaticText m(message);
        float aw = q_ptr->width() - 1.7*height;
        if (m.size().width() > aw) {
            QString em = q_ptr->fontMetrics().elidedText(message, Qt::ElideRight, aw);
            m = QStaticText(em);
        }
        float x = 0.3*height;
        float y = 0.5*(height - m.size().height());
        textPos = QPointF(x, y);
        return m;
    }

    void drawPixmap() {
        pixmap = QPixmap(q_ptr->size());
        QPainter p(&pixmap);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setPen(Qt::NoPen);
        p.setBrush(bgColors.at(selectedColor));
        p.drawRect(q_ptr->geometry());
        // Draw a close button
        p.setPen(fgColors.at(selectedColor));
        p.setBrush(fgColors.at(selectedColor));
        p.drawPolygon(cross_picture());
        // Draw the text
        QFont f = p.font();
        f.setBold(true);
        p.setFont(f);
        p.drawStaticText(textPos, static_text());
    }

    void animation_finished() {
        if (timeout > 100) {
            QTimer::singleShot(timeout, q_ptr, &BannerWidget::close);
        }
    }
};

BannerWidget::BannerWidget(Color color, const QString& message, bool animated, int timeout, QWidget *parent) :
    QWidget(parent),
    d_ptr(new BannerWidgetPrivate(this))
{
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(10);
    shadow->setColor(Qt::black);
    shadow->setOffset(0);
    setGraphicsEffect(shadow);

    QFontMetricsF f = fontMetrics();
    d_ptr->selectedColor = color;
    d_ptr->message = message;
    d_ptr->isAnimated = animated;
    d_ptr->timeout = timeout;
    d_ptr->height = 2.5*f.tightBoundingRect(message).height();
    parent->installEventFilter(this);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_DeleteOnClose, true);
    resize(parent->width(), d_ptr->height);
    d_ptr->drawPixmap();
    raise();

    if (!animated && timeout > 100)
        QTimer::singleShot(timeout, this, &BannerWidget::close);

    if (animated) {
        move(0, -d_ptr->height);
        QPropertyAnimation *anim = new QPropertyAnimation(this, "geometry");
        anim->setDuration(150);
        anim->setStartValue(QRect(QPoint(0,-d_ptr->height), size()));
        anim->setEndValue(QRect(QPoint(0,0), size()));
        show();
        connect(anim, &QPropertyAnimation::finished, this, std::bind(&BannerWidgetPrivate::animation_finished, d_ptr));
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
        show();
}

BannerWidget::~BannerWidget() {
    delete d_ptr;
}

void BannerWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.drawPixmap(d_ptr->pixmapPos, d_ptr->pixmap);
}

bool BannerWidget::eventFilter(QObject *watched, QEvent *event) {
    // Resize this widget when the parent widget resizes
    if (watched == parent() && event->type() == QEvent::Resize) {
        resize(parentWidget()->width(), d_ptr->height);
        d_ptr->drawPixmap();
    }
    return QWidget::eventFilter(watched, event);
}

void BannerWidget::mouseReleaseEvent(QMouseEvent * event) {
    // Triggered just when clicking the close button
    if (d_ptr->closeButtonRect.contains(event->pos()))
        close();
    QWidget::mouseReleaseEvent(event);
}

void BannerWidget::closeEvent(QCloseEvent *e) {
    if (d_ptr->isAnimated) {
        QPropertyAnimation *anim = new QPropertyAnimation(this, "geometry");
        anim->setDuration(150);
        anim->setEndValue(QRect(QPoint(0,-d_ptr->height), size()));
        anim->setStartValue(QRect(QPoint(0,0), size()));
        connect(anim, &QPropertyAnimation::finished, this, &BannerWidget::close);
        d_ptr->isAnimated = false;
        anim->start(QAbstractAnimation::DeleteWhenStopped);
        e->ignore();
    }
    else {
        e->accept();
    }
}

BannerWidget* BannerWidget::normal(const QString& message, bool animated, int timeout, QWidget *parent) {
    BannerWidget * pc = parent->findChild<BannerWidget*>();
    if (pc) pc->close();
    return new BannerWidget(Normal, message, animated, timeout, parent);
}

BannerWidget* BannerWidget::inverted(const QString& message, bool animated, int timeout, QWidget *parent) {
    BannerWidget * pc = parent->findChild<BannerWidget*>();
    if (pc) pc->close();
    return new BannerWidget(Inverted, message, animated, timeout, parent);
}

BannerWidget* BannerWidget::information(const QString& message, bool animated, int timeout, QWidget *parent) {
    BannerWidget * pc = parent->findChild<BannerWidget*>();
    if (pc) pc->close();
    return new BannerWidget(Information, message, animated, timeout, parent);
}

BannerWidget* BannerWidget::warning(const QString& message, bool animated, int timeout, QWidget *parent) {
    BannerWidget * pc = parent->findChild<BannerWidget*>();
    if (pc) pc->close();
    return new BannerWidget(Warning, message, animated, timeout, parent);
}

BannerWidget* BannerWidget::critical(const QString& message, bool animated, int timeout, QWidget *parent) {
    BannerWidget * pc = parent->findChild<BannerWidget*>();
    if (pc) pc->close();
    return new BannerWidget(Critical, message, animated, timeout, parent);
}
