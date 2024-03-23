#pragma once

#include "beatsaber-hook/shared/utils/utils.h"
#include "paper/shared/logger.hpp"

#define INFO(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::INF>(str, "Transitions" __VA_OPT__(, __VA_ARGS__))
#define DEBUG(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::DBG>(str, "Transitions" __VA_OPT__(, __VA_ARGS__))
#define ERROR(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::ERR>(str, "Transitions" __VA_OPT__(, __VA_ARGS__))
#define WARNING(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::WRN>(str, "Transitions" __VA_OPT__(, __VA_ARGS__))
#define CRITICAL(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::CRIT>(str, "Transitions" __VA_OPT__(, __VA_ARGS__))
