/*
 * Copyright (C) 2005 Koen Deforche, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
// This may look like C code, but it's really -*- C++ -*-
#ifndef WSTATEICON_H_
#define WSTATEICON_H_

#include <WContainerWidget>

class WImage;

class WStateIcon : public WContainerWidget
{
  //MOC: W_OBJECT WStateIcon:WContainerWidget
  W_OBJECT;

public:
  WStateIcon(const std::string icon1URI, const std::string icon2URI,
	     bool clickIsSwitch = true, WContainerWidget *parent = 0);

  WImage *icon1() const { return icon1_; }
  WImage *icon2() const { return icon2_; }

  void setIcon(int num);

public static_slots:
  //MOC: STATIC SLOT WStateIcon::showIcon1()
  void showIcon1();
  //MOC: STATIC SLOT WStateIcon::showIcon2()
  void showIcon2();

private:
  WImage *icon1_;
  WImage *icon2_;

  int previousState_;
  void undoShowIcon1();
  void undoShowIcon2();
};

#endif // WSTATEICON_H_
