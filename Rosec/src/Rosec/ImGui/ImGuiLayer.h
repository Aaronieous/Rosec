#pragma once

#include "Rosec/Layer.h"


#include "Rosec/Events/KeyEvent.h"
#include "Rosec/Events/MouseEvent.h"
#include "Rosec/Events/ApplicationEvent.h"


namespace Rosec {


	class ROSEC_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender();

		void Begin();
		void End();

	protected:
		inline static void Init(bool set) { s_Init = set; }
		inline static bool GetInit() { return s_Init; }

		
	private:
		float m_Time = 0;
		static bool s_Init;
	};

}