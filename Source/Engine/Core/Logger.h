#pragma once
#include "Framework/Singleton.h"
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define INFO_LOG(message) { if (bunny::Logger::Instance().log(bunny::LogLevel::Info, __FILE__, __LINE__)) { bunny::Logger::Instance() << message << "\n"; } }
#define WARNING_LOG(message) { if (bunny::Logger::Instance().log(bunny::LogLevel::Warning, __FILE__, __LINE__)) { bunny::Logger::Instance() << message << "\n"; } }
#define ERROR_LOG(message) { if (bunny::Logger::Instance().log(bunny::LogLevel::Error, __FILE__, __LINE__)) { bunny::Logger::Instance() << message << "\n"; } }
#define ASSERT_LOG(condition, message) { if (!condition && bunny::Logger::Instance().log(bunny::LogLevel::Assert, __FILE__, __LINE__)) { bunny::Logger::Instance() << message << "\n"; } assert(condition); }
#else
#define INFO_LOG(message) {}
#define WARNING_LOG(message) {}
#define ERROR_LOG(message) {}
#define ASSERT_LOG(condition, message) {}
#endif // -DEBUG

namespace bunny {
	enum class LogLevel {
		Info,
		Warning,
		Error,
		Assert
	};

	class Logger : public Singleton<Logger>	 {
	public:
		Logger(LogLevel ll = LogLevel::Info, std::ostream* o = &std::cout, const std::string& f = "log.txt") :
			m_loglevel{ ll },
			m_ostream{ o }
		{
			if (!f.empty()) m_fstream.open(f);
		}

		bool log(LogLevel ll, const std::string& filename, int line);

		template<typename T>
		Logger& operator << (T value);
	private:
		LogLevel m_loglevel;
		std::ostream* m_ostream = nullptr;
		std::ofstream m_fstream;
	};

	template<typename T>
	inline Logger& Logger::operator<<(T value) {
		if (m_ostream) {
			*m_ostream << value;
		}

		if (m_fstream.is_open()) {
			m_fstream << value;
			m_fstream.flush();
		}

		return *this;
	}
}