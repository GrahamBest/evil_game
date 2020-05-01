#pragma once

template <class T>
class c_singleton
{
public:
	static T* get_instance()
	{
		static T m_instance; // this instance is static inside this function, that means that this function will return the same instance.

		return &m_instance;
	};
private:
};