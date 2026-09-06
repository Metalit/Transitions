#pragma once

#include "paper2_scotland2/shared/logger.hpp"

static constexpr auto Logger = Paper::ConstLoggerContext(MOD_ID);

#define LOG_INFO(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::INF>(str, MOD_ID __VA_OPT__(, __VA_ARGS__))
#define LOG_ERROR(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::ERR>(str, MOD_ID __VA_OPT__(, __VA_ARGS__))
