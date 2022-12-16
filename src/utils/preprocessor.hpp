#pragma once

#ifndef STRUCTURED_GL_PREPROCESSOR_HPP
#define STRUCTURED_GL_PREPROCESSOR_HPP

#include <tuple>

#define NUM_ARGS(...) _NUM_ARGS(__VA_ARGS__ 0) - 1
#define _NUM_ARGS(...) (std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value)

#endif //STRUCTURED_GL_PREPROCESSOR_HPP
