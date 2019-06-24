/*
 * version: 1.0.0.2
 * last modified date: 2013.7.23
 * last modified by: leo
 *
 */
#ifndef NG_HEADER_FOR_LOG4CXX_LOG_VAR_HPP
#define NG_HEADER_FOR_LOG4CXX_LOG_VAR_HPP

#include <string>

#define LOG_VAR(var) \
  #var"["<< ng_log::MaybeNull (var) << "]"

#define LOG_NOVAR(var) \
  "["<< ng_log::MaybeNull (var) << "]"

//#include <QString>

namespace ng_log
{
static std::string MaybeNull (char value)
{
  std::string s;
  if (value == 0) {
    s = "";
  } else {
    s.append (1, value);
  }
  return s;
}

static std::string MaybeNull (unsigned char value)
{
  std::string s;
  if (value == 0) {
    s = "";
  } else {
    s.append (1, value);
  }
  return s;
}


static char *MaybeNull (char *value)
{
  return value;
}

static char *MaybeNull (const char *value_const)
{
  return const_cast<char *> (value_const);
}

static wchar_t *MaybeNull (wchar_t *value)
{
  return value;
}

static wchar_t *MaybeNull (const wchar_t *value_const)
{
  return const_cast<wchar_t *> (value_const);
}

static int MaybeNull (int value)
{
  return value;
}

static unsigned int MaybeNull (unsigned int value)
{
  return value;
}

static int MaybeNull (long value)
{
  return value;
}

static int MaybeNull (unsigned long value)
{
  return value;
}

static int MaybeNull (long long value)
{
  return value;
}

static bool MaybeNull (bool value)
{
  return value;
}

static std::string MaybeNull (std::string value)
{
  return value;
}

static float MaybeNull (float value)
{
  return value;
}

static double MaybeNull (double value)
{
  return value;
}

static void *MaybeNull (void *value)
{
  return value;
}

static void *MaybeNull (const void *value_const)
{
  return const_cast<void *>(value_const);
}

}//namespace ng_log

#endif//NG_HEADER_FOR_LOG4CXX_LOG_VAR_HPP
