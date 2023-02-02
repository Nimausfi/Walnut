#pragma once

namespace Walnut {

	class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnAttach2() {}
		virtual void OnDetach2() {}

		virtual void OnUpdate(float ts) {}
		virtual void OnUIRender() {}
		virtual void OnUIRender2() {}
	};

}