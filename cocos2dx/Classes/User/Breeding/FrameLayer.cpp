#include "FrameLayer.h"
#include <array>
USING_NS_CC;

namespace User
{
	bool FrameLayer::init()
	{
		if (!Layer::init()) { return false; }
		
		auto size = Director::getInstance()->getWinSize();
		auto frameSize = Vec2(720, 1280);

		DrawNode* drawNode = DrawNode::create();
		drawNode->setPosition(Point(0.0f, 0.0f));
		this->addChild(drawNode);

		// 描画
		std::array<Point, 4> vertexes = {
			Point(0, 0),
			Point(frameSize.x, 0),
			Point(frameSize.x, frameSize.y),
			Point(0, frameSize.y),
		};
		float weight = 5.0f;
		drawNode->drawPolygon(vertexes.data(), vertexes.size(), Color4F::BLACK, weight, Color4F::RED);

		auto director = Director::getInstance();
		director->setDisplayStats(true);

		return true;
	}
}
