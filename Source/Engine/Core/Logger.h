#pragma once
#include <string>
#include <cassert>
#include <fstream>

#ifdef _DEBUG
#define INFO_LOG(message) { if (bunny::g_l.log(bunny::LogLevel::Info, __FILE__, __LINE__)) { bunny::g_l << message << "\n"; } }
#define WARNING_LOG(message) { if (bunny::g_l.log(bunny::LogLevel::Warning, __FILE__, __LINE__)) { bunny::g_l << message << "\n"; } }
#define ERROR_LOG(message) { if (bunny::g_l.log(bunny::LogLevel::Error, __FILE__, __LINE__)) { bunny::g_l << message << "\n"; } }
#define ASSERT_LOG(condition, message) { if (!condition && bunny::g_l.log(bunny::LogLevel::Assert, __FILE__, __LINE__)) { bunny::g_l << message << "\n"; } assert(condition); }
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

	class Logger {
	public:
		Logger(LogLevel ll, std::ostream* o, const std::string& f = "") :
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

	extern Logger g_l;

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