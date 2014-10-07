#ifndef UICOMPONENT_H_
#define UICOMPONENT_H_

#include <string>
#include <Xm/Xm.h>

class UIComponent
{
  public:
    virtual ~UIComponent();
    virtual void manage();
    virtual void unmanage();
    virtual const char* const className() { return "UIComponent"; }
    const Widget baseWidget() { return (w_); }

  protected:
    std::string name_;
    Widget w_;

    virtual void widgetDestroyed();
    UIComponent(const std::string&);
    void installDestroyHandler();
    // TODO: Convert const char* to vector to be more safe
    void setDefaultResources(const Widget, const char*[]);
    void getResources(const XtResourceList, int);

  private:
    // Interface between XmNdestroyCallback and this class
    static void widgetDestroyedCallback(Widget, XtPointer, XtPointer);
};

#endif /* UICOMPONENT_H_ */
