/*
 * Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include <WImage>

#include "WStateIcon.h"

WStateIcon::WStateIcon(const std::string icon1URI, const std::string icon2URI,
		       bool clickIsSwitch, WContainerWidget *parent)
  : WContainerWidget(parent)
{
  setInline(true);

  icon1_ = new WImage(icon1URI, this);
  icon2_ = new WImage(icon2URI, this);

  icon2_->hide();

  if (clickIsSwitch) {

	connect(icon1_, SIGNAL(clicked()),
	    icon1_, SLOT(hide()), STATIC);
    connect(icon1_, SIGNAL(clicked()),
	    icon2_, SLOT(show()), STATIC);

    connect(icon2_, SIGNAL(clicked()),
	    icon2_, SLOT(hide()), STATIC);
    connect(icon2_, SIGNAL(clicked()),
	    icon1_, SLOT(show()), STATIC);

    decorationStyle().setCursor(WCssDecorationStyle::Pointer);
  }
}

void WStateIcon::setIcon(int num)
{
  if (num == 0) {
    icon1_->show();
    icon2_->hide();
  } else {
    icon1_->hide();
    icon2_->show();
  }
}

void WStateIcon::showIcon1()
{
  previousState_ = (icon1_->isHidden() ? 1 : 0);
  setIcon(0);
}

void WStateIcon::showIcon2()
{
  previousState_ = (icon1_->isHidden() ? 1 : 0);
  setIcon(1);
}

void WStateIcon::undoShowIcon1()
{
  setIcon(previousState_);
}

void WStateIcon::undoShowIcon2()
{
  setIcon(previousState_);
}
