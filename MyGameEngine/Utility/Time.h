//
// Time.h
//
#pragma once

#include <memory>

#include "../Common/DeviceResources.h"
#include "../Common/StepTimer.h"


namespace MyLibrary
{
	class Time
	{
	private:

		Time();


	public:

		static Time* GetInstance();

		void Update(StepTimer const& timer);

		// Properties
		const float& GetElapsedTime() { return float(m_timer.GetElapsedSeconds()); }
		const float& GetTotalTime() { return float(m_timer.GetTotalSeconds()); }


	private:

		static std::unique_ptr<Time> m_pInstance;

		StepTimer m_timer;
	};
}
