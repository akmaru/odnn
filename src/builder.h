#pragma once

#include <optional>
#include <utility>

namespace odnn {

#define ODNN_BUILDER_FIELD(Type, name)                                     \
public:                                                                    \
  inline auto name(const Type& new_##name)->decltype(*this) { /* NOLINT */ \
    this->name##_ = new_##name;                                            \
    return *this;                                                          \
  }                                                                        \
  inline auto name(Type&& new_##name)->decltype(*this) { /* NOLINT */      \
    this->name##_ = std::move(new_##name);                                 \
    return *this;                                                          \
  }                                                                        \
  inline const Type& name() const noexcept { /* NOLINT */                  \
    return this->name##_;                                                  \
  }                                                                        \
  inline Type& name() noexcept { /* NOLINT */                              \
    return this->name##_;                                                  \
  }                                                                        \
                                                                           \
private:                                                                   \
  Type name##_ /* NOLINT */

#define ODNN_BUILDER_OPTIONAL_FIELD(Type, name)                            \
public:                                                                    \
  inline auto name(const Type& new_##name)->decltype(*this) { /* NOLINT */ \
    this->name##_ = new_##name;                                            \
    return *this;                                                          \
  }                                                                        \
  inline auto name(Type&& new_##name)->decltype(*this) { /* NOLINT */      \
    this->name##_ = std::move(new_##name);                                 \
    return *this;                                                          \
  }                                                                        \
  inline const std::optional<Type>& name() const noexcept { /* NOLINT */   \
    return this->name##_;                                                  \
  }                                                                        \
  inline std::optional<Type>& name() noexcept { /* NOLINT */               \
    return this->name##_;                                                  \
  }                                                                        \
                                                                           \
private:                                                                   \
  std::optional<Type> name##_ = std::nullopt /* NOLINT */

}  // namespace odnn
