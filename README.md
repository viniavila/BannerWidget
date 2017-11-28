## Welcome to my BannerWidget module

This class is intended to create fancy and discrete notifications to show to the users information, warning and critical messages directly your program's Qt UI. This class was inspired by GtkInfoBar Gtk3 widget, as there is no equivalent of this widget in Qt. Although inspired by GtKInfoBar, BannerWidget is simpler and limited. Its main objective is just show messages, on the other hand, GtkInfoBar permits add actions like a real message box replacement.
 
![alt text](https://github.com/viniavila/BannerWidget/blob/master/test/example.png "BannerWidget Examples")

### Installation

* Embbed the code into your application. You can download/clone my source code and import the .h and .cpp files through Qt Creator or whatever source code editor you are using.

* You can create a shared or static library using my class, but I will not explain how to do this. If you want to do this, I can suppose you know how to do it.

### Using

Use this module is pretty simple. Just use one of its static functions:
```
BannerWidget::normal(message, animated, timeout, parent);
BannerWidget::inverted(message, animated, timeout, parent);
BannerWidget::information(message, animated, timeout, parent);
BannerWidget::warning(message, animated, timeout, parent);
BannerWidget::critical(message, animated, timeout, parent);
``` 
* message: `QString` value - the message you want to show to the user
* animated: `bool` value - tell if you want the banner to show/hide using a fancy slide animation
* timeout: `int` value - number of milliseconds to make the banner disappear automatically. Any value greater than zero will set the timeout. Negative values disable the timeout function and the banner will be closed only by pressing the close button or calling the slot `close()` member. 
* parent: `QWidget` pointer - a pointer to the QWidget instance where the banner will be drawn.

These static functions returns a `BannerWidget` pointer so one can optionally connect its slot `close()` to another widget signal or make the banner disapear based in events occurring in the parent widget routine. Internally `Qt::WA_DeleteOnClose` BannerWidget attribute was set `true`, so deleting the pointer is not necessary.

Rich Text is NOT supported because there is no easy way to elide a string with HTML tags. When Qt add support to this in an easier way, I will add it too. Indeed all messages are formatted in **bold**
 
You can add just one BannerWidget per parent QWidget. If you try to create another BannerWidget associated with one parent widget, the program will close the previous BannerWidget before creating the new one.

### Licensing

My code is licensed in LGPL v3 so you can use it either in open source or closed source applications since it concerns with the terms of this license. If you are using my code into your project and finds it useful, do not forget to mention my name in the credits, and if it is worthy, donation can be accepted.

## Authors and Contributors
Vinícius de Ávila Jorge (@viniavila). You can contact me through my GitHub profile, or if you prefer, [email](mailto:vinicius.avila.jorge@gmail.com) me.

Many thanks for using this code!

