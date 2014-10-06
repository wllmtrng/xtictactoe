/*
 * Message.cpp
 *
 *  Created on: Oct 5, 2014
 *      Author: wtruong
 */
#include <Xm/Label.h>

#include "Message.h"

Message::Message(const std::string& name, Widget parent)
    : UIComponent(name_)
{
  w_ = XmCreateLabel(parent, const_cast<char*>(name_.c_str()), NULL, 0);
  installDestroyHandler();
  postMessage(" "); // Clear the widget
}

void Message::postMessage(const std::string& msg)
{

}

void Message::postAlert(const std::string& msg)
{
}
