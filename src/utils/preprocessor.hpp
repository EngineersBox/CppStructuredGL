#pragma once

#ifndef STRUCTURED_GL_PREPROCESSOR_HPP
#define STRUCTURED_GL_PREPROCESSOR_HPP

#include <tuple>

#define NUM_ARGS(...) (std::tuple_size<decltype(std::make_tuple(__VA_ARGS__ 0))>::value - 1)

#endif //STRUCTURED_GL_PREPROCESSOR_HPP
