/*
 * Message.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: wtruong
 */
#include <Xm/Label.h>

#include "Message.h"

Message::Message(const std::string& name, Widget parent)
    : UIComponent(name)
{
  w_ = XmCreateLabel(parent, const_cast<char*>(name_.c_str()), NULL, 0);
  installDestroyHandler();
  postMessage(" "); // Clear the widget
}

void Message::postMessage(const std::string& msg)
{
  // Convert the character string to a compound string for Motif
  XmString xmstr = XmStringCreateSimple (const_cast<char*>(msg.c_str()));
  // Display the new label
  XtVaSetValues(w_, XmNlabelString, xmstr, NULL);
  //XmLabel copies the string, so we can free our copy
  XmStringFree(xmstr);
}

void Message::postAlert(const std::string& msg)
{
  if (msg.empty()) {
    postMessage (msg);  // Display the string
  }

  // Sound a bell as an alert.
  XBell(XtDisplay (w_), 100);
}
