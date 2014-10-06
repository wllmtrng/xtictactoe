/*
 * Message.h
 *
 *  Created on: Oct 5, 2014
 *      Author: wtruong
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "UIComponent.h"

class Message: public UIComponent
{
  public:
    Message(const std::string&, Widget);
    void postMessage(const std::string&);
    void postAlert(const std::string&);
};

#endif /* MESSAGE_H_ */
