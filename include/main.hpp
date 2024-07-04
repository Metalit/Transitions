#pragma once

#include "beatsaber-hook/shared/utils/logging.hpp"

#define LOG_INFO(...) logger.info(__VA_ARGS__)
#define LOG_ERROR(...) logger.error(__VA_ARGS__)

constexpr auto logger = Paper::ConstLoggerContext(MOD_ID);
