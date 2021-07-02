#pragma once

#include <quill/Quill.h>

#include <string>
#include <vector>

static std::shared_ptr<quill::Logger> initLogger(const std::string& name = "app",
                                                 const std::string& logFilename = "app.log") {
  quill::start(false, {});

  auto formatter = QUILL_STRING(
      "[%(ascii_time)] #%(process).%(thread) %(filename)/%(function_name:):%(lineno:<8) [%(logger_name)] "
      "%(level_name) %(message)");

  auto file_handler = quill::rotating_file_handler(logFilename, "a", 1024 * 1024 * 5, 5);
  file_handler->set_pattern(formatter, "%D %H:%M:%S.%Qms %z", quill::Timezone::LocalTime);

  auto console_handler = quill::stdout_handler();
  console_handler->set_pattern(formatter, "%D %H:%M:%S.%Qms %z", quill::Timezone::LocalTime);

  auto logger = quill::create_logger(name.c_str(), {file_handler, console_handler});
  logger->set_log_level(quill::LogLevel::TraceL3);
  return std::shared_ptr<quill::Logger>(logger);
};
