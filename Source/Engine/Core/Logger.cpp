#include "Logger.h"
#include "FileIO.h"
#include <iostream>

namespace bunny {
	Logger g_l(LogLevel::Info, &std::cout, "Log.txt");

	bool Logger::log(LogLevel ll, const std::string& filename, int line) {
		if (ll < m_loglevel) {
			return false;
		}

		//switch tab "enter conditional" enter, enter
		switch (ll) {
		case LogLevel::Info:
			*this << "Info: ";
			break;
		case LogLevel::Warning:
			*this << "Warning: ";
			break;
		case LogLevel::Error:
			*this << "Error: ";
			break;
		case LogLevel::Assert:
			*this << "Assert: ";
			break;
		default:
			break;
		}

		*this << getFileName(filename) << "(" << line << ") ";

		return true;
	}
}