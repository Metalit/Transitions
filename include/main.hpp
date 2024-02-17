#pragma once

#include "scotland2/shared/loader.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

#define LOG_INFO(...) getLogger().info(__VA_ARGS__)
#define LOG_ERROR(...) getLogger().error(__VA_ARGS__)

Logger& getLogger();
