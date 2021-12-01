#pragma once

#include <stack>
#include<memory>
#include "state.h"



namespace sn
{

	class stateManager {

	private:
		std::stack<std::unique_ptr<state>> m_stateStack;
		std::unique_ptr<state> m_newState;

		bool m_add;
		bool m_replace;
		bool m_remove;

	public:
		stateManager();
		~stateManager();

		void add(std::unique_ptr<state> toAdd, bool replace = false);
		void PopCurrent();
		void ProcessStateChange();
		std::unique_ptr<state>& GetCurrent();

	};
	
}
