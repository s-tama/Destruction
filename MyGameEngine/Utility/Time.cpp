//
// Time.cpp
// 作成日: 2019/03/31
//

#include "Time.h"


std::unique_ptr<MyLibrary::Time> MyLibrary::Time::m_pInstance;

MyLibrary::Time::Time()
{
}

MyLibrary::Time* MyLibrary::Time::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance.reset(new Time());
	return m_pInstance.get();
}

void MyLibrary::Time::Update(StepTimer const& timer)
{
	m_timer = timer;
}


