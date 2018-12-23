#ifndef JAMTEMPLATE_BOX2DOBJECT_HPP_INCLUDEGUARD
#define JAMTEMPLATE_BOX2DOBJECT_HPP_INCLUDEGUARD

#include <memory>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "../JamTemplate/SmartObject.hpp"
#include "../JamTemplate/GameObject.hpp"

namespace JamTemplate {

	class Box2DObject : public GameObject
	{
	public:
		using Sptr = std::shared_ptr<Box2DObject>;
		Box2DObject() = delete;

		Box2DObject(std::shared_ptr<b2World> world, const b2BodyDef* def)
		{
			setB2Body(world->CreateBody(def));
		}

		
		
	
		b2Body* getB2Body()
		{
			return m_body;
		}

	private:

		// this pointer is NOT owning!
		// do never call delete on this
		b2Body* m_body{nullptr};

		void doUpdate(float const /*elapsed*/) override {};
		void doDraw() const override {};
		void doCreate() override {};

		void setB2Body(b2Body* body)
		{
			m_body = body;
		}
	};
}
#endif
