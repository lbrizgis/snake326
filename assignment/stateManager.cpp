#include "stateManager.h"

sn::stateManager::stateManager() : m_add(false), m_replace(false), m_remove(false) {

}

sn::stateManager::~stateManager() {

}

void sn::stateManager::add(std::unique_ptr<state> toAdd, bool replace) {

	m_add = true;
	m_newState = std::move(toAdd);

	m_replace = replace;

}


void sn::stateManager::PopCurrent() {

	m_remove = true;

}


void sn::stateManager::ProcessStateChange() {

    if (m_remove && (!m_stateStack.empty()))
    {
        m_stateStack.pop();

        if (!m_stateStack.empty())
        {
            m_stateStack.top()->Start();
        }

        m_remove = false;
    }

    if (m_add)
    {
        if (m_replace && (!m_stateStack.empty()))
        {
            m_stateStack.pop();
            m_replace = false;
        }

        if (!m_stateStack.empty())
        {
            m_stateStack.top()->Pause();
        }

        m_stateStack.push(std::move(m_newState));
        m_stateStack.top()->Init();
        m_stateStack.top()->Start();
        m_add = false;
    }
}


std::unique_ptr<sn::state>& sn::stateManager::GetCurrent() {

	return m_stateStack.top();
}