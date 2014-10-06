/*
 * BasicComponent.cpp
 *
 *  Created on: Oct 4, 2014
 *      Author: wtruong
 */

#include <cstdio>

#include "UIComponent.h"

UIComponent::~UIComponent() {
	if (w_) {
	  XtRemoveCallback(w_, XmNdestroyCallback,
	                   UIComponent::widgetDestroyedCallback,
	                   (XtPointer)this);
	  XtDestroyWidget(w_);
	}
}

void UIComponent::manage()
{
  if (w_) {
    //TODO: Put a check to see if XmNdestroyCallback is registered
    XtManageChild(w_);
  }
}

void UIComponent::unmanage()
{
  if (w_) {
    XtUnmanageChild(w_);
  }
}

void UIComponent::widgetDestroyed()
{
  w_ = NULL;
}

UIComponent::UIComponent(const std::string& n)
    : name_(n)
{
  w_ = NULL;
}

void UIComponent::installDestroyHandler()
{
  if (w_) {
    XtAddCallback(w_, XmNdestroyCallback,
                  UIComponent::widgetDestroyedCallback,
                  (XtPointer)this);
  }
}

void UIComponent::setDefaultResources(const Widget,
    const char* resourceSpec[])
{
  int i;
  Display *dpy = XtDisplay(w_);
  XrmDatabase rdb = NULL;

  // Create empty resource database
  rdb = XrmGetStringDatabase("");

  // Add the Component resources, prepending the name of the component
  i = 0;
  while (resourceSpec[i] != NULL) {
    char buf[1000];

    snprintf(buf, 1000, "*%s%s", name_.c_str(), resourceSpec[i++]);
    XrmPutLineResource(&rdb, buf);
  }

  // Merge them into the Xt database, with lowest precedence
  if (rdb) {
    XrmDatabase db = XtDatabase(dpy);
    XrmCombineDatabase(rdb, &db, FALSE);
  }
}

void UIComponent::getResources(const XtResourceList resources,
                               int numResources)
{
  if (w_ && resources) {
    XtGetSubresources(XtParent(w_), (XtPointer)this,
                      name_.c_str(), className(),
                      resources, numResources,
                      NULL, 0);
  }
}

void UIComponent::widgetDestroyedCallback(Widget,
                                          XtPointer clientData,
                                          XtPointer)
{
  UIComponent* obj = (UIComponent*)clientData;
  obj->widgetDestroyed();
}
