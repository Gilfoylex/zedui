#ifndef MACROS_H_
#define MACROS_H_

#define ZEDUI_DISALLOW_COPY(TypeName) TypeName(const TypeName&) = delete

#define ZEDUI_DISALLOW_ASSIGN(TypeName) \
  TypeName& operator=(const TypeName&) = delete

#define ZEDUI_DISALLOW_MOVE(TypeName) \
  TypeName(TypeName&&) = delete;    \
  TypeName& operator=(TypeName&&) = delete

#define ZEDUI_DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;          \
  TypeName& operator=(const TypeName&) = delete

#define ZEDUI_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName) \
  TypeName(const TypeName&) = delete;               \
  TypeName(TypeName&&) = delete;                    \
  TypeName& operator=(const TypeName&) = delete;    \
  TypeName& operator=(TypeName&&) = delete

#define ZEDUI_DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName() = delete;                               \
  ZEDUI_DISALLOW_COPY_ASSIGN_AND_MOVE(TypeName)

#ifdef _WIN32
#define ZEDUI_EXPORT __declspec(dllexport)
#else 
#define ZEDUI_EXPORT
#endif

#endif  // MACROS_H_