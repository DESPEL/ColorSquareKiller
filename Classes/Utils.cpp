#include "Utils.h"

USING_NS_CC;

namespace Utils {
	void resizeButton(ui::Button* btn, Size size) {
		btn->ignoreContentAdaptWithSize(false);
		btn->setContentSize(size);
	}
}