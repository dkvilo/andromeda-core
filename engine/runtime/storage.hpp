#ifndef ANDROMEDA_RUNTIME_STORAGE
#define ANDROMEDA_RUNTIME_STORAGE

#include <vector>

#include "andromeda.hpp"

class Andromeda::Runtime::Storage
{

public:
	static void AppendLog(const char *data)
	{
		Get().append_log_impl(data);
	}

	static std::vector<const char *> &GetLogs()
	{
		return Get().get_logs_impl();
	}

private:
	std::vector<const char *> m_Logs;
	std::vector<const char *> &get_logs_impl()
	{
		return m_Logs;
	}

	void append_log_impl(const char *data)
	{
		m_Logs.push_back(data);
	}

	static Storage &Get()
	{
		static Storage s_Instance;
		return s_Instance;
	}
};

#endif // ANDROMEDA_RUNTIME_STORAGE
