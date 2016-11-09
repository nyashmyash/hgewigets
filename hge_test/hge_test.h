#pragma once

#include "resource.h"
#include <memory>
#include "hge.h"
#include "hgesprite.h"
#include "hgefont.h"
#include "hgeparticle.h"
#include "Widget.h"
#include "WidgetContainer.h"
#include "WidgetBtn.h"
#include "WidgetImg.h"
#include <algorithm>    // std::sort

// Global Variables:
extern HGE* hge;
extern Position mousePos;
extern bool mouse_down;
extern std::vector<std::shared_ptr<Widget>> renderVect;

